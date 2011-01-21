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
#include "block.h"
#include "dompath.h"
#include "qscaledsvgitem.h"
#include "qscaledpixmapitem.h"
#include "variantdompath.h"
#include "mindmap.h"
#include "pathshaped.h"
#include "titleeditor.h"
#include "editblockpropertycommand.h"

#include <QMenu>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QFontMetricsF>
#include <QDomElement>
#include <QGraphicsSceneMouseEvent>
#include <QUuid>
#include <QApplication>
#include <QSvgRenderer>
#include <QBuffer>
#include <QPainter>
#include <QDataStream>


#include <qdebug.h>
#include <math.h>

Block::Block( Block* parent, QGraphicsScene * scene)
: QObject( scene ), QGraphicsItemGroup(parent, scene),
	m_previous(0),
	m_active(false),
	m_topLevelNode(false),
	m_shapeType( Rectangle ),
	m_mindmap(0)
{
	m_background = 0;
	m_shapeColor = QColor(250,255,150);

	calculateUUID();

	setShapeType(m_shapeType);

	m_document = new QTextDocument(this);

	m_text = new QGraphicsTextItem(this);

	m_text->setZValue(2);
	m_titleFont = QFont("DejaVu Sans",8);

	m_emblem = new QScaledSVGItem(QLatin1String(":/emblems/clear.svg"), this);
	m_emblem->setZValue(1);

	m_emblemPX = new QScaledPixmapItem(this);
	m_emblemPX->setZValue(1);


	addToGroup( m_emblem );
	addToGroup( m_emblemPX );

	addToGroup( m_text );
	addToGroup( m_background );

	connect( document()->documentLayout(),
	                   SIGNAL(documentSizeChanged( const QSizeF &)),
	                   this,
	                   SLOT(updateContents()));
	setZValue(3);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsFocusable, false);
}

Block::~Block()
{
}

QTextDocument * Block::document( )
{
	return m_document;
}

void resizeItem( QAbstractGraphicsShapeItem *item, const QRectF &rect )
{
	if( qgraphicsitem_cast<QGraphicsEllipseItem*>( item ) != 0)
		qgraphicsitem_cast<QGraphicsEllipseItem*>( item )->setRect( rect );
	if( qgraphicsitem_cast<QGraphicsRectItem*>( item ) != 0 )
		qgraphicsitem_cast<QGraphicsRectItem*>( item )->setRect( rect );
	if( qgraphicsitem_cast<PathShaped*>( item ) != 0 )
		qgraphicsitem_cast<PathShaped*>( item )->setRect( rect );
}

void Block::updateContents( )
{
	if( !m_mindmap )
		return;

	removeFromGroup(m_background);
	removeFromGroup(m_text);

	if( m_emblem != 0 )
		removeFromGroup(m_emblem);
	if( m_emblemPX != 0 )
		removeFromGroup(m_emblemPX);

	m_text->setFont( titleFont() );

	QRectF rect = m_text->boundingRect();
	resizeItem( m_background, rect.adjusted(-10,-10,5,5) );

	QBrush brush(m_shapeColor);
	QPen pen(m_shapeColor.dark(125), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);

	if( active() )
	{
		pen.setColor(QColor(200,90,90));
		pen.setWidthF(2.5);
	}
	m_background->setBrush( brush );
	m_background->setPen(pen);

	m_emblem->hide();
	m_emblemPX->hide();

	if( !m_emblemName.isEmpty() )
	{
		if( m_mindmap->imageAttachments().contains(m_emblemName))
		{
			m_emblemPX->setPixmap( QPixmap::fromImage( m_mindmap->imageAttachment(m_emblemName) ));
			m_emblemPX->setSize( QSizeF(48, 48) );
			m_emblemPX->show();
			qreal emblemX = mapToParent(m_background->boundingRect().topRight() ).x() - m_emblemPX->size().width() / 2.0;
			qreal emblemY = mapToParent(m_background->boundingRect().topRight() ).y() - m_emblemPX->size().height() / 2.0;
			m_emblemPX->setPos(emblemX, emblemY );

		}
		else if( m_emblem->renderer()->load( m_emblemName ) )
		{
			m_emblem->setSize( QSizeF(24, 24) );
			m_emblem->show();
			qreal emblemX = mapToParent(m_background->boundingRect().topRight() ).x() - m_emblem->size().width() / 2.0;
			qreal emblemY = mapToParent(m_background->boundingRect().topRight() ).y() - m_emblem->size().height() / 2.0;
			m_emblem->setPos(emblemX, emblemY );
		}

	}

	updateConnections();

	addToGroup(m_text);
	addToGroup(m_emblem );
	addToGroup(m_emblemPX );
	addToGroup(m_background);

}

