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
#include <qadaptor.h>

#include <QAbstractTableModel>
#include <QModelIndex>
#include <QWidget>

namespace QModelAdaptor
{

	QModelAdaptorBase::QModelAdaptorBase( QAbstractItemModel *model, QObject *parent)
	: QObject(parent), m_model(model), m_editor(0)
	{
		m_currentRow = 0;
		m_currentColumn = 0;
		connect( m_model, SIGNAL(dataChanged ( const QModelIndex &, const QModelIndex &)),
		         this, SLOT(updateEditor(const QModelIndex &, const QModelIndex &)));
		connect( m_model, SIGNAL(modelReset()), this, SLOT( updateEditor() ));
	}

	QModelAdaptorBase::~QModelAdaptorBase( )
	{}

	void  QModelAdaptorBase::setPropertyName( const QByteArray & theValue )
	{
		m_property = theValue;
		updateEditor();
	}

	QByteArray  QModelAdaptorBase::propertyName( ) const
	{
		return m_property;
	}

	void  QModelAdaptorBase::setColumn( const int & theValue )
	{
		int col = qBound( 0, theValue, model()->columnCount() - 1 );
		m_currentColumn = col;
		updateEditor();
	}

	int  QModelAdaptorBase::column( ) const
	{
		return m_currentColumn;
	}

	void  QModelAdaptorBase::setRow( const int & theValue )
	{
		int row = qBound( 0, theValue, model()->rowCount() - 1 );
		m_currentRow = row;
		updateEditor();
	}

	int  QModelAdaptorBase::row( ) const
	{
		return m_currentRow;
	}

	void  QModelAdaptorBase::setEditor( QWidget * theValue )
	{
		if( m_editor && !m_signal.isEmpty() )
			disconnect( m_editor, m_signal.constData(), this, SLOT(updateModel()) );
		m_editor = theValue;
		if( m_editor && !m_signal.isEmpty() )
			connect( m_editor, m_signal.constData(), this, SLOT(updateModel()) );
// 		updateEditor();
	}

	QWidget *  QModelAdaptorBase::editor( ) const
	{
		return m_editor;
	}

	QModelIndex QModelAdaptorBase::currentIndex( ) const
	{
		return m_model->index( m_currentRow, m_currentColumn );
	}


	const QAbstractItemModel *QModelAdaptorBase::model( ) const
	{
		return m_model;
	}
	void  QModelAdaptorBase::updateModel( )
	{
		if( isValid())
		{
			QModelIndex index = currentIndex();
			if(  m_model->flags( currentIndex() ) & Qt::ItemIsEditable )
			{
// Wont work on Qt 4.2 because of != in QVariant with custom types
 				if( m_model->data(index, Qt::EditRole) != m_editor->property(m_property.constData()) ||
					m_editor->property(m_property.constData()).type() > 127 )
					m_model->setData(index, m_editor->property(m_property.constData()), Qt::EditRole );
			}
		}
	}

	void  QModelAdaptorBase::updateEditor( const QModelIndex & topLeft, const QModelIndex & bottomRight )
	{
		if( topLeft.row() <= row() && bottomRight.row() >= row() &&
		        topLeft.column() <= column() && bottomRight.column() >= column() )
		{
			updateEditor();
		}
	}

	void QModelAdaptorBase::first( )
	{
		setRow(0);
	}

	void QModelAdaptorBase::next( )
	{
		setRow(row() + 1);
	}

	void QModelAdaptorBase::last( )
	{
		setRow(model()->rowCount()  -  1 );
	}

	void QModelAdaptorBase::previous( )
	{
		setRow( row() - 1);
	}

	void QModelAdaptorBase::jump( int row )
	{
		setRow( row );
	}

	bool  QModelAdaptorBase::isValid( )
	{
		if( !m_editor)
			return false;
		if( !currentIndex().isValid() )
			return false;
		if( m_property.isEmpty())
			return false;
		return true;
	}

