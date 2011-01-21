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


#include "shapeselector.h"
#include "block.h"
#include <QStandardItemModel>
#include <QIcon>

ShapeSelector::ShapeSelector( QWidget* parent, Qt::WFlags fl )
		: QDialog( parent, fl ), Ui::ShapeSelector()
{
	QStandardItemModel *shapes = new QStandardItemModel(3, 2, this);
	shapes->setHeaderData(0, Qt::Horizontal, tr("Shape") );
	shapes->setData(shapes->index( 0, 0 ), tr("Topic") );
	shapes->setData(shapes->index( 0, 0 ), QIcon(":/images/topic.svg"), Qt::DecorationRole );
	shapes->setData(shapes->index( 0, 1 ), (int)Block::Ellipse );
	shapes->setData(shapes->index( 1, 0 ), tr("Idea") );
	shapes->setData(shapes->index( 1, 0 ), QIcon(":/images/idea.svg"), Qt::DecorationRole );
	shapes->setData(shapes->index( 1, 1 ), (int)Block::Rectangle );
	shapes->setData(shapes->index( 2, 0 ), tr("Supporting Idea") );
	shapes->setData(shapes->index( 2, 0 ), QIcon(":/images/supporting_idea.svg"), Qt::DecorationRole );
	shapes->setData(shapes->index( 2, 1 ), (int)Block::Path );
	setupUi( this );
	shapeType->setModel( shapes );
}

ShapeSelector::~ShapeSelector()
{
}

void ShapeSelector::on_shapeType_currentIndexChanged( int index )
{
	QAbstractItemModel *model = shapeType->model();
	shapePreview->setPixmap( model->data( model->index(index,0), Qt::DecorationRole ).value<QIcon>().pixmap( shapePreview->size() ) );
}

int ShapeSelector::currentShapeType( ) const
{
	QAbstractItemModel *model = shapeType->model();
	return model->data( model->index(shapeType->currentIndex(),1) ).toInt();
}

void ShapeSelector::setCurrentShapeType( int type )
{
	QAbstractItemModel *model = shapeType->model();
	QModelIndexList indexes = model->match ( model->index(0,1), Qt::DisplayRole, type );
	QModelIndex index  = indexes.value(0);
	shapeType->setCurrentIndex( index.row() );
}