void Block::setParentNode( Block * other )
{
	if( m_previous )
	{
		m_previous->start()->m_nextNodes.removeAll(m_previous);
		scene()->removeItem(m_previous);
		delete m_previous;
	}

	if( other )
	{
		Connector *conn = new Connector();
		conn->setLineType( Connector::Spline );
		conn->setStart( other );
		conn->setEnd( this );
		conn->setZValue( -1 );
		m_previous = conn;
		other->m_nextNodes << conn;
		m_path = other->path();
		m_path << index();
		scene()->addItem(conn);
	}
	else
	{
		m_path.clear();
		m_previous = 0;
	}
}

QVariant Block::itemChange( GraphicsItemChange change, const QVariant & value )
{
	QVariant result;
	if( change == QGraphicsItem::ItemPositionChange)
	{
		result = QGraphicsItemGroup::itemChange(change,value);
	}
	else if( change == QGraphicsItem::ItemSelectedChange )
	{
		setActive(value.toBool());
		result = value;
	}
	else
		result = QGraphicsItemGroup::itemChange(change,value);

	return result;
}

void Block::updateConnections( )
{
	foreach( Connector *conn, m_nextNodes )
		conn->updatePath();
	if( m_previous )
		m_previous->updatePath();
}

void Block::setText( const QString & text )
{
	m_document->setPlainText(text);
}

QString Block::text( ) const
{
	return m_document->toPlainText();
}

bool Block::active() const
{
	return m_active;
}


void Block::setActive( bool theValue )
{
	m_active = theValue;
	updateContents();
}

int Block::index( ) const
{
	if( m_previous)
		return m_previous->start()->m_nextNodes.indexOf(m_previous);
	else
		return 0;
}

void Block::setIndex( int idx )
{
	int currentIndex = index();
	if( m_previous)
	{
		if( currentIndex != idx )
			m_previous->start()->m_nextNodes.swap( idx, currentIndex);
	}
}

int Block::maxIndex( ) const
{
	if( m_previous)
		return m_previous->start()->m_nextNodes.count() - 1;
	else
		return 0;
}

QList< Block * > Block::children( ) const
{
	QList<Block*> nodes;
	foreach( Connector *conn, m_nextNodes)
		nodes << conn->end();

	return nodes;
}

Block * Block::parent( )  const
{
	if( m_previous )
		return m_previous->start();
	else
		return 0;
}



void Block::saveBlock( SxDomUtils::DomPath &blockPath,
                       SxDomUtils::DomPath &connPath,
                       bool pasteBuffer )
{
	blockPath.setValue( QLatin1String("node/geometry.x"), QString::number(x()) );
	blockPath.setValue( QLatin1String("node/geometry.y"), QString::number(y()) );
	blockPath.setValue( QLatin1String("node/geometry.z"), QString::number(zValue()) );

	VariantDomPath propertyPath( blockPath.elementInPath(), "node/properties" );
	propertyPath.saveProperties(properties());

	if( pasteBuffer )
		blockPath.setValue( "node.id", id() + "-buffer");
	else
		blockPath.setValue( QLatin1String("node.id"), id());

	blockPath.setValue( QLatin1String("node.toplevel"), QString::number(m_topLevelNode));

	QString startPathTemplate = QLatin1String("connection/node[%1].start");
	QString endPathTemplate = QLatin1String("connection/node[%1].end");

	int index = 0;
	if( m_nextNodes.count() == 0 )
		connPath.removeElement();
	else
	{
		foreach( Connector *conn, m_nextNodes)
		{
			if( pasteBuffer )
			{
				connPath.setValue( startPathTemplate.arg(index),  conn->start()->id() + QLatin1String("-buffer") );
				connPath.setValue( endPathTemplate.arg(index),  conn->end()->id() + QLatin1String("-buffer")  );
			}
			else
			{
				connPath.setValue( startPathTemplate.arg(index),  conn->start()->id() );
				connPath.setValue( endPathTemplate.arg(index),  conn->end()->id() );
			}

			++index;
		}
	}
}

