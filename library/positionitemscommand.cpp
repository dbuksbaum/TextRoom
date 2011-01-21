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
#include "positionitemscommand.h"
#include "mindmap.h"
#include "block.h"

#include <QGraphicsScene>

PositionItemsCommand::PositionItemsCommand( MindMap *listener)
		: QUndoCommand(), m_listener(listener)
{
	setText("layout mindmap");
	foreach( QGraphicsItem *item, listener->scene()->items() )
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
			m_oldPositions[ block->id() ] = block->pos();
	}

	listener->placeChildren();

	foreach( QGraphicsItem *item, listener->scene()->items() )
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
			m_newPositions[ block->id() ] = block->pos();
	}
}


PositionItemsCommand::~PositionItemsCommand()
{
}

void PositionItemsCommand::undo( )
{
	foreach( QByteArray key, m_oldPositions.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setPos( m_oldPositions[ key ] );
		block->updateConnections();
	}
}

void PositionItemsCommand::redo( )
{
	foreach( QByteArray key, m_newPositions.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setPos( m_newPositions[ key ] );
		block->updateConnections();
	}
}

int PositionItemsCommand::id( ) const
{
	return 1031;
}


