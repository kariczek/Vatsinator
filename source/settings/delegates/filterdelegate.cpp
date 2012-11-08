/*
    filterdelegate.cpp
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

#include "settings/models/filtertablemodel.h"

#include "filterdelegate.h"
#include "defines.h"

FilterDelegate::FilterDelegate(QObject* _parent) :
    QStyledItemDelegate(_parent) {}

void
FilterDelegate::paint(QPainter* _painter, const QStyleOptionViewItem& _option,
                      const QModelIndex& _index) const {
  switch (_index.column()) {
    case FilterTableModel::Title:
      QStyledItemDelegate::paint(_painter, _option, _index);
      break;
    case FilterTableModel::Active:
      QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                         __getStyleOptionCheckBox(_option, false),
                                         _painter);
      break;
  }
}

QSize
FilterDelegate::sizeHint(const QStyleOptionViewItem& _option,
                         const QModelIndex& _index) const {
  switch (_index.column()) {
    case FilterTableModel::Title:
      return QStyledItemDelegate::sizeHint(_option, _index);
    case FilterTableModel::Active:
      return QApplication::style()->sizeFromContents(QStyle::CT_CheckBox,
                                                     __getStyleOptionCheckBox(false),
                                                     QSize(3, 3)).
            expandedTo(QApplication::globalStrut());
    default:
      return QStyledItemDelegate::sizeHint(_option, _index);
  }
}

const QStyleOptionButton *
FilterDelegate::__getStyleOptionCheckBox(const QStyleOptionViewItem& _option,
                                         bool _active) const {
  QCheckBox tempCheckBox;
  tempCheckBox.setChecked(_active ? Qt::Checked : Qt::Unchecked);
  
  __optChkBox.initFrom(&tempCheckBox);
  __optChkBox.rect = _option.rect;
  
  return &__optChkBox;
}

const QStyleOptionButton *
FilterDelegate::__getStyleOptionCheckBox(bool _active) const {
  QCheckBox tempCheckBox;
  tempCheckBox.setChecked(_active ? Qt::Checked : Qt::Unchecked);
  
  __optChkBox.initFrom(&tempCheckBox);
  
  return &__optChkBox;
}
