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
#include "colorbutton.h"

#include <QColorDialog>

ColorButton::ColorButton(QWidget* parent)
: QPushButton(parent), m_color(Qt::green)
{
	connect( this, SIGNAL(released()), this, SLOT(buttonPressed()));
	setIcon(buildPixmap(m_color));
}

ColorButton::~ColorButton()
{

}

void ColorButton::setColor(const QColor& theValue)
{
	m_color = theValue;
	setIcon(buildPixmap(m_color));
}


QColor ColorButton::color() const
{
	return m_color;
}

void ColorButton::buttonPressed( )
{
	QColor newColor = QColorDialog::getColor(m_color, this);
	if( newColor != m_color )
	{
		m_color = newColor;
		setIcon(buildPixmap(m_color));
		emit colorChanged(m_color);
	}
}

QPixmap ColorButton::buildPixmap( const QColor & color )
{
	QPixmap pix(16,16);
	pix.fill(color);
	return pix;
}
