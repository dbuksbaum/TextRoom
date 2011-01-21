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
#include "documentoptions.h"
#include "ui_documentoptions.h"
#include "mindmap.h"
#include "getusername.h"

DocumentOptions::DocumentOptions(QWidget* parent ): QDialog(parent), m_map(0)
{
	m_ui = new Ui::DocumentOptions;
	m_ui->setupUi(this);
}


DocumentOptions::~DocumentOptions()
{
	delete m_ui;
}

void DocumentOptions::setupGui( MindMap * map )
{
	m_map = map;
	m_ui->documentTitle->setText( map->getProperty("document.title", "Untitled").toString() );
	m_ui->documentAuthor->setText( map->getProperty("document.author", currentUserName() ).toString());
	m_ui->documentDescription->setPlainText( map->getProperty("document.description").toString() );
}

void DocumentOptions::configureMindmap( )
{
	m_map->setProperty("document.title", m_ui->documentTitle->text() );
	m_map->setProperty("document.author", m_ui->documentAuthor->text() );
	m_map->setProperty("document.description", m_ui->documentDescription->toPlainText() );
}


