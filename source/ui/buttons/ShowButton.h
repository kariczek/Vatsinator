/*
    ShowButton.h
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


#ifndef SHOWBUTTON_H
#define SHOWBUTTON_H

#include <QPushButton>

class Pilot;

class ShowButton : public QPushButton {
	
	/*
	 * This is the "Show" button for Airport Details Window.
	 * It centres the MapWidget's map on the particular pilot if clicked. 
	 */
	
	Q_OBJECT
	
public:
	ShowButton(const Pilot*, QWidget* = 0);
	
signals:
	void clicked(const Pilot*);
	
public slots:
	void handleClicked();
	
private:
	const Pilot * __current;
	
	
};

#endif // SHOWBUTTON_H