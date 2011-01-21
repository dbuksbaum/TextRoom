/***************************************************************************
*   Copyright (C) 2006 by Ian Reinhart Geiser   *
*   geiseri@yahoo.com   *
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
#ifndef MINDMAPVIEW_H
#define MINDMAPVIEW_H

#include <QGraphicsView>

class QGraphicsLineItem;
class Block;
class MindMap;
class TitleEditor;
class QResizeEvent;
class BasicPropertyEditor;
/**
This is a special implementation of the QGraphicsView that will handle connection of blocks as well as selection and panning.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class MindMapView : public QGraphicsView
{
	Q_OBJECT
public:
	enum DragMode{ None, Reparent, Select, Pan };
	MindMapView( QWidget* parent );

	~MindMapView();

	void setMode(const DragMode& theValue);
	DragMode mode() const;

	qreal zoomView() const;
protected:
	void mouseMoveEvent( QMouseEvent* event );
	void mousePressEvent( QMouseEvent* event );
	void mouseReleaseEvent( QMouseEvent* event );
	void wheelEvent ( QWheelEvent * event );
	void keyPressEvent ( QKeyEvent * event );
	void mouseDoubleClickEvent ( QMouseEvent * event );
	bool event ( QEvent * event );

public slots:
	void setZoomView(const int& theValue);

	void setMindmap(MindMap* theValue);
	MindMap* mindmap() const;

signals:
	void reparentBlocks( Block *newParent, Block *child);
	void selectionChanged();
	void zoomLevelChanged( int newValue );

private:
	void updateMatrix();
	QGraphicsLineItem *m_connector;
	DragMode m_mode;
	QPoint m_startPoint;
	QPoint m_endPoint;
	QPoint m_lastPoint;
	Block *m_startBlock;
	Block *m_endBlock;

	qreal m_zoomView;
	MindMap *m_mindmap;
};

#endif
