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
#include "blockremover.h"
#include "block.h"
#include "mindmap.h"

#include <QGraphicsScene>

BlockRemover::BlockRemover(const QByteArray &id, MindMap *listener)
: m_id(id), m_listener(listener)
{
	Block *node = m_listener->resolveNodeByID(m_id);
	if( node->parent())
		m_parent = node->parent()->id();
	m_pos = node->pos();
	foreach( Block *child, node->children())
	{
		m_children << child->id();
	}

	foreach( QString propertyName, node->propertyNames() )
	{
		m_properties[propertyName] = node->getProperty(propertyName);
	}
}


BlockRemover::~BlockRemover()
{}

void BlockRemover::removeBlock( )
{
	Block *node = m_listener->resolveNodeByID(m_id);

	m_listener->selectRootNode();

	node->detatch();
	m_listener->scene()->removeItem(node);
	delete node;
}

void BlockRemover::restoreBlock( )
{
	Block *parent = m_listener->resolveNodeByID(m_parent);
	Block *block = new Block();
	if( !m_id.isEmpty() )
		block->setId(m_id);
	m_listener->scene()->addItem(block);

	block->setPos( m_pos );
	block->setParentNode(parent);
	block->setMindmap(m_listener);

	foreach( QByteArray childId, m_children )
	{
		Block *child = m_listener->resolveNodeByID(childId);
		child->setParentNode(block);
	}

	foreach( QString propertyName, m_properties.keys() )
	{
		block->setProperty( propertyName, m_properties[propertyName] );
	}
	m_listener->clearSelection();
	block->setSelected(true);
	m_listener->itemSelectionChanged();
}


