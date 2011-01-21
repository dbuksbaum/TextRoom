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
#include "editblockpropertycommand.h"
#include "block.h"
#include "mindmap.h"

QString EditBlockPropertyCommandTextTemplate = "modify \"%1\" on \"%2\"";
EditBlockPropertyCommand::EditBlockPropertyCommand(const QByteArray &id, const QString &propName,
	const QVariant &propValue, MindMap *listener)
: QUndoCommand(),m_id(id), m_listener(listener), m_property(propName), m_newProperty(propValue)
{
	Block *block = m_listener->resolveNodeByID(m_id);
	m_oldProperty = block->getProperty(m_property);
	setText(EditBlockPropertyCommandTextTemplate.arg(m_property).arg(block->title()));
}


EditBlockPropertyCommand::~EditBlockPropertyCommand()
{

}

bool EditBlockPropertyCommand::mergeWith( const QUndoCommand * command )
{
	if (command->id() != id())
		return false;

	const EditBlockPropertyCommand *cmd = dynamic_cast<const EditBlockPropertyCommand*>(command);

	if( cmd == 0 )
		return false;

	if( cmd->m_property != m_property )
		return false;
	m_newProperty = cmd->m_newProperty;
	return true;
}

int EditBlockPropertyCommand::id( ) const
{
	return 1025;
}

void EditBlockPropertyCommand::undo( )
{
	Block *block = m_listener->resolveNodeByID(m_id);
	block->setProperty( m_property, m_oldProperty );
}

void EditBlockPropertyCommand::redo( )
{
	Block *block = m_listener->resolveNodeByID(m_id);
	m_oldProperty = block->getProperty( m_property );
	block->setProperty( m_property, m_newProperty );
}




