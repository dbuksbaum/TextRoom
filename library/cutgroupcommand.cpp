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
#include "cutgroupcommand.h"
#include "mindmap.h"
#include "blockremover.h"
#include "blockmimedata.h"
#include "block.h"

#include <QClipboard>
#include <QMimeData>
#include <QGraphicsScene>
#include <QApplication>

QString CutBlockCommandTextTemplate = "cut \"%1\"";
QString CutGroupCommandTextTemplate = "cut %1 items";

CutGroupCommand::CutGroupCommand(const QList<QByteArray> &ids, MindMap *listener)
: QUndoCommand(), m_ids(ids), m_listener(listener)
{
	if( ids.count() == 1 )
	{
		Block *node = m_listener->resolveNodeByID(m_ids.at(0));
		setText(CutBlockCommandTextTemplate.arg(node->title()));
	}
	else
		setText(CutGroupCommandTextTemplate.arg(m_ids.count()));

	foreach( QByteArray id, m_ids)
		m_removedBlocks << new BlockRemover(id, listener);

}


CutGroupCommand::~CutGroupCommand()
{}


void CutGroupCommand::redo()
{
	QList<Block*> nodeList;
	foreach( QByteArray id, m_ids)
		nodeList << m_listener->resolveNodeByID(id);

	QApplication::clipboard()->setMimeData( new BlockMimeData(nodeList) );

	foreach(BlockRemover *remover, m_removedBlocks)
		remover->removeBlock();
}

void CutGroupCommand::undo()
{
	foreach(BlockRemover *remover, m_removedBlocks)
		remover->restoreBlock();
}

int CutGroupCommand::id( ) const
{
	return 1028;
}

