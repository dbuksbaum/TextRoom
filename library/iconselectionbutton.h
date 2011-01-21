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
#ifndef ICONSELECTIONBUTTON_H
#define ICONSELECTIONBUTTON_H

#include <QPushButton>
#include <QIcon>

class MindMap;
/**
A icon selection button.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class IconSelectionButton : public QPushButton
{
	Q_OBJECT
	Q_PROPERTY( QIcon currentIcon READ currentIcon WRITE setCurrentIcon )
	Q_PROPERTY( QString currentIconName READ currentIconName WRITE setCurrentIconName )
public:
	IconSelectionButton(QWidget *parent = 0);
	~IconSelectionButton();

	void setCurrentIcon(const QIcon& theValue);
	QIcon currentIcon() const;

	void setCurrentIconName(const QString& theValue);
	QString currentIconName() const;

        void setMindMap( MindMap *map );
        
signals:
	void iconChanged(const QIcon &icon);
	void iconNameChanged( const QString &name);

private slots:
	void buttonPressed();

private:
	QIcon m_currentIcon;
	QString m_currentIconName;
        MindMap *m_mindmap;
};

#endif
