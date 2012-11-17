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
  
  __mouse.down = false;
}

void
FilterDelegate::paint(QPainter* _painter, const QStyleOptionViewItem& _option,
                      const QModelIndex& _index) const {
  switch (_index.column()) {
    case FilterTableModel::Title:
      QStyledItemDelegate::paint(_painter, _option, _index);
      break;
    
    case FilterTableModel::ActiveCheckBox:
      /* Checkbox is smaller than _option.rect. Get the real size */
      __optCheckBox.rect = QStyle::alignedRect(Qt::LayoutDirectionAuto,
                                               Qt::AlignCenter,
                                               QApplication::style()->subElementRect(
                                                 QStyle::SE_CheckBoxIndicator, &__optCheckBox
                                               ).size(),
                                               _option.rect);
  
      __optCheckBox.state = QStyle::State_Enabled;
      
      if (_option.state & QStyle::State_HasFocus)
        __optCheckBox.state |= QStyle::State_HasFocus;
  
      if (__optCheckBox.rect.contains(__mouse.position)) {
        __optCheckBox.state |= QStyle::State_MouseOver;
        if (__mouse.down)
          __optCheckBox.state |= QStyle::State_Sunken;
      }
  
      /* Checked or unchecked */
      __optCheckBox.state |= _index.data().toBool() ? QStyle::State_On : QStyle::State_Off;
      
      QApplication::style()->drawControl(QStyle::CE_CheckBox,
                                         &__optCheckBox,
                                         _painter);
      break;
    
    case FilterTableModel::DeleteButton:
      __optDeleteButton.rect = QStyle::alignedRect(Qt::LayoutDirectionAuto,
                                                   Qt::AlignCenter,
                                                   QSize(40, 25),
                                                   _option.rect);
       
      __optDeleteButton.state = QStyle::State_Enabled;
      
      if (_option.state & QStyle::State_HasFocus)
        __optDeleteButton.state |= QStyle::State_HasFocus;
      
      if (__optDeleteButton.rect.contains(__mouse.position)) {
        __optDeleteButton.state |= QStyle::State_MouseOver;
        if (__mouse.down)
          __optDeleteButton.state |= QStyle::State_Sunken;
      }
      
      QApplication::style()->drawControl(QStyle::CE_PushButton,
                                         &__optDeleteButton,
                                         _painter);
      break;
    
    case FilterTableModel::EditButton:
      __optEditButton.rect = QStyle::alignedRect(Qt::LayoutDirectionAuto,
                                                 Qt::AlignCenter,
                                                 QSize(40, 25),
                                                 _option.rect);
     
      __optEditButton.state = QStyle::State_Enabled;
      
      if (_option.state & QStyle::State_HasFocus)
        __optEditButton.state |= QStyle::State_HasFocus;
    
      if (__optEditButton.rect.contains(__mouse.position)) {
        __optEditButton.state |= QStyle::State_MouseOver;
        if (__mouse.down)
          __optEditButton.state |= QStyle::State_Sunken;
      }
      
      QApplication::style()->drawControl(QStyle::CE_PushButton,
                                         &__optEditButton,
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
      return QSize(44, 25);
      
    case FilterTableModel::EditButton:
      return QSize(44, 25);
    
    default:
      return QStyledItemDelegate::sizeHint(_option, _index);
  }
}

bool
FilterDelegate::editorEvent(QEvent* _event,
                            QAbstractItemModel* _model,
                            const QStyleOptionViewItem&,
                            const QModelIndex& _index) {
  
  switch (_event->type()) {
    case QEvent::MouseButtonRelease:
      __mouse.down = false;
      emit activated(_index);
      break;
      
    case QEvent::MouseButtonPress:
      __mouse.down = true;
      break;
      
    case QEvent::MouseMove:
      __mouse.position = static_cast< QMouseEvent* >(_event)->pos();
      break;
    
    default:
      break;
  }
  
  _event->accept();
  
  return true;
}
