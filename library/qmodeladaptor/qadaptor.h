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
#ifndef QMODELADAPTORQADAPTORBASE_H
#define QMODELADAPTORQADAPTORBASE_H

#include <QObject>
#include <QPersistentModelIndex>
class QAbstractItemModel;
class QWidget;

#define MODEL_ADAPTOR( CLAZZ, PROPERTY, EDITSIGNAL ) \
namespace QModelAdaptor {\
	class CLAZZ : public QAbstractItemModelAdaptor \
	{ \
	public: \
		CLAZZ(QAbstractItemModel *model, QWidget *editor ) \
		: QAbstractItemModelAdaptor(model, editor, PROPERTY, EDITSIGNAL) \
		{}\
	};\
}

namespace QModelAdaptor
{

	/**
	* @author Ian Reinhart Geiser
	*/
	class QModelAdaptorBase : public QObject
	{
		Q_OBJECT
		Q_PROPERTY(int column READ column WRITE setColumn)
		Q_PROPERTY(int row READ row WRITE setRow)
		Q_PROPERTY(QByteArray propertyName READ propertyName WRITE setPropertyName )

	public:
		QModelAdaptorBase(QAbstractItemModel *model, QObject *parent = 0 );

		virtual ~QModelAdaptorBase();

		void setPropertyName(const QByteArray& theValue);
		QByteArray propertyName() const;

		void setEditSignal( const QByteArray& theValue );
		QByteArray editSignal() const;

		void setColumn(const int& theValue);
		int column() const;
		void setRow(const int& theValue);
		int row() const;

		virtual void setEditor(QWidget* theValue);
		QWidget* editor() const;
		QModelIndex currentIndex( ) const;
		const QAbstractItemModel *model( ) const;

	public slots:
		virtual void updateModel();
		virtual void updateEditor();
		virtual void updateEditor(const QModelIndex & topLeft, const QModelIndex & bottomRight);

		virtual void first();
		virtual void next();
		virtual void last();
		virtual void previous();
		virtual void jump( int row );

	signals:
		void dataChanged();

	protected:
		virtual bool isValid();


	private:
		QAbstractItemModel *m_model;
		QWidget *m_editor;
		QModelIndex m_parent;
		QByteArray m_property;
		QByteArray m_signal;
		int m_currentRow;
		int m_currentColumn;
	};

	class QAbstractItemModelAdaptor : public QModelAdaptorBase
	{
	Q_OBJECT
	public:
			QAbstractItemModelAdaptor(QAbstractItemModel *model, QWidget* editor,
		                          const char *property, const char * editSignal);

	};

	class QAbstractItemModelSelectionAdaptor : public QModelAdaptorBase
	{
	Q_OBJECT
	public:
		QAbstractItemModelSelectionAdaptor(QAbstractItemModel *model,
		                                    QWidget* editor, const char * editSignal );

		void setContentModel(QAbstractItemModel *model);
		QAbstractItemModel *contentModel() const;

		void setDisplayColumn( int col );
		int displayColumn( ) const;

		void setIndexColumn( int col );
		int indexColumn( ) const;

		virtual void updateEditorContent() = 0;
		virtual void setEditorSelection( const QModelIndex &index ) = 0;
		virtual QModelIndex editorSelection(  ) const = 0;

	public slots:
		virtual void updateModel();
		virtual void updateEditor();

	private:
		QAbstractItemModel *m_contentModel;
		int m_displayColumn;
		int m_indexColumn;
	};
}
#endif
