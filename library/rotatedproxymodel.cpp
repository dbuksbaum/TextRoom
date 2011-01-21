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
#include "rotatedproxymodel.h"

RotatedProxyModel::RotatedProxyModel( QObject* parent ): QAbstractProxyModel( parent )
{
}

RotatedProxyModel::~RotatedProxyModel()
{
}

void RotatedProxyModel::setSourceModel( QAbstractTableModel* sourceModel )
{
	QAbstractProxyModel::setSourceModel(sourceModel);
}

int RotatedProxyModel::columnCount( const QModelIndex & parent ) const
{
	if( parent.isValid() )
		return 0;

	if( sourceModel() )
		return sourceModel()->rowCount( );
	else
		return 0;
}

QModelIndex RotatedProxyModel::parent( const QModelIndex & index ) const
{
	if( sourceModel() )
		return sourceModel()->parent(index);
	else
		return QModelIndex();
}

int RotatedProxyModel::rowCount( const QModelIndex & parent ) const
{
	if( parent.isValid() )
		return 0;

	if( sourceModel() )
		return sourceModel()->columnCount( );
	else
		return 0;
}

QModelIndex RotatedProxyModel::mapFromSource( const QModelIndex & sourceIndex ) const
{
	if( sourceModel() )
		return sourceModel()->index( sourceIndex.column(), sourceIndex.row(), sourceIndex.parent() );
	else
		return QModelIndex();
}

QModelIndex RotatedProxyModel::mapToSource( const QModelIndex & proxyIndex ) const
{
	if( sourceModel() )
		return sourceModel()->index( proxyIndex.column(), proxyIndex.row(), proxyIndex.parent() );
	else
		return QModelIndex();
}

QModelIndex RotatedProxyModel::index( int row, int column, const QModelIndex & parent ) const
{
	if( sourceModel() )
		return sourceModel()->index( column, row, parent );
	else
		return QModelIndex();
}

QVariant RotatedProxyModel::headerData( int section, Qt::Orientation orientation, int role ) const
{
	if( orientation == Qt::Horizontal )
		return sourceModel()->headerData( section, Qt::Vertical, role );
	else
		return sourceModel()->headerData( section, Qt::Horizontal, role );
}

bool RotatedProxyModel::setHeaderData( int section, Qt::Orientation orientation, const QVariant & value, int role )
{
	if( orientation == Qt::Horizontal )
		return sourceModel()->setHeaderData( section, Qt::Vertical, value, role );
	else
		return sourceModel()->setHeaderData( section, Qt::Horizontal, value, role );
}

