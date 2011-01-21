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
#include "movecommand.h"
#include "block.h"
#include "mindmap.h"

#include <qdebug.h>

QString MoveCommandTextTemplate = "move \"%1\"";
MoveCommand::MoveCommand(const QByteArray &id,
                         const QPointF & delta,
                         MindMap *listener,
                         QUndoCommand * parent  )
: QUndoCommand(parent),m_id(id), m_listener(listener), m_delta(delta)
{
	Block *block = m_listener->resolveNodeByID(m_id);
	setText(MoveCommandTextTemplate.arg(block->title()));
}


MoveCommand::~MoveCommand()
{

}

void MoveCommand::undo( )
{
	Block *block = m_listener->resolveNodeByID(m_id);
	block->moveBy( -(m_delta.x()), -(m_delta.y()) );
	block->updateConnections();
}

void MoveCommand::redo( )
{
	Block *block = m_listener->resolveNodeByID(m_id);
	block->moveBy((m_delta.x()),(m_delta.y()));
	block->updateConnections();
}

int MoveCommand::id( ) const
{
	return 1024;
}

bool MoveCommand::mergeWith( const QUndoCommand * command )
{
	if ( command == 0)
		return false;

	if (command->id() != id())
		return false;

	const MoveCommand *cmd = dynamic_cast<const MoveCommand*>(command);

	if( cmd->m_id != m_id )
		return false;

	m_delta += cmd->m_delta;
	return true;
}


