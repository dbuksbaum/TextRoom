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
#include "blockmimedata.h"
#include "block.h"
#include "dompath.h"
#include "mindmap.h"

#include <QStringList>
#include <QImage>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QMessageBox>
#include <QTextStream>

const QString MapFragmentMimeType = "x-mindmap/fragment";

BlockMimeData::BlockMimeData(Block *block)
: QMimeData()
{
// 	QImage copyImage(block->boundingRect().size().toSize(), QImage::Format_ARGB32_Premultiplied);
// 	QStyleOptionGraphicsItem option;
// 	QPainter p(&copyImage);
// 	block->paint(&p, &option);
// 	p.end();
//
// 	setImageData(copyImage);

	QList<Block*> blocks;
	blocks << block;
	setData( MapFragmentMimeType, saveMimeData( blocks ) );
}


BlockMimeData::~BlockMimeData()
{}

BlockMimeData::BlockMimeData( QList< Block * > blocks )
: QMimeData()
{
/*
	QImage copyImage(block->boundingRect().size().toSize(), QImage::Format_ARGB32_Premultiplied);
	QStyleOptionGraphicsItem option;
	QPainter p(&copyImage);
	block->paint(&p, &option);
	p.end();

	setImageData(copyImage);
*/
	setData( MapFragmentMimeType, saveMimeData( blocks ) );
}

QByteArray BlockMimeData::saveMimeData( const QList< Block * > blocks )
{
	QString textBuffer;
	QTextStream ts(&textBuffer, QIODevice::WriteOnly);
	QDomDocument dom;
	QDomElement fragmentElement = dom.createElement("mindmap");
	dom.appendChild(fragmentElement);

	int idx = 0;
	foreach( Block *block, blocks )
	{
		SxDomUtils::DomPath blockPath( fragmentElement,
		                               QString("mindmap/nodes/node[%1]").arg(idx));
		SxDomUtils::DomPath connPath( fragmentElement,
		                              QString("mindmap/connections/connection[%1]").arg(idx));
		block->saveBlock( blockPath, connPath, true );
		idx++;
	}

	fragmentElement.save(ts, 1);
	return textBuffer.toLatin1();
}

QList< Block * > BlockMimeData::loadMimeData(  const QByteArray &xml,  MindMap * listener )
{
	QList<Block*> blockList;

	QDomDocument document;
	QString error;
	int line;
	int col;
	if( document.setContent( xml, &error, &line, &col ) )
	{
		int blockCount = SxDomUtils::count( document.documentElement(), QString("mindmap/nodes/node"));

		for( int idx = 0; idx < blockCount; ++idx)
		{
			SxDomUtils::DomPath blockPath( document.documentElement(),
										QString("mindmap/nodes/node[%1]").arg(idx));
			Block *block = Block::loadBlock(blockPath, listener->scene());
			if( block )
			{
				block->setMindmap(listener);
				blockList << block;
			}
		}

		int connCount = SxDomUtils::count( document.documentElement(),
										QString("mindmap/connections/connection"));

		for( int idx = 0; idx < connCount; ++idx)
		{
			SxDomUtils::DomPath connPath( document.documentElement(),
										QString("mindmap/connections/connection[%1]").arg(idx));
			int nodeCount = connPath.count( "connection/node" );
			for( int nodeIdx = 0; nodeIdx < nodeCount; ++nodeIdx )
			{
				QString startPathTemplate = "connection/node[%1].start";
				QString endPathTemplate = "connection/node[%1].end";

				Block *start = listener->resolveNodeByID( connPath.getValue( startPathTemplate.arg(nodeIdx) ).toLatin1() );
				Block *end = listener->resolveNodeByID( connPath.getValue( endPathTemplate.arg(nodeIdx) ).toLatin1() );
				if( start != 0 && end != 0)
					end->setParentNode(start);
			}
		}
	}
	else
	{
		QMessageBox::critical(0, "Error", QString("Parse error \"%1\" at %2,%3")
							.arg(error).arg(line).arg(col), QMessageBox::Ok, QMessageBox::NoButton);
	}

	return blockList;
}

QString BlockMimeData::mimeTypeName( )
{
	return MapFragmentMimeType;
}

