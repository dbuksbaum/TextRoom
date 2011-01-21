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
#include "qadaptormanager.h"

#include <QAbstractItemModel>
#include <QWidget>

#include "qadaptorfactory.h"
#include "qadaptor.h"

#include <QComboBox>

using namespace QModelAdaptor;

MODEL_ADAPTOR( QCheckBoxAdaptor, "checked", SIGNAL(clicked(bool)))
MODEL_ADAPTOR( QRadioButtonAdaptor, "checked", SIGNAL(clicked(bool)) )
MODEL_ADAPTOR( QDateTimeEditAdaptor, "dateTime", SIGNAL(editingFinished()))
MODEL_ADAPTOR( QDateEditAdaptor, "date", SIGNAL(editingFinished()))
MODEL_ADAPTOR( QTimeEditAdaptor, "time", SIGNAL(editingFinished()))
MODEL_ADAPTOR( QLineEditAdaptor, "text", SIGNAL(editingFinished()))
MODEL_ADAPTOR( QSpinBoxAdaptor, "value", SIGNAL(editingFinished()))
MODEL_ADAPTOR( QAbstractSliderAdaptor, "value", SIGNAL(sliderReleased()))
MODEL_ADAPTOR( QFontComboAdaptor, "currentFont", SIGNAL(currentFontChanged( const QFont &)) )
MODEL_ADAPTOR( QProgressBarAdaptor, "value", 0)
MODEL_ADAPTOR( QLCDNumberAdaptor, "value", 0)

#include <QAbstractItemView>
class QComboBoxAdaptor : public QAbstractItemModelSelectionAdaptor
{
public:
	QComboBoxAdaptor( QAbstractItemModel *model, QWidget* editor);
	void updateEditorContent();
	void setEditorSelection( const QModelIndex &index );
	QModelIndex editorSelection(  ) const;
};

QComboBoxAdaptor::QComboBoxAdaptor( QAbstractItemModel *model, QWidget* editor)
	: QAbstractItemModelSelectionAdaptor( model, editor, SIGNAL(activated (int)) )
{
	setPropertyName( "currentIndex" );
}

void QComboBoxAdaptor::updateEditorContent()
{
	QComboBox *combo = qobject_cast<QComboBox*>( editor() );
	if( combo )
	{
		combo->setModel( contentModel() );
		combo->setModelColumn( displayColumn() );
	}
}

void QComboBoxAdaptor::setEditorSelection( const QModelIndex &index )
{
	QComboBox *combo = qobject_cast<QComboBox*>( editor() );
	if( combo )
	{
		combo->setCurrentIndex( index.row() );
	}
}

QModelIndex QComboBoxAdaptor::editorSelection(  ) const
{
	QComboBox *combo = qobject_cast<QComboBox*>( editor() );
	if( combo )
	{
		int curIndex = combo->currentIndex( );
		return contentModel()->index( curIndex, displayColumn() );
	}
	return QModelIndex();
}



QAdaptorManager::QAdaptorManager(QAbstractItemModel *parent)
		: QObject(parent), m_model(parent)
{
	setAdaptorFactory("QComboBox", new QAdaptorFactory<QComboBoxAdaptor>());
	setAdaptorFactory("QLineEdit", new QAdaptorFactory<QLineEditAdaptor>());
	setAdaptorFactory("QSpinBox", new QAdaptorFactory<QSpinBoxAdaptor>());
	setAdaptorFactory("QDoubleSpinBox", new QAdaptorFactory<QSpinBoxAdaptor>());
	setAdaptorFactory("QCheckBox", new QAdaptorFactory<QCheckBoxAdaptor>());
	setAdaptorFactory("QRadioButton", new QAdaptorFactory<QRadioButtonAdaptor>());
	setAdaptorFactory("QTimeEdit", new QAdaptorFactory<QTimeEditAdaptor>());
	setAdaptorFactory("QDateEdit", new QAdaptorFactory<QDateEditAdaptor>());
	setAdaptorFactory("QDateTimeEdit", new QAdaptorFactory<QDateTimeEditAdaptor>());
	setAdaptorFactory("QAbstractSlider", new QAdaptorFactory<QAbstractSliderAdaptor>());
	setAdaptorFactory("QProgressBar", new QAdaptorFactory<QProgressBarAdaptor>());
	setAdaptorFactory("QLCDNumber", new QAdaptorFactory<QLCDNumberAdaptor>());
	setAdaptorFactory("QFontComboBox", new QAdaptorFactory< QFontComboAdaptor>());
}

