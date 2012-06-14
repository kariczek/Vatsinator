/*
    pilot.cpp
    Copyright (C) 2012  Michał Garapich garrappachc@gmail.com

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui>

#include "db/airportsdatabase.h"
#include "db/firsdatabase.h"

#include "modules/modelsmatcher.h"

#include "ui/mapwidget/mapwidget.h"

#include "vatsimdata/vatsimdatahandler.h"

#include "pilot.h"
#include "defines.h"

/*
 * 0 callsign
 * 1 cid
 * 2 realname
 * 3 clienttype
 * 4 frequency
 * 5 latitude
 * 6 longitude
 * 7 altitude
 * 8 groundspeed
 * 9 planned_aircraft
 * 10 planned_tascruise
 * 11 planned_depairport
 * 12 planned_altitude
 * 13 planned_destairport
 * 14 server
 * 15 protrevision
 * 16 rating
 * 17 transponder
 * 18 facilitytype
 * 19 visualrange
 * 20 planned_revision
 * 21 planned_flighttype
 * 22 planned_deptime
 * 23 planned_actdeptime
 * 24 planned_hrsenroute
 * 25 planned_minenroute
 * 26 planned_hrsfuel
 * 27 planned_minfuel
 * 28 planned_altairport
 * 29 planned_remarks
 * 30 planned_route
 * 31 planned_depairport_lat
 * 32 planned_depairport_lon
 * 33 planned_destairport_lat
 * 34 planned_destairport_lon
 * 35 atis_message
 * 36 time_last_atis_received
 * 37 time_logon
 * 38 heading
 * 39 QNH_iHg
 * 40 QNH_Mb
 */
Pilot::Pilot(const QStringList& _data, bool _prefiled) :
		altitude(_data[7].toInt()),
		groundSpeed(_data[8].toInt()),
		squawk(_data[17]),
		aircraft(_data[9]),
		tas(_data[10].toInt()),
		flightRules(_data[21] == "I" ? IFR : VFR),
		remarks(_data[29]),
		heading(_data[38].toUInt()),
		position({_data[5].toDouble(), _data[6].toDouble()}),
		route({_data[11].toUpper(), _data[13].toUpper(), _data[30], _data[12].toUpper()}),
		prefiledOnly(_prefiled),
		__callsignTip(0) {
	callsign = _data[0];
	pid = _data[1].toUInt();
	realName = _data[2].simplified();
	server = _data[14];
	onlineFrom = QDateTime::fromString(_data[37], "yyyyMMddhhmmss");
	
	if (!route.origin.isEmpty()) {
		AirportObject* ap = VatsimDataHandler::GetSingleton().addActiveAirport(route.origin);
		ap->addOutbound(this);
		
		if (prefiledOnly && ap->getData()) {
			position.latitude = ap->getData()->latitude;
			position.longitude = ap->getData()->longitude;
		}
		
		if (ap->getFirs()[0])
			ap->getFirs()[0]->addFlight(this);
		if (ap->getFirs()[1])
			ap->getFirs()[1]->addFlight(this);
	}
	
	if (!route.destination.isEmpty()) {
		AirportObject* ap = VatsimDataHandler::GetSingleton().addActiveAirport(route.destination);
		ap->addInbound(this);
		
		if (ap->getFirs()[0])
			ap->getFirs()[0]->addFlight(this);
		if (ap->getFirs()[1])
			ap->getFirs()[1]->addFlight(this);
	}
	
	__setMyStatus();
	//__generateTip();
	
	modelTexture = ModelsMatcher::GetSingleton().matchMyModel(aircraft);
}

Pilot::~Pilot() {
	if (__callsignTip)
		MapWidget::deleteImage(__callsignTip);
}

void
Pilot::__setMyStatus() {
	if (!route.origin.isEmpty() && !route.destination.isEmpty()) {
		const AirportRecord* ap_origin =
			VatsimDataHandler::GetSingleton().getActiveAirports()[route.origin]->getData();
		const AirportRecord* ap_arrival =
			VatsimDataHandler::GetSingleton().getActiveAirports()[route.destination]->getData();
		
		if ((ap_origin == ap_arrival) && (ap_origin != NULL)) // traffic pattern?
			if (groundSpeed < 50) {
				flightStatus = DEPARTING;
				return;
			}
		
		if (ap_origin)
			if ((VatsimDataHandler::calcDistance(ap_origin->longitude, ap_origin->latitude,
							    position.longitude, position.latitude) < PILOT_TO_AIRPORT) &&
					(groundSpeed < 50)) {
				flightStatus = DEPARTING;
				return;
			}
		
		if (ap_arrival)
			if ((VatsimDataHandler::calcDistance(ap_arrival->longitude, ap_arrival->latitude,
							     position.longitude, position.latitude) < PILOT_TO_AIRPORT) &&
					(groundSpeed < 50)) {
				flightStatus = ARRIVED;
				return;
			}
	} else { // no flight plan
		if (groundSpeed > 50) {
			flightStatus = AIRBORNE;
			return;
		}
		
		const AirportRecord* closest = NULL;
		qreal distance = 0.0;
		for (const AirportRecord& ap: AirportsDatabase::GetSingleton().getAirports()) {
			qreal temp = VatsimDataHandler::calcDistance(ap.longitude, ap.latitude,
								     position.longitude, position.latitude);
			if (((temp < distance) && closest) || !closest) {
				closest = &ap;
				distance = temp;
			}
		}
		
		if (closest) {
			if (distance > PILOT_TO_AIRPORT) {
				flightStatus = AIRBORNE;
				return;
			}
			
			route.origin = closest->icao;
			flightStatus = DEPARTING;
			return;
		}
	}
	
	flightStatus = AIRBORNE;
}

GLuint
Pilot::__generateTip() const {
	QImage temp(MapWidget::GetSingleton().getPilotToolTipBackground());
	QPainter painter(&temp);
	painter.setRenderHint(QPainter::TextAntialiasing);
	painter.setRenderHint(QPainter::SmoothPixmapTransform);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setFont(MapWidget::GetSingleton().getPilotFont());
	painter.setPen(QColor(PILOTS_LABELS_FONT_COLOR));
	QRect rectangle(0, 1, 75, 14); // size of the tooltip.png
	painter.drawText(rectangle, Qt::AlignCenter, callsign);
	__callsignTip = MapWidget::loadImage(temp);
	return __callsignTip;
}

