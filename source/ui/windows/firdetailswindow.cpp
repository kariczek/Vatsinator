/*
    firdetailswindow.cpp
    Copyright (C) 2012  Michał Garapich michal@garapich.pl

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

#include "db/airportdatabase.h"
#include "db/firdatabase.h"

#include "modules/vatbookhandler.h"
#include "modules/models/bookedatctablemodel.h"

#include "ui/userinterface.h"

#include "ui/buttons/clientdetailsbutton.h"
#include "ui/buttons/showairportbutton.h"

#include "ui/windows/airportdetailswindow.h"
#include "ui/windows/atcdetailswindow.h"
#include "ui/windows/flightdetailswindow.h"

#include "vatsimdata/airport.h"
#include "vatsimdata/vatsimdatahandler.h"

#include "vatsimdata/client/controller.h"
#include "vatsimdata/client/pilot.h"

#include "vatsimdata/models/airporttablemodel.h"
#include "vatsimdata/models/controllertablemodel.h"
#include "vatsimdata/models/flighttablemodel.h"

#include "vatsinatorapplication.h"

#include "firdetailswindow.h"
#include "defines.h"

FirDetailsWindow::FirDetailsWindow(QWidget* _parent) :
    QWidget(_parent) {
  setupUi(this);
  UserInterface::setWindowPosition(this);

  connect(VatsinatorApplication::getSingletonPtr(), SIGNAL(dataUpdated()),
          this,                                     SLOT(__updateData()));
}

void
FirDetailsWindow::show(const Fir* _f) {
  __currentICAO = _f->getIcao();

  __fillLabels(_f);
  __updateModels(_f);
  __setFlightTableButtons();
  __setControllerTableButtons();
  __setAirportTableButtons();
  __adjustTables();

  QWidget::show();
}

void
FirDetailsWindow::__updateModels(const Fir* _f) {
  const Fir* f;

  if (!_f)
    f = FirDatabase::getSingleton().findFirByIcao(__currentICAO);
  else
    f = _f;

  Q_ASSERT(f);
  
  disconnect(this, SLOT(__setFlightTableButtons()));
  disconnect(this, SLOT(__setControllerTableButtons()));

  connect(_f->getFlightsModel(), SIGNAL(sorted()),
          this,                  SLOT(__setFlightTableButtons()));
  FlightsTable->setModel(_f->getFlightsModel());
  
  connect(_f->getStaffModel(),   SIGNAL(sorted()),
          this,                  SLOT(__setControllerTableButtons()));
  ATCTable->setModel(_f->getStaffModel());
  
  AirportsTable->setModel(_f->getAirportsModel());
  
  BookedATCTable->setModel(VatbookHandler::getSingleton().getModel(_f->getIcao()));
}

void
FirDetailsWindow::__fillLabels(const Fir* _f) {
  if (_f->getCountry() != "USA")
    setWindowTitle(_f->getIcao() + " - " + tr("FIR details"));
  else
    setWindowTitle(_f->getIcao() + " - " + tr("ARTCC details"));

  if (!_f->isOceanic())
    ICAOLabel->setText(_f->getIcao());
  else
    ICAOLabel->setText(_f->getIcao() + " Oceanic");

  NameLabel->setText(_f->getName());
}

void
FirDetailsWindow::__adjustTables() {
  FlightsTable->hideColumn(FlightTableModel::Name);
  // 150, 160, 160, 150, 120
  FlightsTable->setColumnWidth(FlightTableModel::Callsign, 150);
  FlightsTable->setColumnWidth(FlightTableModel::From, 160);
  FlightsTable->setColumnWidth(FlightTableModel::To, 160);
  FlightsTable->setColumnWidth(FlightTableModel::Aircraft, 150);

  ATCTable->setColumnWidth(ControllerTableModel::Callsign, 150);
  ATCTable->setColumnWidth(ControllerTableModel::Name, 320);
  ATCTable->setColumnWidth(ControllerTableModel::Frequency, 150);

  AirportsTable->setColumnWidth(AirportTableModel::Label, 250);
  AirportsTable->setColumnWidth(AirportTableModel::Facilities, 170);
  AirportsTable->setColumnWidth(AirportTableModel::Outbounds, 100);
  AirportsTable->setColumnWidth(AirportTableModel::Inbounds, 100);
  
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Callsign, 150);
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Name, 300);
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Date, 150);
  BookedATCTable->setColumnWidth(BookedAtcTableModel::Hours, 150);
}

void
FirDetailsWindow::__setFlightTableButtons() {
  const FlightTableModel* flightsModel = qobject_cast< const FlightTableModel* >(FlightsTable->model());
  Q_ASSERT(flightsModel);

  for (int i = 0; i < flightsModel->rowCount(); ++i) {
    if (flightsModel->getFlights()[i]->prefiledOnly)
      continue;

    ClientDetailsButton* pButton = new ClientDetailsButton(flightsModel->getFlights()[i]);
    connect(pButton,        SIGNAL(clicked(const Client*)),
            FlightDetailsWindow::getSingletonPtr(), SLOT(show(const Client*)));
    FlightsTable->setIndexWidget(flightsModel->index(i, FlightTableModel::Button), pButton);
  }
}

void
FirDetailsWindow::__setControllerTableButtons() {
  const ControllerTableModel* atcModel = qobject_cast< const ControllerTableModel* >(ATCTable->model());
  Q_ASSERT(atcModel);

  for (int i = 0; i < atcModel->rowCount(); ++i) {
    ClientDetailsButton* pButton = new ClientDetailsButton(atcModel->getStaff()[i]);
    connect(pButton,        SIGNAL(clicked(const Client*)),
            ATCDetailsWindow::getSingletonPtr(),  SLOT(show(const Client*)));
    ATCTable->setIndexWidget(atcModel->index(i, ControllerTableModel::Button), pButton);
  }
}

void
FirDetailsWindow::__setAirportTableButtons() {
  const AirportTableModel* apModel = qobject_cast< const AirportTableModel* >(AirportsTable->model());
  Q_ASSERT(apModel);

  for (int i = 0; i < apModel->rowCount(); ++i) {
    ShowAirportButton* pButton = new ShowAirportButton(apModel->getAirports()[i]);
    connect(pButton,        SIGNAL(clicked(const Airport*)),
            AirportDetailsWindow::getSingletonPtr(), SLOT(show(const Airport*)));
    AirportsTable->setIndexWidget(apModel->index(i, AirportTableModel::Button), pButton);
  }
}

void
FirDetailsWindow::__updateData() {
  if (__currentICAO.isEmpty() || !isVisible())
    return;

  __setFlightTableButtons();
  __setControllerTableButtons();
}




