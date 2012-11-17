/*
    filterrule.h
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


#ifndef FILTERRULE_H
#define FILTERRULE_H

#include <QCoreApplication>
#include <QString>
#include <QVariant>

class Pilot;

class FilterRule {
  
  /*
   * This class contains one single filter rule.
   * It can, among others, filter planes by callsign, pilot name or
   * altitude.
   */
  
  Q_DECLARE_TR_FUNCTIONS(FilterRule);
  
public:
  
  enum FilterField {
    CALLSIGN_STARTS_WITH,
    CALLSIGN_ENDS_WITH,
    CALLSIGN_CONTAINS,
    
    ALTITUDE_ABOVE,
    ALTITUDE_BELOW,
    ALTITUDE_ABOUT
  };
  
  /**
   * Creates filter that matches rule to the given
   * field.
   * @param field Where to match the filter.
   * @param rule Rule to be matched.
   * @param active Is filter active or not? By default, it is.
   */
  FilterRule(FilterField, const QVariant&, bool = true);
  
  /**
   * Checks if the pilot matches the rule.
   * @param pilot Pilot the rule will be tested on.
   * @return True if pilot passes the test, otherwise - false.
   */
  bool matches(const Pilot*) const;
  
  /**
   * @return "Callsign ends with foo" etc etc.
   */
  QString getName() const;
  
  /**
   * Toogles filter active/inactive.
   */
  void toggle();
  
  /**
   * Checks whether the particular field is numeric (int) or not.
   * If not, it is string.
   * @param field Field to be checked.
   */
  static bool isNumeric(FilterField);
  
    
  inline bool
  isActive() const { return __active; }
  
  inline const QVariant &
  getRule() const { return __rule; }
  
  inline void
  setRule(const QVariant& _r) { __rule = _r; }
  
  inline FilterField
  getField() const { return __field; }
  
  inline void
  setField(FilterField _f) { __field = _f; }
  
private:
  QString __convertFieldToString() const;
  
  FilterField __field;
  QVariant    __rule;
  
  bool __active;
  
};

#endif // FILTERRULE_H
