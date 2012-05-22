/*
    FlightsListWindow.h
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


#ifndef FLIGHTSLISTWINDOW_H
#define FLIGHTSLISTWINDOW_H

#include "ui/ui_FlightsListWindow.h"
#include "Singleton.h"

class FlightsListWindow : public QWidget, public Singleton< FlightsListWindow >, private Ui::FlightsListWindow {
	
	Q_OBJECT
	
	
};

#endif // FLIGHTSLISTWINDOW_H