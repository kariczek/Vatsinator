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

QStringListModel FilterDialog::__fieldBeginModel(QStringList({
    QT_TRANSLATE_NOOP("FilterDialog", "callsign"),
    QT_TRANSLATE_NOOP("FilterDialog", "altitude")
  }));
  
QStringListModel FilterDialog::__fieldCallsignModel(QStringList({
    QT_TRANSLATE_NOOP("FilterDialog", "starts with"),
    QT_TRANSLATE_NOOP("FilterDialog", "contains"),
    QT_TRANSLATE_NOOP("FilterDialog", "ends with")
  }));

QStringListModel FilterDialog::__fieldAltitudeModel(QStringList({
    QT_TRANSLATE_NOOP("FilterDialog", "above"),
    QT_TRANSLATE_NOOP("FilterDialog", "below"),
    QT_TRANSLATE_NOOP("FilterDialog", "about")
  }));

FilterDialog::FilterDialog(QWidget* _parent, const FilterRule* _rule) :
   QDialog(_parent) {
  setupUi(this);
  
  __ruleLineEdit = new QLineEdit();
  RuleEdit->addWidget(__ruleLineEdit);
  
  __ruleSpinBox = new QSpinBox();
  __ruleSpinBox->setSuffix(" " % tr("feet"));
  __ruleSpinBox->setSingleStep(1000);
  __ruleSpinBox->setRange(0, 100000);
  __ruleSpinBox->setValue(1000);
  RuleEdit->addWidget(__ruleSpinBox);
  
  FieldBeginComboBox->setModel(&__fieldBeginModel);
  FieldEndComboBox->setModel(&__fieldCallsignModel);
  
    
  connect(FieldBeginComboBox,      SIGNAL(currentIndexChanged(int)),
          this,                    SLOT(__handleIndexChange(int)));
  
  if (_rule) {
    switch (_rule->getField()) {
      case FilterRule::FilterField::CALLSIGN_STARTS_WITH:
        FieldBeginComboBox->setCurrentIndex(0);
        FieldEndComboBox->setCurrentIndex(0);
        __ruleLineEdit->setText(_rule->getRule().toString());
        break;
        
      case FilterRule::FilterField::CALLSIGN_CONTAINS:
        FieldBeginComboBox->setCurrentIndex(0);
        FieldEndComboBox->setCurrentIndex(1);
        __ruleLineEdit->setText(_rule->getRule().toString());
        break;
        
      case FilterRule::FilterField::CALLSIGN_ENDS_WITH:
        FieldBeginComboBox->setCurrentIndex(0);
        FieldEndComboBox->setCurrentIndex(2);
        __ruleLineEdit->setText(_rule->getRule().toString());
        break;
        
      case FilterRule::FilterField::ALTITUDE_ABOVE:
        FieldBeginComboBox->setCurrentIndex(1);
        FieldEndComboBox->setCurrentIndex(0);
        __ruleSpinBox->setValue(_rule->getRule().toInt());
        break;
        
      case FilterRule::FilterField::ALTITUDE_BELOW:
        FieldBeginComboBox->setCurrentIndex(1);
        FieldEndComboBox->setCurrentIndex(1);
        __ruleSpinBox->setValue(_rule->getRule().toInt());
        break;
        
      case FilterRule::FilterField::ALTITUDE_ABOUT:
        FieldBeginComboBox->setCurrentIndex(1);
        FieldEndComboBox->setCurrentIndex(2);
        __ruleSpinBox->setValue(_rule->getRule().toInt());
        break;
        
      default:
        break;
    } 
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
      }
    case 1:
      switch (FieldEndComboBox->currentIndex()) {
        case 0:
          return FilterRule::FilterField::ALTITUDE_ABOVE;
        case 1:
          return FilterRule::FilterField::ALTITUDE_BELOW;
        case 2:
          return FilterRule::FilterField::ALTITUDE_ABOUT;
      }
  }
  
  return FilterRule::FilterField::CALLSIGN_STARTS_WITH;
}

QVariant
FilterDialog::getRule() const {
  if (FilterRule::isNumeric(getField()))
    return __ruleSpinBox->value();
  else
    return __ruleLineEdit->text().toUpper();
}

void
FilterDialog::__handleIndexChange(int _index) {
  switch (_index) {
    case 0:
      FieldEndComboBox->setModel(&__fieldCallsignModel);
      RuleEdit->setCurrentWidget(__ruleLineEdit);
      break;
    case 1:
      FieldEndComboBox->setModel(&__fieldAltitudeModel);
      RuleEdit->setCurrentWidget(__ruleSpinBox);
      break;
    default:
      break;
  }
}
