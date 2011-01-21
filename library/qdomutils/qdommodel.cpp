/*
    Copyright (C) Ian Reinhart Geiser  <geiseri@sourcextreme.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include "qdommodel.h"
using namespace SxDomUtils;

QDomModel::QDomModel(const QDomDocument &document, QObject *parent)
	: QAbstractItemModel(parent)
{
	m_root = DomPath( document );
}

QDomModel::~QDomModel()
{

}

QVariant QDomModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	if (role != Qt::DisplayRole)
		return QVariant();

	return pathFromIndex( index ).elementInPath().nodeName();
}

QVariant QDomModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && section == 0)
        return "Node";

    return QVariant();

}

Qt::ItemFlags QDomModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return Qt::ItemIsEnabled;
	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QModelIndex QDomModel::index(int row, int column, const QModelIndex &parent ) const
{
    Q_UNUSED(column);

    DomPath parentPath = pathFromIndex( parent );
    QDomElement element = parentPath.elementInPath( );
    QStringList children = parentPath.elementChildren();
    if( children.size() == 0)
        return QModelIndex();

    DomPath childPath( element, element.nodeName() + "/" + children.value(row));
    if( !m_nodes.contains( childPath ) )
        m_nodes << childPath;
    int index = m_nodes.indexOf( childPath );
    return createIndex(row, 0, index );
}

QModelIndex QDomModel::parent(const QModelIndex &index) const
{
	DomPath path = pathFromIndex( index );
	if( path == m_root )
		return QModelIndex();

	QDomElement parentElement = path.elementInPath().parentNode().toElement();
	if( parentElement.isNull() )
		return QModelIndex();

	DomPath parentPath( parentElement );

	int row = 0;
	QDomNode elem = parentElement;
	while( !elem.isNull() )
	{
		row++;
		elem = elem.previousSibling();
	}

	if( m_nodes.contains(parentPath) )
	{
		int id = m_nodes.indexOf(parentPath);
		return createIndex(row - 1, 0, id);
	}
	else
		return QModelIndex();

}

int QDomModel::rowCount(const QModelIndex &parent ) const
{
	DomPath path = pathFromIndex(parent);
	return path.elementChildren().size();
}

int QDomModel::columnCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    return 1;
}

DomPath QDomModel::pathFromIndex( const QModelIndex &parent ) const
{
	DomPath path;
	if (!parent.isValid())
		path = m_root;
	else
		path = m_nodes.value( parent.internalId() );

	return path;
}


QDomPropertyModel::QDomPropertyModel(const DomPath &root, QObject *parent )
	: QAbstractItemModel(parent)
{
	m_root = root;
}

QDomPropertyModel::~QDomPropertyModel()
{

}

QVariant QDomPropertyModel::data(const QModelIndex &index, int role) const
{
	QString field = m_newFields.at( index.column() ).path;
	QVariant returnValue;
	if( field.contains("[%") )
		returnValue = m_root.getValue( field.arg( index.row() ) );
	else
		returnValue = m_root.getValue( field );
	returnValue.convert( m_newFields.at(index.column()).type );

	switch( role )
	{
		case Qt::CheckStateRole:
		{
			if ( m_newFields.at( index.column() ).type == QVariant::Bool )
				return returnValue;
			else
				return QVariant();
			break;
		}
		case Qt::DisplayRole:
		case Qt::EditRole:
		{
			return returnValue;
			break;
		}
		case Qt::StatusTipRole:
		case Qt::ToolTipRole:
		{
			QString textTemplate = "%1-[%2]";
			if( returnValue.toString().isEmpty() )
				returnValue = "...";
			return textTemplate
				.arg(m_newFields.at(index.column()).name)
				.arg(returnValue.toString());
			break;
		}
		default:
			return QVariant();
	}
}

bool QDomPropertyModel::setData ( const QModelIndex & index, const QVariant & value, int role )
{
	if( role != Qt::EditRole )
		return false;

	QString field = m_newFields.at(index.column() ).path;
	QString stringValue = value.toString();

	if( field.contains("[%"))
		field = field.arg( index.row());

	m_root.setValue( field, stringValue );

	dataChanged( index, index );
	return true;
}

Qt::ItemFlags QDomPropertyModel::flags(const QModelIndex &index) const
{
	Qt::ItemFlags itemFlags = Qt::ItemIsEnabled;
	if (index.isValid())
	{
		itemFlags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
	}
	if ( m_newFields.at( index.column() ).type == QVariant::Bool )
	{
		itemFlags |= Qt::ItemIsUserCheckable;
	}
	return itemFlags;
}

QVariant QDomPropertyModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return m_newFields.at(section).name;
	if (orientation == Qt::Vertical && role == Qt::DisplayRole)
		return section;
	return QVariant();
}

QModelIndex QDomPropertyModel::index(int row, int column, const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    int index = (columnCount() * row ) + column;
    return createIndex(row, column, index);
}

QModelIndex QDomPropertyModel::parent(const QModelIndex &index) const
{
    Q_UNUSED(index);
    return QModelIndex();
}

int QDomPropertyModel::rowCount(const QModelIndex &parent ) const
{
	int rows = 0;
	foreach( Field field, m_newFields)
	{
		if( field.path.contains("[%") )
		{
			QString path = field.path.arg(0);
			path.truncate( path.indexOf("[") );
			rows = qMax( m_root.count( path ), rows );
		}
		else
		{
			rows = qMax( 1, rows);
		}
	}
	return rows;
}

int QDomPropertyModel::columnCount(const QModelIndex &parent ) const
{
    Q_UNUSED(parent);
    if( !parent.isValid() )
        return m_newFields.size();
    return 0;
}

bool QDomPropertyModel::insertRows( int row, int count, const QModelIndex & parent )
{
	int maxRow = rowCount();
	beginInsertRows( parent, maxRow, maxRow + count);
	for( int idx = 0; idx < count; ++idx)
	{
		foreach( Field field, m_newFields)
		{
			QString path = field.path.arg( maxRow + idx );
			m_root.setValue( path, "" );
		}
	}
	endInsertRows();
	return true;
}

bool QDomPropertyModel::removeRows ( int row, int count, const QModelIndex & parent  )
{
	beginRemoveRows( parent, row, row + count);
	for( int idx = 0; idx < count; ++idx)
	{
		foreach( Field field, m_newFields)
		{
			QString path = field.path.arg( row + idx);
			m_root.removeElement( path );
			QDomElement element = m_root.elementInPath( path );
			if( !element.hasAttributes() )
				element.parentNode().removeChild(element);
		}
	}
	endRemoveRows();

	return true;
}

void QDomPropertyModel::setRootPath( const DomPath &path )
{
	m_root = path;
	reset();
}

DomPath QDomPropertyModel::rootPath( ) const
{
	return m_root;
}

DomPath QDomPropertyModel::pathForIndex( const QModelIndex &index ) const
{
	Field field = m_newFields.at(index.column());
	if( field.path.contains("[%") )
		return m_root.childPath( field.path.arg( index.row() ) );
	else
		return m_root.childPath( field.path );
}

QModelIndex QDomPropertyModel::indexForPath( const DomPath &path ) const
{
	// There has to be a better way!
	int rows = rowCount();
	int cols = columnCount();
	for( int row = 0; row < rows; ++row)
	{
		for( int col = 0; col < cols; ++col)
		{
			Field field = m_newFields.at(col);
			QString pathString = field.path.arg( row );
			if( pathString.contains("[%") )
				pathString = pathString.arg( row );
			DomPath childPath = m_root.childPath( pathString );
			if( childPath == path)
			{
				if( childPath.property() == path.property() )
					return index( row, col );
			}
		}
	}
	return QModelIndex();
}

void QDomPropertyModel::addField( const QString &name, const QString &path, QVariant::Type type )
{
	Field field = {name, path, type};
	int idx = indexOfField( name );
	if( idx == -1)
	{
		beginInsertColumns( QModelIndex(), m_newFields.count(), m_newFields.count() + 1);
		m_newFields << field;
		endInsertColumns();
	}
	else
	{
		m_newFields.replace(idx,field);
		dataChanged( index(0,idx), index(rowCount(), idx) );
	}
}

void QDomPropertyModel::removeField( const QString &name )
{
	int index = indexOfField( name );
	if( index == -1)
		return;

	beginRemoveColumns( QModelIndex(), index, index );
	m_newFields.removeAt( index );
	endRemoveColumns();
}

int QDomPropertyModel::indexOfField( const QString &name )
{
	int idx = 0;
	foreach( Field field, m_newFields )
	{
		if( field.name == name )
			return idx;
		++idx;
	}
	return -1;
}

void QDomPropertyModel::updateFieldPath( const QString & name, const QString & newPath )
{

	int idx = indexOfField( name );
	if( idx == -1)
		return;

	Field field  = m_newFields.at(idx);
	field.path = newPath;
	m_newFields.replace( idx, field);
	dataChanged( index(0,idx), index(rowCount(), idx) );
}
