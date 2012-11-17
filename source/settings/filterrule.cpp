/*
    filterrule.cpp
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

#include "vatsimdata/client/pilot.h"

#include "filterrule.h"
#include "defines.h"

FilterRule::FilterRule(FilterRule::FilterField _field, const QVariant& _rule, bool _active) :
    __field(_field),
    __rule(_rule),
    __active(_active) {}

bool
FilterRule::matches(const Pilot* _pilot) const {
  if (!__active)
    return false;
  
  switch (__field) {
    case CALLSIGN_STARTS_WITH:
      return _pilot->callsign.startsWith(__rule.toString());
    case CALLSIGN_ENDS_WITH:
      return _pilot->callsign.endsWith(__rule.toString());
    case CALLSIGN_CONTAINS:
      return _pilot->callsign.contains(__rule.toString());
    case ALTITUDE_ABOVE:
      return _pilot->altitude > __rule.toInt();
    case ALTITUDE_BELOW:
      return _pilot->altitude < __rule.toInt();
    case ALTITUDE_ABOUT:
      return (_pilot->altitude > __rule.toInt() - 1000) && (_pilot->altitude < __rule.toInt() + 1000);
  }
  
  return false;
}

QString
FilterRule::getName() const {
  switch (__field) {
    case CALLSIGN_STARTS_WITH:
    case CALLSIGN_ENDS_WITH:
    case CALLSIGN_CONTAINS:
      return __convertFieldToString() % " " % __rule.toString();
    case ALTITUDE_ABOVE:
    case ALTITUDE_BELOW:
    case ALTITUDE_ABOUT:
      return __convertFieldToString() % " " % QString::number(__rule.toInt()) % " " % tr("feet");
  }
  
  return "";
}

void
FilterRule::toggle() {
  __active = !__active;
}

bool
FilterRule::isNumeric(FilterRule::FilterField _field) {
  switch (_field) {
    case CALLSIGN_STARTS_WITH:
    case CALLSIGN_ENDS_WITH:
    case CALLSIGN_CONTAINS:
      return false;
    case ALTITUDE_ABOVE:
    case ALTITUDE_BELOW:
    case ALTITUDE_ABOUT:
      return true;
  }
  
  return false;
}

QString
FilterRule::__convertFieldToString() const {
  switch (__field) {
    case CALLSIGN_STARTS_WITH:
      return tr("Callsign starts with");
    case CALLSIGN_ENDS_WITH:
      return tr("Callsign ends with");
    case CALLSIGN_CONTAINS:
      return tr("Callsign contains");
    case ALTITUDE_ABOVE:
      return tr("Altitude above");
    case ALTITUDE_BELOW:
      return tr("Altitude below");
    case ALTITUDE_ABOUT:
      return tr("Altitude about");
    default:
      return QString();
  }
}
