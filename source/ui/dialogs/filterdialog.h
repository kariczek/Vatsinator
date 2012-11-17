/*
    filterdialog.h
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


#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include "settings/filterrule.h"
#include "ui/ui_filterdialog.h"

class FilterDialog : public QDialog, private Ui::FilterDialog {
  
  Q_OBJECT
  
public:
  FilterDialog(QWidget* = 0, const FilterRule* = 0);
  
  FilterRule::FilterField getField() const;
  
  inline QString
  getRule() const { return RuleLineEdit->text().toUpper(); }
  
};

#endif // FILTERDIALOG_H
