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
#include "changecolorgroupcommand.h"
#include "block.h"
#include "mindmap.h"

#include <QApplication>
#include <QColorDialog>

QString ChangeColorCommandTextTemplate = "color \"%1\"";
QString ChangeColorGroupCommandTextTemplate = "color %1 items";
ChangeColorGroupCommand::ChangeColorGroupCommand( const QList<QByteArray> &ids, MindMap *listener )
	: QUndoCommand(), m_listener(listener)
{
	if( ids.count() == 1 )
	{
		Block *node = m_listener->resolveNodeByID(ids.at(0));
		setText(ChangeColorCommandTextTemplate.arg(node->title()));
	}
	else
		setText( ChangeColorGroupCommandTextTemplate.arg(ids.count()) );

	m_newColor = QColorDialog::getColor( m_newColor, QApplication::activeWindow() );

	foreach( QByteArray id, ids )
	{
		Block *node = m_listener->resolveNodeByID(id);
		if( node )
		{
			m_colors[id] = node->getProperty("color").value<QColor>();
			node->setProperty("color", m_newColor);
		}
	}
}


ChangeColorGroupCommand::~ChangeColorGroupCommand()
{
}

void ChangeColorGroupCommand::redo( )
{
	foreach( QByteArray key, m_colors.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setProperty("color", m_newColor);
		block->updateConnections();
	}

}

void ChangeColorGroupCommand::undo( )
{
	foreach( QByteArray key, m_colors.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setProperty("color", m_colors[key]);
		block->updateConnections();
	}

}

int ChangeColorGroupCommand::id( ) const
{
	return 1032;
}