QAdaptorManager::~QAdaptorManager()
{
	foreach( QAdaptorFactoryBase *factory, m_factories )
		delete factory;
}

void QAdaptorManager::setAdaptorFactory(const QByteArray &type, QAdaptorFactoryBase* factory )
{
	m_factories[type] = factory;
}

void QAdaptorManager::add(QModelAdaptorBase *obj )
{
	connect( this, SIGNAL(first()), obj, SLOT(first()));
	connect( this, SIGNAL(next()), obj, SLOT(next()));
	connect( this, SIGNAL(previous()), obj, SLOT(previous()));
	connect( this, SIGNAL(last()), obj, SLOT(last()));
	connect( this, SIGNAL(jump(int)), obj, SLOT(jump(int)));
	m_activeAdaptors << obj;
}

void QAdaptorManager::remove(QModelAdaptorBase *obj )
{
	disconnect( this, SIGNAL(first()), obj, SLOT(first()));
	disconnect( this, SIGNAL(next()), obj, SLOT(next()));
	disconnect( this, SIGNAL(previous()), obj, SLOT(previous()));
	disconnect( this, SIGNAL(last()), obj, SLOT(last()));
	disconnect( this, SIGNAL(jump(row)), obj, SLOT(jump(int)));

	m_activeAdaptors.removeAll( obj );
}

void QAdaptorManager::bindForm( QWidget *form )
{

	int max = m_model->columnCount();
	for( int idx = 0; idx < max; ++idx)
	{
		QString objName = qVariantValue<QString>(m_model->headerData(idx, Qt::Horizontal ) );
		QWidget *editor = qFindChild<QWidget *>(form, objName);
		bindWidget( editor, idx );
	}
}

bool QAdaptorManager::bindContentModel( const QWidget *target, QAbstractItemModel *content,
	int indexColumn, int displayColumn )
{
	foreach( QModelAdaptorBase *adaptor, m_activeAdaptors)
	{
		if( adaptor->editor() == target)
		{
			QAbstractItemModelSelectionAdaptor *nativeAdaptor =
				qobject_cast<QAbstractItemModelSelectionAdaptor*>( adaptor );
			if( nativeAdaptor == 0)
				return false;
			nativeAdaptor->setContentModel( content );
			nativeAdaptor->setDisplayColumn( displayColumn );
			nativeAdaptor->setIndexColumn( indexColumn );
			nativeAdaptor->updateEditorContent();
			nativeAdaptor->updateEditor();
			return true;
		}
	}

	return false;

}

bool QAdaptorManager::bindWidget( QWidget *editor, const QString &column )
{
	int max = m_model->columnCount();
	for( int idx = 0; idx < max; ++idx)
	{
		QString headerName = qVariantValue<QString>(m_model->headerData(idx, Qt::Horizontal ) );
		if( headerName == column )
		{
			return bindWidget( editor, idx );
		}
	}
	return false;
}

bool QAdaptorManager::bindWidget( QWidget *editor, int column )
{
	if( editor == 0)
		return false;

	QAdaptorFactoryBase *factory = m_factories[editor->metaObject()->className()];
	if( factory == 0 )
	{
		QList<QByteArray> keys = m_factories.keys();
		foreach (QByteArray key, keys)
		{
			if( editor->inherits( key.constData() ) )
			{
				factory = m_factories[key];
				break;
			}
		}
	}

	if( factory == 0 )
		return false;

	QModelAdaptorBase *item = factory->create(m_model, editor );
	item->setColumn(column);
	add( item );
	return true;
}

void QAdaptorManager::firstRow()
{
	emit first();
}

void QAdaptorManager::nextRow()
{
	emit next();
}


void QAdaptorManager::lastRow()
{
	emit last();
}

void QAdaptorManager::previousRow()
{
	emit previous();
}

void QAdaptorManager::jumpRow( int idx )
{
	emit jump(idx);
}

void QAdaptorManager::setRowFromIndex( const QModelIndex &index )
{
	emit jump( index.row() );
}

