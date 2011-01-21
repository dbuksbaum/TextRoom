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
#ifndef EDITBLOCKPROPERTYCOMMAND_H
#define EDITBLOCKPROPERTYCOMMAND_H

#include <QUndoCommand>
#include <QList>
#include <QVariant>

class MindMap;
/**
This is a command that will edit a generic block property.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class EditBlockPropertyCommand : public QUndoCommand
{
public:
	EditBlockPropertyCommand(const QByteArray &id, const QString &propName,
	                         const QVariant &propValue, MindMap *listener );

	~EditBlockPropertyCommand();

	bool mergeWith ( const QUndoCommand * command );
	int id () const;
	void undo();
	void redo();

private:
	QByteArray m_id;
	MindMap *m_listener;
	QString m_property;
	QVariant m_newProperty;
	QVariant m_oldProperty;
};

#endif
