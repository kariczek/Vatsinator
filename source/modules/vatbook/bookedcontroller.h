/*
    bookedcontroller.h
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


#ifndef BOOKEDCONTROLLER_H
#define BOOKEDCONTROLLER_H

#include <QDate>
#include <QTime>
#include <QString>
#include <QStringList>

class BookedController {
  
public:
  BookedController() = delete;
  BookedController(const QStringList&);
  
  QString getIcao() const;
  
  QString callsign;
  QString realName;
  
  bool trainingSession;
  
  QDate dateBooked;
  QTime bookedFrom;
  QTime bookedTo;
  
};

#endif // BOOKEDCONTROLLER_H
