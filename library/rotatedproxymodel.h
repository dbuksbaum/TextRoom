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
#ifndef ROTATEDPROXYMODEL_H
#define ROTATEDPROXYMODEL_H

#include <QAbstractProxyModel>
class QAbstractTableModel;

/**
Swaps a table models rows and columns.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class RotatedProxyModel : public QAbstractProxyModel
{
		Q_OBJECT
	public:
		RotatedProxyModel( QObject* parent );
		~RotatedProxyModel();

		virtual QModelIndex index ( int row, int column, const QModelIndex & parent = QModelIndex() ) const;
		virtual QModelIndex mapFromSource ( const QModelIndex & sourceIndex ) const;
		virtual QModelIndex mapToSource ( const QModelIndex & proxyIndex ) const;

		virtual void setSourceModel( QAbstractTableModel* sourceModel );
		virtual int columnCount ( const QModelIndex & parent = QModelIndex() ) const;
		virtual QModelIndex parent ( const QModelIndex & index ) const;
		virtual int rowCount ( const QModelIndex & parent = QModelIndex() ) const;

		virtual QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
		virtual bool setHeaderData ( int section, Qt::Orientation orientation, const QVariant & value, int role = Qt::EditRole );

};

#endif
