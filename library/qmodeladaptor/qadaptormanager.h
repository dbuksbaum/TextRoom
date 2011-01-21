/***************************************************************************
 *   Copyright (C) 2005 by Ian Reinhart Geiser                             *
 *   geiseri@sourcextreme.com                                              *
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
#ifndef QMODELADAPTORQADAPTORMANAGER_H
#define QMODELADAPTORQADAPTORMANAGER_H

#include <QObject>
#include <QHash>
#include <qadaptorfactory.h>

class QAbstractItemModel;
class QWidget;

namespace QModelAdaptor
{

	/**
	@author Ian Reinhart Geiser
	*/
	class QAdaptorManager : public QObject
	{
		Q_OBJECT
	public:
			/**
			 * A proxy that will forward updates to a group of Model Adaptors.
			 */
		QAdaptorManager(QAbstractItemModel *parent );
		~QAdaptorManager();

		void bindForm( QWidget *editor );
		bool bindWidget( QWidget *editor, int column );
		bool bindWidget( QWidget *editor, const QString &column );
		bool bindContentModel( const QWidget *target,
		                       QAbstractItemModel *content,
		                       int indexColumn = 0,
		                       int displayColumn = 1);

		void add( QModelAdaptorBase *obj);
		void remove( QModelAdaptorBase *obj);
		void setAdaptorFactory(const QByteArray &type, QAdaptorFactoryBase* factory );

	public slots:
		void firstRow();
		void nextRow();
		void lastRow();
		void previousRow();
		void jumpRow( int idx );
		void setRowFromIndex( const QModelIndex &index );
	signals:
		void first();
		void next();
		void last();
		void previous();
		void jump( int idx );

	private:
		QAbstractItemModel *m_model;
		QHash<QByteArray,QAdaptorFactoryBase*> m_factories;
		QList<QModelAdaptorBase*> m_activeAdaptors;
	};

}

#endif
