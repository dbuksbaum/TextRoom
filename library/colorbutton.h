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
#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QPushButton>
#include <QColor>
#include <QPixmap>
/**
A simple button that allows the user to pick a color.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class ColorButton : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY( QColor color READ color WRITE setColor)
public:
	ColorButton(QWidget* parent);

	~ColorButton();

	void setColor(const QColor& theValue);
	QColor color() const;

signals:
	void colorChanged(const QColor &color);
private slots:
	void buttonPressed();

private:
	QPixmap buildPixmap( const QColor &color );
	QColor m_color;
};

#endif
