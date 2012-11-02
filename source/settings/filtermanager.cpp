/*
    filtermanager.cpp
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

#include "filtermanager.h"
#include "defines.h"

FilterManager::FilterManager() {}

FilterManager::~FilterManager() {
  qDeleteAll(__filters);
}

void
FilterManager::addFilter(FilterRule::FilterField _field, const QString& _rule) {
  __filters.push_back(new FilterRule(_field, _rule));
}

bool
FilterManager::matches(const Pilot& _pilot) const {
  for (const FilterRule* fr: __filters)
    if (!fr->matches(_pilot))
      return false;
  
  return true;
}