	void  QModelAdaptorBase::updateEditor( )
	{
		if( !isValid())
			return;
		QModelIndex index = currentIndex();
		m_editor->setToolTip(qVariantValue<QString>( currentIndex().data(Qt::ToolTipRole)));
		m_editor->setWhatsThis(qVariantValue<QString>(currentIndex().data(Qt::WhatsThisRole)));
		m_editor->setStatusTip(qVariantValue<QString>(currentIndex().data(Qt::StatusTipRole)));
		m_editor->setEnabled( m_model->flags( currentIndex() ) & Qt::ItemIsEnabled );
// Wont work on Qt 4.2 because of != in QVariant with custom types
// 		if( m_editor->property(m_property.constData()) != currentIndex().data(Qt::EditRole ) )
		{
			m_editor->setProperty(m_property.constData(), currentIndex().data(Qt::EditRole ) );
			emit dataChanged();
		}
	}

	void QModelAdaptorBase::setEditSignal( const QByteArray & theValue )
	{
		if( !m_signal.isEmpty()  && m_editor )
			disconnect( m_editor, m_signal.constData(), this, SLOT(updateModel()) );
		m_signal = theValue;
		if( !m_signal.isEmpty()  && m_editor )
			connect( m_editor, m_signal.constData(), this, SLOT(updateModel()) );
		updateEditor();
	}

	QByteArray QModelAdaptorBase::editSignal( ) const
	{
		return m_signal;
	}

	QAbstractItemModelAdaptor::QAbstractItemModelAdaptor(QAbstractItemModel *model, QWidget* editor,
		const char *property, const char * editSignal)
	: QModelAdaptorBase( model, editor)
	{
		setPropertyName( property );
		setEditSignal( editSignal );
		setEditor( editor );
	}

QAbstractItemModelSelectionAdaptor::QAbstractItemModelSelectionAdaptor( QAbstractItemModel *model,
	QWidget* editor, const char * editSignal )
	: QModelAdaptorBase( model, editor ), m_contentModel(0)
{
	setEditSignal( editSignal );
	setEditor( editor );
}

void QAbstractItemModelSelectionAdaptor::updateModel()
{
	if( m_contentModel == 0)
		return;
	QModelIndex currentContentIndex = editorSelection();
	if( !currentContentIndex.isValid() )
		return;

	QModelIndex dataIndex = m_contentModel->index( currentContentIndex.row(), m_indexColumn );

	if( !dataIndex.isValid() )
		return;

	QAbstractItemModel *ncModel = const_cast<QAbstractItemModel*>( model() );
	if( ncModel == 0)
		return;

	ncModel->setData( currentIndex(), dataIndex.data(Qt::EditRole), Qt::EditRole );
}

void QAbstractItemModelSelectionAdaptor::updateEditor( )
{
	if( m_contentModel == 0)
		return;
	QVariant curData = currentIndex().data(Qt::EditRole );
	QModelIndex startIndex = m_contentModel->index( 0, m_indexColumn );
	QModelIndexList matchList = m_contentModel->match( startIndex, Qt::EditRole, curData, 1, Qt::MatchExactly );
	if( matchList.isEmpty() )
		return;

	QModelIndex resultIndex = m_contentModel->index( matchList.at(0).row(), m_displayColumn );
	setEditorSelection( resultIndex );

	editor()->setToolTip(qVariantValue<QString>(resultIndex.data(Qt::ToolTipRole)));
	editor()->setWhatsThis(qVariantValue<QString>(resultIndex.data(Qt::WhatsThisRole)));
	editor()->setStatusTip(qVariantValue<QString>(resultIndex.data(Qt::StatusTipRole)));
}

void QAbstractItemModelSelectionAdaptor::setContentModel(QAbstractItemModel *model)
{
	m_contentModel = model;
	updateEditor();
}

QAbstractItemModel *QAbstractItemModelSelectionAdaptor::contentModel() const
{
	return m_contentModel;
}

void  QAbstractItemModelSelectionAdaptor::setDisplayColumn( int col )
{
	m_displayColumn = col;
}

int  QAbstractItemModelSelectionAdaptor::displayColumn( ) const
{
	return m_displayColumn;
}

void  QAbstractItemModelSelectionAdaptor::setIndexColumn( int col )
{
	m_indexColumn = col;
}

int  QAbstractItemModelSelectionAdaptor::indexColumn( ) const
{
	return m_indexColumn;
}

}


