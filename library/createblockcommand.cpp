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
#include "createblockcommand.h"
#include "block.h"
#include "mindmap.h"

#include <QGraphicsScene>

CreateBlockCommand::CreateBlockCommand( const QByteArray &parentId, const QPointF & pos, MindMap *listener )
: QUndoCommand(), m_parentId(parentId), m_listener(listener), m_pos(pos)

{
	setText("new idea");
}


CreateBlockCommand::~CreateBlockCommand()
{}

void CreateBlockCommand::undo( )
{
	Block *block = m_listener->resolveNodeByID(m_id);

	m_listener->selectRootNode();

	m_pos = block->pos();
	block->detatch();
	m_listener->scene()->removeItem(block);
	delete block;

}

void CreateBlockCommand::redo( )
{
	Block *root = m_listener->root();
	Block *parent = m_listener->resolveNodeByID(m_parentId);
	Block *block = new Block();
	if( !m_id.isEmpty() )
		block->setId(m_id);
	m_listener->scene()->addItem(block);

	block->setParentNode(parent);

	block->updateContents();
	parent->updateContents();

	block->setTitle(QString("New idea %1").arg(block->index()));
	block->setMindmap(m_listener);

		if( m_pos.isNull() )
	{
		qreal xpos = 0.0;
		qreal ypos = parent->pos().y();
		if( parent->pos().x() > root->pos().x() )
		{
			xpos = parent->calculateNewXPos(block, true);
		}
		else
		{
			xpos = parent->calculateNewXPos(block, false);
		}
		if( parent->pos().y() > root->pos().y() )
		{
			ypos += parent->recursiveChildHeight();
		}
		else
		{
			ypos -= parent->recursiveChildHeight();
		}
		block->setPos( xpos, ypos );

	}
	else
		block->setPos( m_pos );


	m_id = block->id();
	m_listener->clearSelection();
	block->setSelected(true);
	m_listener->itemSelectionChanged();
}

int CreateBlockCommand::id( ) const
{
	return 1027;
}
