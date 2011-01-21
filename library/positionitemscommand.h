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
#ifndef POSITIONITEMSCOMMAND_H
#define POSITIONITEMSCOMMAND_H

#include <QUndoCommand>
#include <QHash>
#include <QPointF>

class MindMap;

/**
A command that arranges the children on the page.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class PositionItemsCommand : public QUndoCommand
{
	public:
		PositionItemsCommand( MindMap *listener );
		~PositionItemsCommand();

		void undo();
		void redo();
		virtual int id() const;

	private:
		MindMap *m_listener;
		QHash<QByteArray,QPointF> m_newPositions;
		QHash<QByteArray,QPointF> m_oldPositions;

};

#endif