Block *Block::loadBlock( const SxDomUtils::DomPath &blockPath, QGraphicsScene *parentScene )
{
	if( !blockPath.getValue(QLatin1String("node.id")).isEmpty() )
	{
		VariantDomPath propertyPath( blockPath.elementInPath(), "node/properties" );
		QPointF newPos;
		Block *newNode = new Block();
		newNode->setId( blockPath.getValue(QLatin1String("node.id")).toLatin1() );
		newNode->setTopLevelNode( blockPath.getValue(QLatin1String("node.toplevel")).toInt() );
		newNode->setProperties( propertyPath.loadProperties() );
		newPos.setX( blockPath.getValue(QLatin1String("node/geometry.x")).toDouble() );
		newPos.setY( blockPath.getValue(QLatin1String("node/geometry.y")).toDouble() );
		newNode->setPos( newPos );
		parentScene->addItem(newNode);
		return newNode;
	}
	else
		return 0;
}



void Block::placeChildren(qreal angleStart, qreal angleEnd)
{

	qreal totalsize = recursiveChildCount();
	qreal substart = angleStart;
	qreal subend = 0.0;

	foreach( Connector  *conn, m_nextNodes )
	{
		Block *block = conn->end();
		qreal subsize = block->recursiveChildCount();
		subend = substart + (subsize * (angleEnd-angleStart)) / totalsize;

		qreal angle = substart + (subend - substart)/2.0;
		QPointF newPoint( 	x() + boundingRect().width()/2.0 - block->boundingRect().width()/2.0 + 130.0*cos( angle),
							y() + boundingRect().height()/2.0 - block->boundingRect().height()/2.0 + 130.0*sin( angle) );

		qDebug() << angle << newPoint << mapToScene( newPoint ) << mapToParent( newPoint );
		block->setPos( newPoint );

		block->placeChildren(substart, subend);

		substart = subend;
	}

	updateConnections();
}

QPointF Block::connection(  Side side ) const
{
	switch(side)
	{
		case Right:
			return mapToScene(
					QPointF( m_background->boundingRect().right(), m_background->boundingRect().center().y())
					);
		break;
		case Left:
			return mapToScene(
					QPointF( m_background->boundingRect().left(), m_background->boundingRect().center().y())
					);
		break;
		case Top:
			return mapToScene(
					QPointF( m_background->boundingRect().center().y(), m_background->boundingRect().top())
					);
		break;
		case Bottom:
			return mapToScene(
					QPointF( m_background->boundingRect().center().y(), m_background->boundingRect().bottom())
					);
		break;
		default:
			return mapToScene(
					QPointF( m_background->boundingRect().center().x(), m_background->boundingRect().center().y())
					);
		break;
	}
}

void Block::detatch( )
{
	if( m_previous )
		m_previous->start()->m_nextNodes.removeAll(m_previous);

	foreach( Connector *conn, m_nextNodes )
		conn->end()->m_previous = 0;

	qDeleteAll(m_nextNodes);
	delete m_previous;

}



QList< int > Block::path() const
{
	QList< int > result;
	const Block *current = this;
	while( current != 0 )
	{
		result.prepend(  current->index() + 1 );
		current = current->parent();
		if( current == this )
			break;
	}
	return result;
}

Block * Block::child( int index )
{
	return m_nextNodes.at(index)->end();
}

void Block::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
	// TODO: do not send delta until the move is complete.
	if ((event->buttons() & Qt::LeftButton) && (flags() & ItemIsMovable))
	{
        // Handle ItemIsMovable.
		QPointF newPos(mapToParent(event->pos()) - matrix().map(event->buttonDownPos(Qt::LeftButton)));
		QPointF diff = newPos - pos();
		emit itemMoved( diff );
		event->accept();
	}
}

void Block::mouseReleaseEvent( QGraphicsSceneMouseEvent * event )
{
    Q_UNUSED(event);
    if( isSelected() )
        emit selectionChanged();
}

void Block::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
    if( event->modifiers() == Qt::ControlModifier )
    {
        setSelected( !isSelected() );
    }
    else
    {
        if( isSelected() )
            return;

        scene()->clearSelection();
        setSelected( true );
    }
    event->accept();
}

void Block::setProperty( const QString & name, const QVariant & value )
{
	if( name == QLatin1String("title"))
		setTitle(value.toString());
	else if( name == QLatin1String("text"))
		setText(value.toString());
	else if( name == QLatin1String("index"))
		setIndex(value.toInt());
	else if( name == QLatin1String("position"))
		setPos(value.value<QPointF>());
	else if( name == QLatin1String("color") )
		setShapeColor(value.value<QColor>());
	else if( name == QLatin1String("font") )
		setTitleFont(value.value<QFont>());
	else if( name == QLatin1String("emblem") )
		setEmblem(value.value<QString>());
	else if( name == QLatin1String("shapetype") )
		setShapeType( (Shape) value.value<int>());
	else
		m_properties[name] = value;
}

