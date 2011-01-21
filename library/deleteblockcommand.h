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
#ifndef DELETEBLOCKCOMMAND_H
#define DELETEBLOCKCOMMAND_H

#include "blockremover.h"

#include <QUndoCommand>
#include <QHash>
#include <QPointF>

class MindMap;

/**
A command that will delete a block from the scene.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class DeleteBlockCommand : public BlockRemover, public QUndoCommand
{
public:
	DeleteBlockCommand(const QByteArray &id, MindMap *listener, QUndoCommand *parent = 0);

	~DeleteBlockCommand();

	virtual void redo();
	virtual void undo();
	virtual int id() const;

private:
	QByteArray m_id;
	QByteArray m_parent;
	QList<QByteArray> m_children;
	MindMap *m_listener;
	QPointF m_pos;
	QHash<QString,QVariant> m_properties;
};

#endif
