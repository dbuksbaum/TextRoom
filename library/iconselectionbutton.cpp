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
#include "iconselectionbutton.h"
#include "emblemselector.h"

IconSelectionButton::IconSelectionButton(QWidget *parent)
		: QPushButton(parent), m_mindmap(0)
{
	connect( this, SIGNAL(released()), this, SLOT(buttonPressed()));
	setCurrentIconName(QString());
}


IconSelectionButton::~IconSelectionButton()
{

}

void IconSelectionButton::buttonPressed( )
{
	EmblemSelector selector(this,m_mindmap);
	selector.setCurrentIcon(m_currentIconName);
	if( selector.exec() == QDialog::Accepted )
	{
		setCurrentIconName( selector.currentIcon() );
	}
}

QIcon IconSelectionButton::currentIcon() const
{
	return m_currentIcon;
}

void IconSelectionButton::setCurrentIcon(const QIcon& theValue)
{
	m_currentIcon = theValue;
	setIcon(m_currentIcon);
	emit iconChanged( m_currentIcon );
}


QString IconSelectionButton::currentIconName() const
{
	if( m_currentIconName == QLatin1String(":/emblems/none.svg"))
		return QString();
	else
		return m_currentIconName;

}


void IconSelectionButton::setCurrentIconName(const QString& theValue)
{
	if( theValue.isEmpty() )
		m_currentIconName = QLatin1String(":/emblems/none.svg");
	else
		m_currentIconName = theValue;
	emit iconNameChanged( m_currentIconName );
	setCurrentIcon( QIcon( m_currentIconName ) );
}

void IconSelectionButton::setMindMap( MindMap *map )
{
	m_mindmap = map;
}
        