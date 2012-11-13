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

#include "settings/filterrule.h"

#include "filterdelegate.h"
#include "defines.h"

FilterDelegate::FilterDelegate(QObject* _parent) :
    QStyledItemDelegate(_parent) {
  __optDeleteButton.icon = QIcon(":/uiIcons/button-delete.png");
  __optEditButton.icon = QIcon(":/uiIcons/button-edit.png");
}

void
FilterDelegate::paint(QPainter* _painter, const QStyleOptionViewItem& _option,
                      const QModelIndex& _index) const {
  switch (_index.column()) {
    case FilterTableModel::Title:
      QStyledItemDelegate::paint(_painter, _option, _index);
      break;
    case FilterTableModel::ActiveCheckBox:
      QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                         __getStyleOptionCheckBox(
                                             _option,
                                             FilterTableModel::getSingleton().getFilter(_index.row()).isActive()),
                                         _painter);
      break;
    case FilterTableModel::DeleteButton:
      QApplication::style()->drawControl(QStyle::CE_PushButton,
                                         __getStyleOptionDeleteButton(
                                           _option),
                                         _painter);
      break;
    case FilterTableModel::EditButton:
      QApplication::style()->drawControl(QStyle::CE_PushButton,
                                         __getStyleOptionEditButton(
                                           _option),
                                         _painter);
      break;
  }
}

QSize
FilterDelegate::sizeHint(const QStyleOptionViewItem& _option,
                         const QModelIndex& _index) const {
  switch (_index.column()) {
    case FilterTableModel::ActiveCheckBox:
      return QApplication::style()->sizeFromContents(QStyle::CT_CheckBox,
                                                     &__optCheckBox,
                                                     QSize(3, 3)).
            expandedTo(QApplication::globalStrut());
    case FilterTableModel::DeleteButton:
      return QApplication::style()->sizeFromContents(QStyle::CT_PushButton,
                                                     &__optDeleteButton,
                                                     QSize(40, 25)).
            expandedTo(QApplication::globalStrut());
    
    case FilterTableModel::EditButton:
      return QApplication::style()->sizeFromContents(QStyle::CT_PushButton,
                                                     &__optEditButton,
                                                     QSize(40, 25)).
            expandedTo(QApplication::globalStrut());
    
    default:
      return QStyledItemDelegate::sizeHint(_option, _index);
  }
}

bool
FilterDelegate::editorEvent(QEvent* _event,
                            QAbstractItemModel*,
                            const QStyleOptionViewItem&,
                            const QModelIndex& _index) {
  if (_event->type() != QEvent::MouseButtonPress)
    return true;
  
  switch (_index.column()) {
    case FilterTableModel::ActiveCheckBox:
      FilterTableModel::getSingleton().getFilter(_index.row()).toggle();
      break;
    
    default:
      break;
  }
  
  return true;
}

const QStyleOptionButton *
FilterDelegate::__getStyleOptionCheckBox(const QStyleOptionViewItem& _option,
                                         bool _active) const {
  
  __optCheckBox.rect = QStyle::alignedRect(Qt::LayoutDirectionAuto,
                                           Qt::AlignCenter,
                                           QApplication::style()->subElementRect(
                                             QStyle::SE_CheckBoxIndicator, &__optCheckBox
                                           ).size(),
                                           _option.rect);
  
  __optCheckBox.state = QStyle::State_Enabled;
  
  if (_option.state & QStyle::State_HasFocus)
    __optCheckBox.state |= QStyle::State_HasFocus;
  
  if (_option.state & QStyle::State_MouseOver)
    __optCheckBox.state |= QStyle::State_MouseOver;
  
  if (_option.state & QStyle::State_Sunken)
    __optCheckBox.state |= QStyle::State_Sunken;
  
  __optCheckBox.state |= _active ? QStyle::State_On : QStyle::State_Off;
  
  
  return &__optCheckBox;
}

const QStyleOptionButton *
FilterDelegate::__getStyleOptionDeleteButton(const QStyleOptionViewItem& _option) const {
  __optDeleteButton.rect = QStyle::alignedRect(Qt::LayoutDirectionAuto,
                                               Qt::AlignCenter,
                                               QSize(40, 25),
                                               _option.rect);
 
  __optDeleteButton.state = QStyle::State_Enabled;
  
  if (_option.state & QStyle::State_HasFocus)
    __optDeleteButton.state |= QStyle::State_HasFocus;

  if (_option.state & QStyle::State_MouseOver)
    __optDeleteButton.state |= QStyle::State_MouseOver;
  
  if (_option.state & QStyle::State_Sunken)
    __optDeleteButton.state |= QStyle::State_Sunken;
  
  
  return &__optDeleteButton;
}

const QStyleOptionButton *
FilterDelegate::__getStyleOptionEditButton(const QStyleOptionViewItem& _option) const {
  __optEditButton.rect = QStyle::alignedRect(Qt::LayoutDirectionAuto,
                                               Qt::AlignCenter,
                                               QSize(40, 25),
                                               _option.rect);
 
  __optEditButton.state = QStyle::State_Enabled;
  
  if (_option.state & QStyle::State_HasFocus)
    __optEditButton.state |= QStyle::State_HasFocus;

  if (_option.state & QStyle::State_MouseOver)
    __optEditButton.state |= QStyle::State_MouseOver;
  
  if (_option.state & QStyle::State_Sunken)
    __optEditButton.state |= QStyle::State_Sunken;
  
  
  return &__optEditButton;
}
