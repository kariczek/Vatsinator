/*
    filtertablemodel.cpp
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

#include "settings/filterrule.h"

#include "filtertablemodel.h"
#include "defines.h"

FilterTableModel::FilterTableModel(QObject* _parent) :
  QAbstractTableModel(_parent) {
  __displayFont.setBold(true);
}

FilterTableModel::~FilterTableModel() {
  qDeleteAll(__filters);
}

int
FilterTableModel::rowCount(const QModelIndex&) const {
  return __filters.size();
}

int
FilterTableModel::columnCount(const QModelIndex&) const {
  return 4;
}

QVariant
FilterTableModel::data(const QModelIndex& _index, int _role) const {
  if (!_index.isValid() || _index.row() >= rowCount() || _index.column() >= columnCount())
    return QVariant();
  
  switch (_role) {
    case Qt::TextAlignmentRole:
      return static_cast< int >(Qt::AlignLeft | Qt::AlignVCenter);
    case Qt::FontRole:
      return __displayFont;
    case Qt::DisplayRole:
      switch (_index.column()) {
        case FilterTableModel::ActiveCheckBox:
          return __filters[_index.row()]->isActive();
        case FilterTableModel::Title:
          return __filters[_index.row()]->getName();
      }
    default:
      return QVariant();
  }
}

void
FilterTableModel::addFilter(FilterRule* _rule) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  __filters.push_back(_rule);
  endInsertRows();
}

void
FilterTableModel::removeFilter(int _row) {
  Q_ASSERT(_row < __filters.size());
  
  beginRemoveRows(QModelIndex(), _row, _row);
  delete __filters[_row];
  __filters.remove(_row);
  endRemoveRows();
}

void
FilterTableModel::updateFilter(int _row, const FilterRule& _newRule) {
  Q_ASSERT(_row < __filters.size());
  
  __filters[_row]->setField(_newRule.getField());
  __filters[_row]->setRule(_newRule.getRule());
}

bool
FilterTableModel::matches(const Pilot* _p) {
  for (const FilterRule* fr: __filters)
    if (fr->matches(_p))
      return true;
  
  return false;
}


