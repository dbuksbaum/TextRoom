/***************************************************************************
 *   Copyright (C) 2006 by Ian Reinhart Geiser   *
 *   geiseri@yahoo.com   *
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
#ifndef BLOCKMIMEDATA_H
#define BLOCKMIMEDATA_H

#include <QMimeData>
#include <QHash>
#include <QVariant>
#include <QPointF>

class Block;
class MindMap;
/**
A mime data object that can handle Blocks.  It will populate the following resources:
 * @li Image - An pixmap image of the block.
 * @li Text - The XML representation of the node.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class BlockMimeData : public QMimeData
{
	Q_OBJECT
public:
	BlockMimeData(Block *block);
	BlockMimeData(QList<Block*> blocks);
	~BlockMimeData();

	static QByteArray saveMimeData( const QList<Block*> blocks);
	static QList<Block*> loadMimeData( const QByteArray &xml, MindMap *listener );
	static QString mimeTypeName();

};

#endif
