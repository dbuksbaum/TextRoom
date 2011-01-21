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
#include "changefontgroupcommand.h"
#include "mindmap.h"
#include "block.h"

#include <QFontDialog>
#include <QApplication>

QString ChangeFontGroupCommandTextTemplate = "change \"%1\" font";
QString ChangeFontGroupCommandCommandTextTemplate = "change %1 items' font";
ChangeFontGroupCommand::ChangeFontGroupCommand( const QList<QByteArray> &ids, MindMap *listener )
	: QUndoCommand(), m_listener(listener)
{
	if( ids.count() == 1 )
	{
		Block *node = m_listener->resolveNodeByID(ids.at(0));
		setText(ChangeFontGroupCommandTextTemplate.arg(node->title()));
		m_newFont = node->getProperty("font").value<QFont>();
	}
	else
		setText( ChangeFontGroupCommandCommandTextTemplate.arg(ids.count()) );
	bool ok = false;
	m_newFont = QFontDialog::getFont ( &ok, m_newFont, QApplication::activeWindow() );

	foreach( QByteArray id, ids )
	{
		Block *node = m_listener->resolveNodeByID(id);
		if( node )
		{
			m_fonts[id] = node->getProperty("font").value<QFont>();
			node->setProperty("font", m_newFont);
		}
	}
}


ChangeFontGroupCommand::~ChangeFontGroupCommand()
{
}

void ChangeFontGroupCommand::redo( )
{
	foreach( QByteArray key, m_fonts.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setProperty("font", m_newFont);
	}

}

void ChangeFontGroupCommand::undo( )
{
	foreach( QByteArray key, m_fonts.keys() )
	{
		Block *block = m_listener->resolveNodeByID( key );
		block->setProperty("font", m_fonts[key]);
	}

}

int ChangeFontGroupCommand::id( ) const
{
	return 1033;
}

