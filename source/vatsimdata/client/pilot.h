/*
    pilot.h
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


#ifndef PILOT_H
#define PILOT_H

#include <QStringList>
#include <QString>

#include <QtOpenGL>

#include "vatsimdata/clickable.h"
#include "vatsimdata/client.h"

enum FlightRules {
  IFR, VFR
};

enum Status {
  DEPARTING,
  AIRBORNE,
  ARRIVED
};

class Pilot : public Client, public Clickable {

  /**
   * This class contains info about one particular pilot - his
   * flight plan, actual position, plane, etc etc.
   * TODO: Flight plan parsing (starting by NATs, may even include the AIRAC later).
   */

public:
  /**
   * @param list Data.
   * @param prefiled Indicates whether the flight is only prefiled.
   */
  Pilot(const QStringList&, bool = false);
  virtual ~Pilot();

  void drawLineFrom() const;
  void drawLineTo() const;

  inline void
  drawLines() const { drawLineFrom(); drawLineTo(); }

  inline Client::Type
  clientType() const { return Client::PILOT; }
  
  inline Clickable::Type
  objectType() const { return Clickable::PLANE; }

  inline GLuint
  getCallsignTip() const { return __callsignTip ? __callsignTip : __generateTip(); }
  
  inline bool
  matchesFilters() const { return __matchesFilters; }

  int   altitude;
  int   groundSpeed;
  QString   squawk;

  QString   aircraft;

  int   tas;

  FlightRules flightRules;

  QString   remarks;

  unsigned  heading;
  
  struct {
    QString ihg;
    QString mb;
  } pressure;

  Status    flightStatus;

  struct {
    QString origin;
    QString destination;
    QString route;
    QString altitude;
  } route;

  GLuint  modelTexture;

  bool prefiledOnly;

private:
  /**
   * Checks whether pilot is departing, airborn or has just arrived.
   */
  void __setMyStatus();

  /**
   * Generates in/out lines.
   */
  void __generateLines();

  /**
   * Generates the callsign label.
   */
  GLuint __generateTip() const;

  GLfloat* __lineFrom;
  GLfloat* __lineTo;

  mutable GLuint __callsignTip;
  
  /* Indicates whether pilot matches all filters or not */
  bool __matchesFilters;

};

#endif // PILOT_H
