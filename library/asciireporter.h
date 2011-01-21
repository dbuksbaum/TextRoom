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
#ifndef ASCIIREPORTER_H
#define ASCIIREPORTER_H

#include <QString>

class Block;
class MindMap;
/**
Generate a ASCII text report from a mindmap.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class ASCIIReporter
{
public:
	ASCIIReporter();

	~ASCIIReporter();

	QString generateReport( Block *root );
	QString generateReport( MindMap *map);

	void indent( int amount, QString *doc );
	void blockTextBodyReporter( Block *block, QString *doc );
	void blockTextTitleReporter( Block *block, QString *doc );
	void blockTextReporter( Block *block, QString *doc );
	void mindmapHeaderReporter( MindMap *mindmap, QString *doc);
	void writeTextBlock( int depth, const QString &text, QString  *doc );
	QString documentText() const;

	void setTabSize(int theValue);
	int tabSize() const;

	void setPageCols(int theValue);
	int pageCols() const;

private:
	QString m_documentText;
	int m_tabSize;
	int m_pageCols;
	QString m_tabular;
};

#endif
