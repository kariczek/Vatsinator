/*
    filterdelegate.h
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


#ifndef FILTERDELEGATE_H
#define FILTERDELEGATE_H

#include <QStyledItemDelegate>

class FilterDelegate : public QStyledItemDelegate {
  
  Q_OBJECT
  
public:
  explicit FilterDelegate(QObject* = 0);
  
  void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
  
  QSize sizeHint(const QStyleOptionViewItem&,const QModelIndex&) const;
  
  bool editorEvent(QEvent*, QAbstractItemModel*, const QStyleOptionViewItem&, const QModelIndex&);
  
private:
  const QStyleOptionButton* __getStyleOptionCheckBox(const QStyleOptionViewItem&, bool) const;
  const QStyleOptionButton* __getStyleOptionDeleteButton(const QStyleOptionViewItem&) const;
  const QStyleOptionButton* __getStyleOptionEditButton(const QStyleOptionViewItem&) const;
  
  mutable QStyleOptionButton __optCheckBox;
  mutable QStyleOptionButton __optDeleteButton;
  mutable QStyleOptionButton __optEditButton;
  
};

#endif // FILTERDELEGATE_H
