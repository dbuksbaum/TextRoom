/***************************************************************************
 *   Copyright (C) 2006-2008 by Ian Reinhart Geiser                        *
 *   geiseri@yahoo.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "titleeditor.h"
#include "blockpropertymodel.h"

#include <QKeyEvent>

TitleEditor::TitleEditor(QWidget *parent)
: QLineEdit(parent), m_isEditing(false)
{
	connect( this, SIGNAL(editingFinished()), this, SLOT(setNewBlockTitle()));
}


TitleEditor::~TitleEditor()
{}

void TitleEditor::setPropertyModel(BlockPropertyModel* theValue)
{
	m_propertyModel = theValue;
}

void TitleEditor::setNewBlockTitle( )
{
	if( m_propertyModel->data(m_propertyModel->indexForProperty("title"),
	                          Qt::EditRole).toString() != text() )
	{
		m_propertyModel->setData(m_propertyModel->indexForProperty("title"),
	                         text(),
	                         Qt::EditRole);
		qDebug("here");

	}
	m_isEditing = false;
	qobject_cast<QWidget*>(parent())->setFocus();
	deleteLater();
}

void TitleEditor::startEditing( )
{
	if( m_isEditing == false)
	{
		setText(
				m_propertyModel->data(m_propertyModel->indexForProperty("title"),
									Qt::EditRole).toString()
			);
		show();
		setFocus();
		selectAll();
	}
	m_isEditing = true;
}

void TitleEditor::keyPressEvent( QKeyEvent * event )
{
	if( event->key() == Qt::Key_Escape )
	{
		setText(
		         m_propertyModel->data(m_propertyModel->indexForProperty("title"),
		                               Qt::EditRole).toString()
		       );
		m_isEditing = false;
		qobject_cast<QWidget*>(parent())->setFocus();
		event->accept();
		deleteLater();
	}
	else
		QLineEdit::keyPressEvent( event );
}


bool TitleEditor::isEditing() const
{
	return m_isEditing;
}


void TitleEditor::setIsEditing(bool theValue)
{
	m_isEditing = theValue;
}
