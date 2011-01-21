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
#include "movegroupcommand.h"
#include "movecommand.h"
MoveGroupCommand::MoveGroupCommand(const QList<QByteArray> &ids,
                                   const QPointF & delta,
                                   MindMap *listener)
	: QUndoCommand()
{
	setText( "move group" );
	foreach( QByteArray id, ids)
		m_children[id] = new MoveCommand(id, delta, listener, this);
}


MoveGroupCommand::~MoveGroupCommand()
{

}


bool MoveGroupCommand::mergeWith(const QUndoCommand* other)
{
	if (other->id() != id())
		return false;

	const MoveGroupCommand *cmd = dynamic_cast<const MoveGroupCommand*>(other);

	if( cmd == 0 )
		return false;

	foreach( QByteArray childId, m_children.keys() )
	{
		QUndoCommand *childNode = m_children[childId];
		QUndoCommand *otherChildNode = cmd->m_children[childId];
		if( childNode == 0 || otherChildNode == 0)
			return false;
		if( childNode->mergeWith(otherChildNode) == false)
			return false;
	}
	return true;
}

int MoveGroupCommand::id() const
{
	return 1025;
}


