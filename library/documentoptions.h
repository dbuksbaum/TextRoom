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
#ifndef DOCUMENTOPTIONS_H
#define DOCUMENTOPTIONS_H

#include <QDialog>

namespace Ui
{
	class DocumentOptions;
}
class MindMap;
/**
Configure document options for the current mind map.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class DocumentOptions : public QDialog
{
	Q_OBJECT
public:
	DocumentOptions(QWidget* parent);
	~DocumentOptions();

	void setupGui( MindMap *map );
public slots:
	void configureMindmap( );

private:
	Ui::DocumentOptions *m_ui;
	class MindMap *m_map;
};

#endif