QVariant Block::getProperty( const QString & name ) const
{
	if( name == QLatin1String("title"))
		return title();
	else if( name == QLatin1String("text"))
		return text();
	else if( name == QLatin1String("index"))
		return index();
	else if( name == QLatin1String("position"))
		return pos();
	else if( name == QLatin1String("color"))
		return shapeColor();
	else if( name == QLatin1String("font") )
		return titleFont();
	else if( name == QLatin1String("emblem") )
		return emblem();
	else if( name == QLatin1String("shapetype") )
		return (int)shapeType();
	else
		return m_properties[name];
}

void Block::removeProperty( const QString & name )
{
	m_properties.remove(name);
}

int Block::propertyCount( ) const
{
	return propertyNames( ).count();
}

QStringList Block::propertyNames( ) const
{
	QStringList keys;
	keys << "title" <<"text" << "index" << "position" << "font" << "color" << "emblem" << "shapetype" << m_properties.keys();
	return keys;
}

void Block::setTitle( const QString & title )
{
	m_text->setPlainText(title);
	updateContents();
}

QString Block::title( ) const
{
	return m_text->toPlainText();
}

int Block::childCount() const
{
	return m_nextNodes.count();
}

int Block::recursiveChildCount() const
{
	int count = childCount();
	foreach( Connector* conn, m_nextNodes)
		count += conn->end()->recursiveChildCount();
	return count;
}

QByteArray Block::id() const
{
	return m_id;
}

int Block::type( ) const
{
	return Type;
}


void Block::setId( const QByteArray& theValue )
{
	m_id = theValue;
}

QByteArray Block::pathString( ) const
{
	QStringList stringRepresentation;
	const Block *current = this;
	while( current != 0 )
	{
		stringRepresentation.prepend( QString::number( current->index() + 1) );
		current = current->parent();
	}
	return stringRepresentation.join(".").toLatin1();
}


bool Block::topLevelNode() const
{
	return m_topLevelNode;
}


void Block::setTopLevelNode( bool theValue )
{
	m_topLevelNode = theValue;
}

void Block::calculateUUID( )
{
	m_id = QUuid::createUuid ().toString().toLatin1();
}

QColor Block::shapeColor() const
{
	return m_shapeColor;
}


void Block::setShapeColor(const QColor& theValue)
{
	m_shapeColor = theValue;
	updateContents( );
}


QFont Block::titleFont() const
{
	return m_titleFont;
}


void Block::setTitleFont(const QFont& theValue)
{
	m_titleFont = theValue;
	updateContents( );
}


QString Block::emblem() const
{
	return m_emblemName;
}


void Block::setEmblem(const QString& theValue)
{
	m_emblemName = theValue;
	updateContents( );
}

void Block::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
    Q_UNUSED(painter);
    Q_UNUSED(widget);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


QHash< QString, QVariant > Block::properties() const
{
	QHash<QString,QVariant> returnProperties;
	foreach( QString propertyName, propertyNames() )
		returnProperties[propertyName] = getProperty(propertyName);
	return returnProperties;
}

void Block::setProperties(const QHash< QString, QVariant >& theValue)
{
	foreach( QString propertyName, theValue.keys() )
		setProperty(propertyName, theValue[propertyName]);
}

QRectF Block::boundingRect( ) const
{
	if( m_background )
		return m_background->boundingRect();
	else
		return QGraphicsItemGroup::boundingRect();
}



void Block::advance( int phase )
{
    Q_UNUSED(phase);
    QRectF sceneRect = scene()->sceneRect();
    QPointF newPos = pos() + m_delta;
    newPos.setX(qMin(qMax(newPos.x(), sceneRect.left() + 10), sceneRect.right() - 10));
    newPos.setY(qMin(qMax(newPos.y(), sceneRect.top() + 10), sceneRect.bottom() - 10));
    setPos(newPos);
    updateConnections();
}


MindMap *Block::mindmap() const
{
	return m_mindmap;
}


