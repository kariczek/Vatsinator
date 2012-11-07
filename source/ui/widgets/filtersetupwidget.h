/*
    filtersetupwidget.h
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


#ifndef FILTERSETUPWIDGET_H
#define FILTERSETUPWIDGET_H

#include <QWidget>

class FilterSetupWidget : public QWidget {
  
  /*
   * This is the widget visible in SettingsWindow, in Filters page.
   * FilterSetupWidget lets user design a working filter.
   */
  
  Q_OBJECT
  
public:
  FilterSetupWidget(QWidget* = 0);
  
  
  
  
};

#endif // FILTERSETUPWIDGET_H
