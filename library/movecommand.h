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
#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include <QUndoCommand>
#include <QList>
#include <QPoint>

class MindMap;

/**
A command that can move or unmove an object to a new location.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class MoveCommand : public QUndoCommand
{
public:
	MoveCommand(const QByteArray &id, const QPointF & delta, MindMap *listener, QUndoCommand * parent = 0 );

	~MoveCommand();

	bool mergeWith ( const QUndoCommand * command );
	int id () const;
	void undo();
	void redo();

private:
	QByteArray m_id;
	MindMap *m_listener;
	QPointF m_delta;
};

#endif
