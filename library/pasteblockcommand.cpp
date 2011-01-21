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
#include "pasteblockcommand.h"
#include "blockmimedata.h"
#include "mindmap.h"
#include "block.h"
#include "dompath.h"

#include <QClipboard>
#include <QGraphicsScene>
#include <QDomDocument>
#include <QApplication>

#include <qdebug.h>

PasteBlockCommand::PasteBlockCommand(MindMap *listener)
: QUndoCommand(), m_listener(listener)
{
	setText("Paste node");
	const QMimeData *data = QApplication::clipboard()->mimeData();
	m_xml = data->data(BlockMimeData::mimeTypeName());
}


PasteBlockCommand::~PasteBlockCommand()
{

}


void PasteBlockCommand::redo()
{
	QList<Block *> blocks = BlockMimeData::loadMimeData( m_xml, m_listener );
	m_listener->clearSelection();
	int index = 0;
	if( blocks.count() == 1 )
		setText("Paste node");
	if( blocks.count() > 1 )
		setText("Paste nodes");

	foreach( Block *block, blocks )
	{
		if( m_ids[index].isEmpty() )
			block->calculateUUID();
		else
			block->setId(m_ids[index]);

		m_ids[index] = block->id();
		block->setSelected(true);
		index++;
	}
	m_listener->itemSelectionChanged();

}

void PasteBlockCommand::undo()
{
	m_listener->selectRootNode();

	foreach( QByteArray id, m_ids )
	{
		Block *block = m_listener->resolveNodeByID(id);
		block->detatch();
		m_listener->scene()->removeItem(block);
		delete block;
	}

}

int PasteBlockCommand::id( ) const
{
	return 1026;
}

