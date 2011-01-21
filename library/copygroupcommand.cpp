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
#include "copygroupcommand.h"
#include "mindmap.h"
#include "block.h"
#include "blockmimedata.h"
#include <QApplication>
#include <QClipboard>

QString CopyBlockCommandTextTemplate = "copy \"%1\"";
QString CopyGroupCommandTextTemplate = "copy %1 items";
CopyGroupCommand::CopyGroupCommand(const QList<QByteArray> &ids, MindMap *listener)
		: QUndoCommand(), m_ids(ids), m_listener(listener)
{
	if( ids.count() == 1 )
	{
		Block *node = m_listener->resolveNodeByID(m_ids.at(0));
		setText(CopyBlockCommandTextTemplate.arg(node->title()));
	}
	else
		setText( CopyGroupCommandTextTemplate.arg(ids.count()) );
}


CopyGroupCommand::~CopyGroupCommand()
{
}

void CopyGroupCommand::undo( )
{
	QUndoCommand::undo();
}

void CopyGroupCommand::redo( )
{
	QList<Block*> nodeList;
	foreach( QByteArray id, m_ids)
		nodeList << m_listener->resolveNodeByID(id);

	QApplication::clipboard()->setMimeData( new BlockMimeData(nodeList) );
}

int CopyGroupCommand::id( ) const
{
	return 1026;
}


