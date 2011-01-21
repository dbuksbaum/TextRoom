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
#include "mindmapview.h"
#include "mindmap.h"
#include "block.h"
#include "blockpropertymodel.h"
#include "basicpropertyeditor.h"
#include "titleeditor.h"

#include <math.h>

#include <QRubberBand>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QApplication>
#include <QGLWidget>
#include <QSettings>
#include <QScrollBar>
#include <QWheelEvent>

#include <qdebug.h>


MindMapView::MindMapView( QWidget* parent )
: QGraphicsView( parent ), m_connector(0), m_mode(None), m_startBlock(0), m_endBlock(0)
{
	QSettings settings;
	if( QGLFormat::hasOpenGL() && settings.value("MainWindow/OpenGL", false).toBool() )
		setViewport( new QGLWidget() );

	setRenderHint(QPainter::Antialiasing);
}


MindMapView::~MindMapView()
{

}


void MindMapView::mouseMoveEvent( QMouseEvent* event )
{
	if (dragMode() == QGraphicsView::RubberBandDrag && mode() == Reparent )
	{
		if( m_startBlock != 0 )
		{
			if( m_connector == 0 )
			{
				QPen pen(Qt::red, 3, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
				m_connector =  new QGraphicsLineItem(  );
				m_connector->setPen(pen);
				scene()->addItem(m_connector);
				m_connector->setZValue(5);
			}
			QLineF line(m_startBlock->connection(Block::Center), mapToScene(event->pos()));
			m_connector->setLine(line);

			if (!m_connector->isVisible())
				m_connector->show();

			m_connector->update();
			event->setAccepted(true);
			return;
		}
	}
	else if(  mode() == Pan )
	{
		int dx =  event->pos().x() - m_lastPoint.x();
		int dy = event->pos().y() - m_lastPoint.y();
		m_lastPoint = event->pos();
		verticalScrollBar()->setValue(verticalScrollBar()->value() - dy);
		horizontalScrollBar()->setValue( horizontalScrollBar()->value() - dx);
		event->setAccepted(true);
	}

	QGraphicsView::mouseMoveEvent( event );
}

void MindMapView::mousePressEvent( QMouseEvent* event )
{

	if ( event->button() == Qt::LeftButton )
	{
		if (dragMode() == QGraphicsView::RubberBandDrag && mode() == Reparent)
		{
			foreach( QGraphicsItem *item, items( event->pos() ) )
			{
				Block *block = qgraphicsitem_cast<Block*>(item);
				if( block )
				{
					m_startPoint = event->pos();
					m_startBlock = block;
					event->setAccepted(true);
					return;
				}
			}
			setMode(None);
		}

		if( mode() == None )
		{
			foreach( QGraphicsItem *item, items( event->pos() ) )
			{
				Block *block = qgraphicsitem_cast<Block*>(item);
				if( block )
				{
					QGraphicsView::mousePressEvent( event );
					emit selectionChanged();
					return;
				}
			}
			setMode( Select );
			QGraphicsView::mousePressEvent( event );
		}
	}
	else if( event->button() == Qt::RightButton && items(event->pos()).size() == 0 )
	{
		setMode(Pan);
		m_lastPoint = event->pos();
		event->setAccepted(true);
	}
	else
		QGraphicsView::mousePressEvent( event );

}

void MindMapView::mouseReleaseEvent( QMouseEvent* event )
{
	if (dragMode() == QGraphicsView::RubberBandDrag)
	{
		if (m_mode == Reparent)
		{
			setMode(None);

			scene()->removeItem(m_connector);
			delete m_connector;
			m_connector = 0;
			m_endPoint = event->pos();

			foreach( QGraphicsItem *item, items( m_endPoint ) )
			{
				Block *block = qgraphicsitem_cast<Block*>(item);
				if( block )
				{
					m_endBlock = block;
					emit reparentBlocks( m_startBlock, m_endBlock);
				}
			}

			m_endBlock = 0;
			m_startBlock = 0;
			return;
		}
		else if( m_mode == Select )
		{
			QGraphicsView::mouseReleaseEvent( event );
			emit selectionChanged();
			setMode( None );
		}

	}
	else if( m_mode == Pan )
	{
		setMode(None);
		event->accept();
	}
	else
		QGraphicsView::mouseReleaseEvent( event );
}

MindMapView::DragMode MindMapView::mode() const
{
	return m_mode;
}


void MindMapView::setMode(const DragMode& theValue)
{
	m_mode = theValue;
	if( m_mode == None )
	{
		QApplication::restoreOverrideCursor();
		setDragMode( QGraphicsView::NoDrag );
	}
	if( m_mode == Reparent || m_mode == Select)
	{
		QApplication::setOverrideCursor(Qt::CrossCursor);
		setDragMode( QGraphicsView::RubberBandDrag );
	}
	if( m_mode == Pan )
	{
		QApplication::setOverrideCursor(Qt::ClosedHandCursor);
		setDragMode( QGraphicsView::NoDrag );
	}
}

void MindMapView::updateMatrix( )
{
	qreal scale = ::pow(2.0, (m_zoomView - 100.0) / 50.0);

	QMatrix matrix;
	matrix.scale(scale, scale);

	setMatrix(matrix);
	if( m_mindmap->selectedNode() )
		centerOn( m_mindmap->selectedNode() );
	else
		centerOn( m_mindmap->root() );
}


qreal MindMapView::zoomView() const
{
	return m_zoomView;
}

void MindMapView::setZoomView(const int& theValue)
{
	m_zoomView = theValue;
	updateMatrix();
}

void MindMapView::keyPressEvent( QKeyEvent * event )
{
	QApplication::restoreOverrideCursor();
	Block *block = m_mindmap->selectedNode();
	if( block )
	{
		if( event->key() == Qt::Key_Escape )
		{
			m_mindmap->clearSelection();
			event->accept();
		}
		else if( event->key() == Qt::Key_Control || event->key() == Qt::Key_Alt )
		{
			QGraphicsView::keyPressEvent( event );
			event->accept();
		}
		else if( event->key() == Qt::Key_Left )
		{
			m_mindmap->moveSelection( QPointF(-1,0) );
			event->accept();
		}
		else if( event->key() == Qt::Key_Right )
		{
			m_mindmap->moveSelection( QPointF(1,0) );
			event->accept();
		}
		else if( event->key() == Qt::Key_Up )
		{
			m_mindmap->moveSelection( QPointF(0,-1) );
			event->accept();
		}
		else if( event->key() == Qt::Key_Down )
		{
			m_mindmap->moveSelection( QPointF(0,1) );
			event->accept();
		}
		else
		{
			QGraphicsView::keyPressEvent( event );
		}
	}
	else
		QGraphicsView::keyPressEvent( event );

}

void MindMapView::mouseDoubleClickEvent( QMouseEvent * event )
{
	QApplication::restoreOverrideCursor();
	if( items( event->pos() ).count() == 0)
	{
		m_mindmap->createNode( m_mindmap->root(), mapToScene(event->pos()) );
	}
	else if( event->button() == Qt::LeftButton )
	{
		Block *block = m_mindmap->selectedNode();
		if( block )
		{
			TitleEditor *editor = new TitleEditor( this );
			editor->setPropertyModel( m_mindmap->propertyModel() );
			editor->move( mapFromScene( block->pos().toPoint() ) );
			editor->startEditing();
		}
	}
	else
		QGraphicsView::mouseDoubleClickEvent(event);
}


MindMap* MindMapView::mindmap() const
{
	return m_mindmap;
}


void MindMapView::setMindmap(MindMap* theValue)
{
	m_mindmap = theValue;
}

bool MindMapView::event( QEvent * event )
{
	switch( event->type() ){
		case QEvent::KeyPress: {
			keyPressEvent((QKeyEvent *)event);
			return true;
			break;
		}
		default:
			return QGraphicsView::event(event);
	};
}

void MindMapView::wheelEvent( QWheelEvent * event )
{
	if( event->modifiers() == Qt::ControlModifier )
		zoomLevelChanged( m_zoomView + (event->delta() / 10.0) );
	else
		QGraphicsView::wheelEvent( event );		
}
