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
#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QGraphicsItemGroup>
#include <QPointF>
#include <QList>
#include <QHash>
#include <QFont>
#include <QIcon>

#include "connector.h"

class QTextDocument;
class QGraphicsScene;
class QGraphicsTextItem;
class QGraphicsRectItem;
class QScaledSVGItem;
class QScaledPixmapItem;
class QDomElement;
class Block;
class MindMap;

namespace SxDomUtils
{
	class DomPath;
}

/**
A node that displays a thought.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class Block : public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
public:
		enum { Type = UserType + 1 };
		enum Side {Left,Right,Top,Bottom,Center};
		enum Shape { Rectangle = 0, Ellipse = 1, Path = 2 };

	Block( Block* parent = 0, QGraphicsScene * scene = 0 );
	~Block();

	virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
	virtual void advance ( int phase );
	QTextDocument *document();

	void setParentNode( Block *other );

	QPointF connection( Side side ) const;
	void setActive( bool theValue );
	bool active() const;

	int maxIndex( ) const;

	QList<Block*> children() const;
	Block *child( int index ) ;
	Block *parent() const;

	void saveBlock(SxDomUtils::DomPath &blockPath,
	               SxDomUtils::DomPath &connPath,
	              bool pasteBuffer = false);
	static Block *loadBlock(  const SxDomUtils::DomPath &blockPath, QGraphicsScene *parentScene   );

	QList< int > path() const;
	QByteArray pathString() const;

	void setProperty( const QString &name, const QVariant &value );
	QVariant getProperty( const QString &name ) const;
	void removeProperty( const QString &name );
	int propertyCount( ) const;
	QStringList propertyNames() const;

	void setTitle( const QString &title );
	QString title( ) const;
	QTextDocument *titleDocument();

	void setText( const QString &text );
	QString text( ) const;

	void setShapeColor(const QColor& theValue);
	QColor shapeColor() const;

	void setTitleFont(const QFont& theValue);
	QFont titleFont() const;

	void setEmblem(const QString& emblemPath);
	QString emblem() const;
	void drawEmblemImage( const QRectF &size, QPainter *painter) const;
	QSizeF naturalEmblemSize( ) const;

	int index() const;
	void setIndex( int index);

	int childCount() const;
	int recursiveChildCount() const;
	qreal recursiveChildHeight() const;
	qreal calculateNewXPos( Block *item, bool right ) const;

	int type() const;
	QByteArray id() const;
	void setId( const QByteArray& theValue );
	void setTopLevelNode( bool theValue );
	bool topLevelNode() const;

	QRectF boundingRect () const;
	/**
	 *    Regenerate the blocks UUID.  Note you should NEVER call this method once there are undo/redo operations.
	 */
	void calculateUUID();
	void setMindmap( MindMap* theValue);
	MindMap *mindmap() const;


public slots:
	void updateContents();
	void updateConnections();
	void placeChildren(qreal startAngle, qreal endAngle);
	void placeChildren(const QPointF &pos, bool right );
	void detatch();

	void setProperties(const QHash< QString, QVariant >& theValue);


	QHash< QString, QVariant > properties() const;

	void setShapeType( const Shape& theValue );
	Shape shapeType() const;


signals:
	void newNode( Block *parent, const QPointF &pos);
	void selectionChanged( );
	void itemMoved( const QPointF &delta );

protected:
	virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mousePressEvent ( QGraphicsSceneMouseEvent * event );
	virtual QVariant itemChange( GraphicsItemChange change, const QVariant & value );
	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent * event );

private:

	QGraphicsTextItem *m_text;
	QAbstractGraphicsShapeItem *m_background;

	QList<Connector*> m_nextNodes;
	Connector* m_previous;
	bool m_active;

	QTextDocument *m_document;
	QList<int> m_path;
	QHash<QString,QVariant> m_properties;
	QByteArray m_id;
	bool m_topLevelNode;

	QColor m_shapeColor;
	QFont m_titleFont;
	QString m_emblemName;
	Shape m_shapeType;

	QScaledSVGItem *m_emblem;
	QScaledPixmapItem *m_emblemPX;
	QPointF m_delta;
	MindMap *m_mindmap;
};

#endif
