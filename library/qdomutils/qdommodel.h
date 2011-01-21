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

#ifndef QDOM_MODEL
#define QDOM_MODEL

#include <dompath.h>
#include <QStringList>
#include <QHash>
#include <QAbstractItemModel>
#include <QDomDocument>

namespace SxDomUtils {

class QDomModel : public QAbstractItemModel
{
Q_OBJECT

public:
	QDomModel(const QDomDocument &document, QObject *parent = 0);
	~QDomModel();

	QVariant data(const QModelIndex &index, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	DomPath pathFromIndex( const QModelIndex &parent ) const;

private:
	DomPath m_root;
	mutable QList<DomPath> m_nodes;
};

/**
 * A model of a list of properties in a QDom object.
 **/
class QDomPropertyModel : public QAbstractItemModel
{
Q_OBJECT

public:
	QDomPropertyModel(const DomPath &root, QObject *parent = 0);
	~QDomPropertyModel();

	/**
	 * Set the root path for the model.  Setting this will reset the model.
	 **/
	void setRootPath( const DomPath &path );
	DomPath rootPath( ) const;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	bool setData ( const QModelIndex & index, const QVariant & value, int role = Qt::EditRole );
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	bool insertRows( int row, int count, const QModelIndex & parent = QModelIndex() );
	bool removeRows ( int row, int count, const QModelIndex & parent = QModelIndex() );

	/**
	 * Returns a DomPath for a model index.  This is useful for propigating a item selection
	 * to another model's root path.
	 */
	DomPath pathForIndex( const QModelIndex &index ) const;
	/**
	 * Returns a QModelIndex for a known dom path.  This is useful for selecting an item in
	 * the model based off of a known path.
	 */
	QModelIndex indexForPath( const DomPath &path ) const;

	/**
	 * Add a field to the model. This field will be appended to the field list.
	 * If the field already exists in the model it will be overwritten.
	 */
	void addField( const QString &name, const QString &path, QVariant::Type type = QVariant::String );
	/**
	 * Update a field's path in the model.
	 */
	void updateFieldPath( const QString &name, const QString &newPath );
	/**
	 * Remove a field from the model.
	 */
	void removeField( const QString &name );

private:
	struct Field
	{
		QString name;
		QString path;
		QVariant::Type type;
	};

	int indexOfField( const QString &name );
	DomPath m_root;
	QList<Field> m_newFields;

};

}
#endif
