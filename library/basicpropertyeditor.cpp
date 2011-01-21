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
#include "basicpropertyeditor.h"
#include "blockpropertymodel.h"
#include "qadaptormanager.h"
#include "mindmap.h"
#include "ui_contents.h"
#include "block.h"
#include "rotatedproxymodel.h"

#include <QPainter>
#include <QLinearGradient>
#include <QBrush>
#include <QStandardItemModel>


MODEL_ADAPTOR( SpellcheckedLineEditAdaptor, "text", SIGNAL(editingFinished()));
MODEL_ADAPTOR( PlainTextEditAdaptor, "text", SIGNAL(editingFinished()));
MODEL_ADAPTOR( ColorButtonAdaptor, "color", SIGNAL(colorChanged( const QColor &)));

BasicPropertyEditor::BasicPropertyEditor(MindMap * mindmap, QWidget * parent): QDialog(parent), m_blockPropertyManager(0)
{
	m_contents = new Ui::ContentsWidget();

	setWindowTitle(QLatin1String("Contents"));
	m_contents->setupUi(this);

	connect( mindmap, SIGNAL(modelChanged(BlockPropertyModel*)),
					this, SLOT(setupModel(BlockPropertyModel *)));
	connect( mindmap, SIGNAL(maxIndex( int )),
	                 this, SLOT(updateMaximumIndex(int)));

	foreach( QString property, properties())
		mindmap->propertyModel()->addProperty(property);

	m_shapes = new QStandardItemModel(3, 2, this);
	m_shapes->setHeaderData(0, Qt::Horizontal, tr("Shape") );
	m_shapes->setData(m_shapes->index( 0, 0 ), tr("Topic") );
	m_shapes->setData(m_shapes->index( 0, 0 ), QIcon(":/images/topic.svg"), Qt::DecorationRole );
	m_shapes->setData(m_shapes->index( 0, 1 ), (int)Block::Ellipse );
	m_shapes->setData(m_shapes->index( 1, 0 ), tr("Idea") );
	m_shapes->setData(m_shapes->index( 1, 0 ), QIcon(":/images/idea.svg"), Qt::DecorationRole );
	m_shapes->setData(m_shapes->index( 1, 1 ), (int)Block::Rectangle );
	m_shapes->setData(m_shapes->index( 2, 0 ), tr("Supporting Idea") );
	m_shapes->setData(m_shapes->index( 2, 0 ), QIcon(":/images/supporting_idea.svg"), Qt::DecorationRole );
	m_shapes->setData(m_shapes->index( 2, 1 ), (int)Block::Path );

	m_proxyModel = new RotatedProxyModel(this);

}


BasicPropertyEditor::~BasicPropertyEditor()
{
	delete m_contents;
}

void BasicPropertyEditor::updateMaximumIndex( int index )
{
	m_contents->objectOrder->setMaximum( index );
}


void BasicPropertyEditor::setupModel( BlockPropertyModel * model )
{
	delete m_blockPropertyManager;

	m_blockPropertyManager = new QModelAdaptor::QAdaptorManager( model );
	m_blockPropertyManager->setAdaptorFactory("SpellcheckedLineEdit",
		new QModelAdaptor::QAdaptorFactory< QModelAdaptor::SpellcheckedLineEditAdaptor>());
	m_blockPropertyManager->setAdaptorFactory("PlainTextEdit",
		new QModelAdaptor::QAdaptorFactory< QModelAdaptor::PlainTextEditAdaptor>());
	m_blockPropertyManager->setAdaptorFactory("ColorButton",
		new QModelAdaptor::QAdaptorFactory< QModelAdaptor::ColorButtonAdaptor>());

	m_blockPropertyManager->bindWidget(m_contents->objectTitle, QLatin1String("title"));
	m_blockPropertyManager->bindWidget(m_contents->objectText, QLatin1String("text"));
	m_blockPropertyManager->bindWidget(m_contents->objectOrder, QLatin1String("index"));
	m_blockPropertyManager->bindWidget(m_contents->objectColor, QLatin1String("color"));
	m_blockPropertyManager->bindWidget(m_contents->objectFont, QLatin1String("font"));
	m_blockPropertyManager->bindWidget(m_contents->shapeSelection, QLatin1String("shapetype"));
	m_blockPropertyManager->bindContentModel( m_contents->shapeSelection, m_shapes, 1, 0 );

	m_proxyModel->setSourceModel( model );
	m_contents->propertyEditor->setModel( m_proxyModel );

	m_blockPropertyManager->firstRow();
}

QStringList BasicPropertyEditor::properties() const
{
	QStringList properties;
	properties << "title" << "text" << "index" << "color" << "font" << "emblem" << "shapetype";
	return properties;
}

