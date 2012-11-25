/*
    metarlistview.cpp
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

#include "metarlistview.h"
#include "defines.h"

MetarListView::MetarListView(QWidget* _parent) :
    QListView(_parent),
    __searchBox(new QLineEdit(this)) {
  __searchBox->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
}

void
MetarListView::resizeEvent(QResizeEvent* _event) {
  __searchBox->move(_event->size().width() - __searchBox->width(),
                    _event->size().height() - __searchBox->height());
}
