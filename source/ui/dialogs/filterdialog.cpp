/*
    filterdialog.cpp
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

#include "filterdialog.h"
#include "defines.h"

FilterDialog::FilterDialog(QWidget* _parent, const FilterRule* _rule) :
   QDialog(_parent) {
  setupUi(this);
  
  if (_rule) {
    switch (_rule->getField()) {
      case FilterRule::FilterField::CALLSIGN_STARTS_WITH:
        FieldBeginComboBox->setCurrentIndex(0);
        FieldEndComboBox->setCurrentIndex(0);
        break;
      case FilterRule::FilterField::CALLSIGN_CONTAINS:
        FieldBeginComboBox->setCurrentIndex(0);
        FieldEndComboBox->setCurrentIndex(1);
        break;
      case FilterRule::FilterField::CALLSIGN_ENDS_WITH:
        FieldBeginComboBox->setCurrentIndex(0);
        FieldEndComboBox->setCurrentIndex(2);
        break;
      default:
        break;
    }
    
    RuleLineEdit->setText(_rule->getRule());
  }
}

FilterRule::FilterField
FilterDialog::getField() const {
  switch (FieldBeginComboBox->currentIndex()) {
    case 0:
      switch (FieldEndComboBox->currentIndex()) {
        case 0:
          return FilterRule::FilterField::CALLSIGN_STARTS_WITH;
        case 1:
          return FilterRule::FilterField::CALLSIGN_CONTAINS;
        case 2:
          return FilterRule::FilterField::CALLSIGN_ENDS_WITH;
        default:
          return FilterRule::FilterField::CALLSIGN_STARTS_WITH;
      }
    default:
      return FilterRule::FilterField::CALLSIGN_STARTS_WITH;
  }
}