void Block::setMindmap( MindMap* theValue)
{
	m_mindmap = theValue;
	connect( this, SIGNAL(newNode(Block *, const QPointF& )),
			m_mindmap, SLOT(createNode(Block *, const QPointF& )));
	connect( this, SIGNAL(selectionChanged( )),
				m_mindmap, SLOT(itemSelectionChanged()));
	connect( this, SIGNAL(itemMoved( const QPointF& )),
			m_mindmap, SLOT(moveSelection( const QPointF& )));
}

QTextDocument * Block::titleDocument( )
{
	return m_text->document();
}

void Block::drawEmblemImage( const QRectF & size, QPainter * painter ) const
{
	QSvgRenderer *renderer = m_emblem->renderer();
	QSizeF source;
	QSizeF correctedSize;
	QSizeF imageSize;
	if( m_emblemName.startsWith(":/emblem"))
	{
		imageSize = source = renderer->defaultSize();
		imageSize.scale( 800, 600, Qt::KeepAspectRatio );
	}
	else
		imageSize = source = m_mindmap->imageAttachment(m_emblemName).size();

	correctedSize = source;
	correctedSize.scale( size.size(), Qt::KeepAspectRatio);

	qreal xscaleImage =  imageSize.width() / source.width();
	qreal yscaleImage =  imageSize.height() / source.height() ;
	qreal xscale =  correctedSize.width() / imageSize.width();
	qreal yscale =  correctedSize.height() / imageSize.height() ;

	QImage image( imageSize.toSize(), QImage::Format_ARGB32_Premultiplied );
	image.fill(qRgba(255,255,255,0));
	QPainter imagePainter( &image );
	imagePainter.scale( xscaleImage, yscaleImage );
	if( m_emblemName.startsWith(":/emblem"))
		renderer->render( &imagePainter, renderer->viewBox() );
	else
		imagePainter.drawImage(0,0,m_mindmap->imageAttachment(m_emblemName));
	imagePainter.end();

	qreal xoffset = ( size.width() - correctedSize.width() )/2;
	qreal yoffset = ( size.height() - correctedSize.height() )/2;

	painter->save();
	painter->translate( size.topLeft().x() + xoffset, size.topLeft().y() + yoffset );
	painter->scale(xscale,yscale);
	painter->drawImage(0,0,image);
	painter->restore();
}


Block::Shape Block::shapeType() const
{
	return m_shapeType;
}


void Block::setShapeType( const Shape& theValue )
{
	m_shapeType = theValue;
	delete m_background;
	switch ( theValue )
	{
	case Rectangle:
		m_background = new QGraphicsRectItem(this, scene() );
		break;
	case Ellipse:
		m_background = new QGraphicsEllipseItem(this, scene() );
		break;
	case Path:
		m_background = new PathShaped(this, scene() );
		break;
	};
	m_background->setZValue(0);
	updateContents();

}

qreal Block::calculateNewXPos( Block *item, bool right ) const
{
		qreal binspace = 50.0;
		if (right)
			return x() + boundingRect().width() + binspace;
		else
			return  x() - item->boundingRect().width() - binspace;

}

void Block::placeChildren( const QPointF & pos, bool right )
{
	qreal nesting = 10.0;
	qreal tmpsize = recursiveChildHeight();
	qreal starty = pos.y();
	qreal newx = pos.x();
	qreal newy = 0;

	if (right )
		newy = pos.y()+(0 - tmpsize + nesting)/2-boundingRect().height()/2;
	else
		newy = pos.y()+(tmpsize-nesting)/2-boundingRect().height()/2;

	setPos(newx, newy);

	if ( childCount() <= 0 )
		return;

	foreach( Block *citem, children() )
	{
		qreal xpos = calculateNewXPos(citem, right);

		citem->placeChildren(QPointF(xpos, starty), right);

		if (right) starty -= citem->recursiveChildHeight();
		else starty += citem->recursiveChildHeight();
	}
	updateConnections();

}

qreal Block::recursiveChildHeight( ) const
{
	qreal nesting = 10.0;
	if ( childCount() > 0 )
	{
		qreal size = 0;
		foreach( const Block *citem, children() )
			size += citem->recursiveChildHeight();

		if (size > boundingRect().height() + nesting)
			return size;
		else
			return boundingRect().height() + nesting;
	}

	return boundingRect().height() + nesting;
}

QSizeF Block::naturalEmblemSize( ) const
{
	QSizeF imageSize;
	if( m_emblemName.startsWith(":/emblem"))
	{
		imageSize = m_emblem->renderer()->defaultSize();
	}
	else
		imageSize = m_mindmap->imageAttachment(m_emblemName).size();

	return imageSize;
}
