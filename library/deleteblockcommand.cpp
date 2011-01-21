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
#include "deleteblockcommand.h"
#include "mindmap.h"
#include "block.h"

#include <QGraphicsScene>

QString DeleteBlockCommandTextTemplate = "remove \"%1\"";
DeleteBlockCommand::DeleteBlockCommand(const QByteArray &id, MindMap *listener, QUndoCommand *parent)
: BlockRemover(id, listener), QUndoCommand(parent), m_id(id), m_listener(listener)
{
	Block *node = m_listener->resolveNodeByID(m_id);
	setText(DeleteBlockCommandTextTemplate.arg(node->title()));
}

DeleteBlockCommand::~DeleteBlockCommand()
{

}

void DeleteBlockCommand::redo()
{
	removeBlock();
}

void DeleteBlockCommand::undo()
{
	restoreBlock();
}

int DeleteBlockCommand::id( ) const
{
	return 1029;
}

