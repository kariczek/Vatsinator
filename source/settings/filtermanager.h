/*
    filtermanager.h
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


#ifndef FILTERMANAGER_H
#define FILTERMANAGER_H

#include <QVector>
#include <QString>

#include "settings/filterrule.h"

#include "singleton.h"

class Pilot;

class FilterManager : public Singleton< FilterManager > {
  
  /*
   * This class contains all filters.
   */
  
public:
  FilterManager();
  virtual ~FilterManager();
  
  /**
   * Adds filter to the filter set.
   */
  void addFilter(FilterRule::FilterField, const QString&);
  
  /**
   * Goes through all the filters and checks every of them.
   * @param pilot A pilot to be checked.
   * @return True if pilot passes all the tests.
   */
  bool matches(const Pilot&) const;
  
private:
  QVector< FilterRule* > __filters;
  
  
};

#endif // FILTERMANAGER_H
