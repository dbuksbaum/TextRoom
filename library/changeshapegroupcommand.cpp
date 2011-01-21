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
#include "changeshapegroupcommand.h"
#include "shapeselector.h"
#include "mindmap.h"
#include "block.h"

QString ChangeShapeGroupCommandTextTemplate = "change \"%1\" type";
QString ChangeShapeGroupCommandGroupTextTemplate = "change %1 items' type";

ChangeShapeGroupCommand::ChangeShapeGroupCommand( const QList<QByteArray> &ids, MindMap *listener )
	: QUndoCommand(), m_listener(listener)
{
	if( ids.count() == 1 )
	{
		Block *node = m_listener->resolveNodeByID(ids.at(0));
		setText(ChangeShapeGroupCommandGroupTextTemplate.arg(node->title()));
		m_newType = node->getProperty("shapetype").value<int>();
	}
	else
		setText( ChangeShapeGroupCommandTextTemplate.arg(ids.count()) );

	ShapeSelector selector( QApplication::activeWindow() );
	if( selector.exec () )
	{
		m_newType = selector.currentShapeType();
	}

	foreach( QByteArray id, ids )
	{
		Block *node = m_listener->resolveNodeByID(id);
		if( node )
		{
			m_type[id] = node->getProperty("shapetype").value<int>();
			node->setProperty("shapetype", m_newType);
		}
	}
}


ChangeShapeGroupCommand::~ChangeShapeGroupCommand()
{
}

void ChangeShapeGroupCommand::redo( )
{
	foreach( QByteArray key, m_type.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setProperty("shapetype", m_newType);
	}

}

void ChangeShapeGroupCommand::undo( )
{
	foreach( QByteArray key, m_type.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setProperty("shapetype", m_type[key]);
	}

}

int ChangeShapeGroupCommand::id() const
{
	return 1034;
}
