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
#include "reparentblockcommand.h"
#include "block.h"
#include  "mindmap.h"

#include <qdebug.h>

QString ReparentBlockCommandTextTemplate = "reparent \"%1\" to \"%2\"";
ReparentBlockCommand::ReparentBlockCommand(const QByteArray &parentId, const QByteArray &id, MindMap *listener)
: QUndoCommand(), m_listener(listener), m_newParentId(parentId), m_id(id)
{
	Block *child = m_listener->resolveNodeByID(m_id);
	Block *parent = m_listener->resolveNodeByID(m_newParentId);
	if(child->parent())
		m_oldParentId = child->parent()->id();
	setText(ReparentBlockCommandTextTemplate.arg(child->title()).arg(parent->title()));
}


ReparentBlockCommand::~ReparentBlockCommand()
{}


void ReparentBlockCommand::undo()
{
	Block *parent = m_listener->resolveNodeByID(m_oldParentId);
	Block *child = m_listener->resolveNodeByID(m_id);
	child->setParentNode(parent);
}

void ReparentBlockCommand::redo()
{
	Block *parent = m_listener->resolveNodeByID(m_newParentId);
	Block *child = m_listener->resolveNodeByID(m_id);
	child->setParentNode(parent);
}

