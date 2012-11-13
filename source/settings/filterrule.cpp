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

FilterRule::FilterRule(FilterRule::FilterField _field, const QString& _rule) :
    __field(_field),
    __rule(_rule),
    __active(false) {}

bool
FilterRule::matches(const Pilot& _pilot) const {
  switch (__field) {
    case CALLSIGN_STARTS_WITH:
      return _pilot.callsign.startsWith(__rule);
    case CALLSIGN_ENDS_WITH:
      return _pilot.callsign.endsWith(__rule);
    case CALLSIGN_CONTAINS:
      return _pilot.callsign.contains(__rule);
  }
  
  return false;
}

QString
FilterRule::getName() const {
  return __convertFieldToString() % " " % __rule;
}

void
FilterRule::toggle() {
  __active = !__active;
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
    default:
      return QString();
  }
}
