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
#include "blockpropertymodel.h"
#include "mindmap.h"
#include  "block.h"
#include "editblockpropertycommand.h"
#include <QUndoStack>

BlockPropertyModel::BlockPropertyModel(MindMap *listener, QUndoStack *commandStack)
: QAbstractTableModel( listener ), m_commandStack(commandStack),m_block(0),m_listener(listener)
{

}

BlockPropertyModel::~BlockPropertyModel()
{

}

bool BlockPropertyModel::setData( const QModelIndex& index, const QVariant& value, int role )
{
    Q_UNUSED(role);
    if( !index.isValid() || m_block == 0)
            return false;
    if( index.row() > 0)
            return false;
    if( index.column() > m_props.count() )
            return false;

    QString propName = m_props.at(index.column());
    m_commandStack->push(new EditBlockPropertyCommand(m_block->id(),propName, value, m_listener));
    emit dataChanged(index, index);
    return true;
}

int BlockPropertyModel::columnCount( const QModelIndex& parent ) const
{
    Q_UNUSED(parent);
    return m_props.count();
}

int BlockPropertyModel::rowCount( const QModelIndex& parent ) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant BlockPropertyModel::data( const QModelIndex& index, int role ) const
{
	if( m_block == 0)
		return QVariant();

	if( !index.isValid() )
		return QVariant();

	if( index.column() < m_props.count() )
	{
		if( role == Qt::DisplayRole || role == Qt::EditRole )
		{
			return m_block->getProperty( m_props.at(index.column()) );
		}
	}
	return QVariant();
}

QVariant BlockPropertyModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( role != Qt::DisplayRole)
		return QVariant();
	else if( orientation == Qt::Vertical)
		return section;
	else
		return m_props.at(section);
}

Block* BlockPropertyModel::block() const
{
	return m_block;
}

void BlockPropertyModel::setBlock( Block* theValue )
{
	m_block = theValue;
	m_props.clear();
	if( theValue )
		m_props = theValue->propertyNames();
	reset();
}

Qt::ItemFlags BlockPropertyModel::flags( const QModelIndex & index ) const
{
    Q_UNUSED(index);
    return Qt::ItemIsSelectable|Qt::ItemIsEnabled|Qt::ItemIsEditable;
}


MindMap* BlockPropertyModel::listener() const
{
	return m_listener;
}


void BlockPropertyModel::setListener( MindMap* theValue )
{
	m_listener = theValue;
}

void BlockPropertyModel::addProperty( const QString & name )
{
	if( !hasProperty(name) )
		m_props << name;
}

void BlockPropertyModel::removeProperty( const QString & name )
{
	m_props.removeAll(name);
}

bool BlockPropertyModel::hasProperty( const QString & name )
{
	return m_props.contains(name);
}

QModelIndex BlockPropertyModel::indexForProperty( const QString &property, int row )
{
	int col = -1;
	for( int idx = 0; idx < columnCount( QModelIndex() ); ++idx )
		if( headerData(idx, Qt::Horizontal, Qt::DisplayRole ).toString() == property )
			col = idx;

	if( col == -1 )
		return QModelIndex();
	else
		return index(row, col);
}
