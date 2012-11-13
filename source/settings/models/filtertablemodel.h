/*
    filtertablemodel.h
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


#ifndef FILTERTABLEMODEL_H
#define FILTERTABLEMODEL_H

#include <QAbstractTableModel>
#include <QFont>
#include <QVector>

#include "singleton.h"

class FilterRule;

class FilterTableModel :
    public QAbstractTableModel,
    public Singleton< FilterTableModel > {
  
  Q_OBJECT
  
public:
  explicit FilterTableModel(QObject* = 0);
  virtual ~FilterTableModel();
  
  int rowCount(const QModelIndex& = QModelIndex()) const;
  int columnCount(const QModelIndex& = QModelIndex()) const;
  QVariant data(const QModelIndex&, int = Qt::DisplayRole) const;
  
  inline FilterRule &
  getFilter(int _row) { return *__filters[_row]; }
  
  inline const FilterRule &
  getFilter(int _row) const { return *__filters[_row]; }
  
  enum Column {
    ActiveCheckBox = 0,
    Title = 1,
    EditButton = 2,
    DeleteButton = 3
  };
  
public slots:
  void newFilter();
  
private:
  QVector< FilterRule* > __filters;
  
  QFont __displayFont;
  
};

#endif // FILTERTABLEMODEL_H
