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
#ifndef BLOCKPROPERTYMODEL_H
#define BLOCKPROPERTYMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

class QUndoStack;
class Block;
class MindMap;

/**
This is a basic model that allows block properties to be editted with undo/redo support.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class BlockPropertyModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	BlockPropertyModel(MindMap *listener, QUndoStack *commandStack);
	~BlockPropertyModel();

	virtual bool setData( const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
	virtual int columnCount( const QModelIndex& parent ) const;
	virtual int rowCount( const QModelIndex& parent ) const;
	virtual QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const;
	virtual QVariant headerData( int section, Qt::Orientation orientation, int role ) const;
	virtual Qt::ItemFlags flags ( const QModelIndex & index ) const;

	void setBlock( Block* theValue );
	Block* block() const;

	void setListener( MindMap* theValue );
	MindMap* listener() const;

	void addProperty( const QString &name );
	void removeProperty( const QString &name );
	bool hasProperty( const QString &name );

	QModelIndex indexForProperty( const QString &property, int row = 0 );

private:
	QUndoStack *m_commandStack;
	Block *m_block;
	MindMap *m_listener;
	QStringList m_props;
};

#endif
