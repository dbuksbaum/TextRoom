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
#ifndef MOVEGROUPCOMMAND_H
#define MOVEGROUPCOMMAND_H

#include <QUndoCommand>
#include <QList>
#include <QHash>
#include <QByteArray>

class QPointF;
class MindMap;

/**
This command will move a group of blocks along the same delta.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class MoveGroupCommand : public QUndoCommand
{
public:
	MoveGroupCommand(const QList<QByteArray> &ids, const QPointF & delta, MindMap *listener );

	~MoveGroupCommand();

	virtual bool mergeWith(const QUndoCommand* other);
	virtual int id() const;
private:
	QHash<QByteArray,QUndoCommand*> m_children;
};

#endif
