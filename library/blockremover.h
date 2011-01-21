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
#ifndef BLOCKREMOVER_H
#define BLOCKREMOVER_H

#include <QUndoCommand>
#include <QHash>
#include <QPointF>

class MindMap;

/**
This is the common base class for DeleteBlockCommand and CutBlockCommand. It will allow for a node to be removed, and readded later.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class BlockRemover
{
public:
	BlockRemover(const QByteArray &id, MindMap *listener);
	~BlockRemover();

	void removeBlock();
	void restoreBlock();

private:
	QByteArray m_id;
	QByteArray m_parent;
	QList<QByteArray> m_children;
	MindMap *m_listener;
	QPointF m_pos;
	QHash<QString,QVariant> m_properties;
};

#endif
