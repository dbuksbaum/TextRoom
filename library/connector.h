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
#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QGraphicsPathItem>
#include <QPointer>
#include <QLineF>

class Block;

/**
A basic spline connector that will connect two shapes.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class Connector : public QGraphicsPathItem
{
public:
	enum Type { Spline, Line, Arc };
	Connector(QGraphicsItem * parent = 0, QGraphicsScene * scene = 0);

	~Connector();

	void setStart( Block *theValue );
	Block *start();

	void setEnd( Block *theValue );
	Block *end();

	void updatePath();

	void setLineType( const Type& theValue );


	Type lineType() const;

	virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:
	QPointer<Block> m_start;
	QPointer<Block> m_end;
	QLineF m_gradientLine;
	Type m_type;
};

#endif
