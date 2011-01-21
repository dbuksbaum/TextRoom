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
#ifndef TITLEEDITOR_H
#define TITLEEDITOR_H

#include <QLineEdit>

class BlockPropertyModel;

/**
A line edit that will directly edit a block's title property with undo/redo support.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class TitleEditor : public QLineEdit
{
	Q_OBJECT
public:
	TitleEditor(QWidget *parent = 0);
	~TitleEditor();

	void setPropertyModel(BlockPropertyModel* theValue);

public slots:
	void setNewBlockTitle();
	void startEditing();

	void setIsEditing(bool theValue);


	bool isEditing() const;


protected:
	virtual void keyPressEvent ( QKeyEvent * event );

private:
	BlockPropertyModel *m_propertyModel;
	bool m_isEditing;
};

#endif
