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
#include "connector.h"
#include "block.h"
#include <QGraphicsScene>
#include <QPainterPath>
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QLineF>
#include <QGradient>

#include <math.h>

static const double Pi = 3.14159265358979323846264338327950288419717;

Connector::Connector(QGraphicsItem * parent, QGraphicsScene * scene)
	: QGraphicsPathItem( parent, scene ), m_start(0),
	m_end(0), m_type(Connector::Spline)
{
	QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	setPen(pen);
	updatePath();
}

Connector::~Connector()
{}

Block *Connector::start()
{
	return m_start;
}


void Connector::setStart( Block *theValue )
{
	m_start = theValue;
	updatePath();
}


Block *Connector::end()
{
	return m_end;
}


void Connector::setEnd( Block *theValue )
{
	m_end = theValue;
	updatePath();
}

void Connector::updatePath( )
{
	if( m_start == 0 || m_end == 0 )
		return;

	QPainterPath myPath;
	qreal x = m_start->connection(Block::Center).x();
	qreal y = m_start->connection(Block::Center).y();
	qreal a = m_end->connection(Block::Center).x();
	qreal b = m_end->connection(Block::Center).y();
	QLineF line(m_start->connection(Block::Center),m_end->connection(Block::Center));
	QLineF baseLine(x,y,x+100.0,y);
	qreal theta = line.angle(baseLine);
	bool renderTopBottom = false;
	qreal leftAngle = 100;
	qreal rightAngle = 80;

	if( theta < rightAngle )
	{
		x = m_start->connection(Block::Right).x();
		a = m_end->connection(Block::Left).x();
	}
	else if( theta > rightAngle  && theta < leftAngle )
	{
		if( y > b )
		{
			y = m_start->connection(Block::Top).y();
			b = m_end->connection(Block::Bottom).y();
		}
		else
		{
			y = m_start->connection(Block::Bottom).y();
			b = m_end->connection(Block::Top).y();
		}
		renderTopBottom = true;
	}
	else if( theta > leftAngle )
	{
		x = m_start->connection(Block::Left).x();
		a = m_end->connection(Block::Right).x();
	}

	switch( m_type )
	{
		case Spline:
		{
			qreal cx1 = 0;
			qreal cy1 = 0;
			qreal cx2 = 0;
			qreal cy2 = 0;

			if( renderTopBottom )
			{
				cx1 = x;
				cy1 = ( b - y )/2 + y;
				cx2 = a;
				cy2 = cy1;
			}
			else
			{
				cx1 = ( a - x )/2 + x;
				cy1 = y;
				cx2 = cx1;
				cy2 = b;
			}

			if( x < a )
			{
				myPath.moveTo( x,y );
				myPath.cubicTo( cx1, cy1, cx2, cy2, a, b);
			}
			else
			{
				myPath.moveTo( a,b );
				myPath.cubicTo( cx2, cy2, cx1, cy1, x, y);
			}
			break;
		}
		case Line:
		{
			myPath.moveTo(x,y);
			myPath.lineTo(a,b);
			break;
		}
		case Arc:
		{
			break;
		}
		default:
			break;
	}
	m_gradientLine = QLineF(x,y,a,b);
	myPath.addEllipse( a - 5, b - 5, 10, 10);
	setPath(myPath);
}


Connector::Type Connector::lineType() const
{
	return m_type;
}


void Connector::setLineType( const Type& theValue )
{
	m_type = theValue;
}

void Connector::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget )
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	QPen currentPen = pen();

 	QLinearGradient linearGrad( m_gradientLine.p1(), m_gradientLine.p2() );
	linearGrad.setColorAt(0, m_start->shapeColor().dark( 125 ) );
	linearGrad.setColorAt(1, m_end->shapeColor().dark( 125 ) );
	currentPen.setBrush( linearGrad );

	painter->save();
	painter->strokePath(path(), currentPen );
	painter->restore();
}
