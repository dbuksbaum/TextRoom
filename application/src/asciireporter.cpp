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
#include "asciireporter.h"
#include "mindmap.h"
#include "block.h"

#ifdef Q_OS_WIN32
const QString endLine = "\r\n";
#else
const QString endLine = "\n";
#endif

ASCIIReporter::ASCIIReporter()
{
	m_pageCols = 80;
	m_tabSize = 5;
	setTabSize( m_tabSize );
}

ASCIIReporter::~ASCIIReporter()
{

}

void ASCIIReporter::indent( int amount, QString * doc )
{
	for( int idx= 0; idx < amount; ++idx)
		doc->append( m_tabular );
}

void ASCIIReporter::writeTextBlock( int depth, const QString & textBlock, QString * doc )
{
	int amount = m_pageCols - ( depth * m_tabSize );
	QString text = textBlock;
	int index = 0;

	while( !text.isEmpty() && index != -1)
	{
		indent( depth, doc);
		if( text.size() > amount )
		{
			int spc = text.lastIndexOf(' ',  amount );
			int end = text.lastIndexOf( '\n', amount );
			if( end != -1 && end < spc )
				index = end;
			else
				index = spc;
			doc->append( text.left( index ) );
			doc->append( endLine );
			text.remove(0, index + 1);
		}
		else
		{
			doc->append( text );
			doc->append( endLine );
			text.clear();
		}
	}
}

void ASCIIReporter::blockTextBodyReporter( Block * block, QString * doc )
{

	int depth = block->path().count() + 1;
	QString text = block->text().replace('\t', m_tabular );
	writeTextBlock( depth, text, doc );
}

void ASCIIReporter::blockTextTitleReporter( Block * block, QString * doc )
{
	indent( block->path().count(), doc );
	doc->append( block->pathString() );
	doc->append( ' ' );
	doc->append( block->title().toUpper() );
	doc->append( endLine );
}


void ASCIIReporter::blockTextReporter( Block * block, QString * doc )
{
	blockTextTitleReporter( block, doc );
	blockTextBodyReporter( block, doc );
	doc->append( endLine );

	foreach( Block *block, block->children() )
		blockTextReporter( block, doc );
}

QString ASCIIReporter::documentText() const
{
	return m_documentText;
}

QString ASCIIReporter::generateReport( Block * block )
{
	m_documentText.clear();

	blockTextReporter( block, &m_documentText );

	return m_documentText;
}


int ASCIIReporter::tabSize() const
{
	return m_tabSize;
}


void ASCIIReporter::setTabSize(int theValue)
{
	m_tabular.clear();
	m_tabSize = theValue;
	for( int idx = 0; idx < m_tabSize; ++idx )
		m_tabular += ' ';
}


int ASCIIReporter::pageCols() const
{
	return m_pageCols;
}

void ASCIIReporter::setPageCols(int theValue)
{
	m_pageCols = theValue;
}

void ASCIIReporter::mindmapHeaderReporter( MindMap * mindmap, QString * doc )
{
	doc->append( mindmap->getProperty("document.title", "Untitled").toString() );
	doc->append( endLine );
	QString author = mindmap->getProperty("document.author").toString();
	if( !author.isEmpty() )
	{
		indent( 2, doc );
		doc->append( "by ");
		doc->append( author );
		doc->append(endLine);
	}
	QString abstract = mindmap->getProperty("document.description").toString();
	if( !abstract.isEmpty())
	{
		doc->append("Abstract:");
		doc->append(endLine);
		writeTextBlock( 2, abstract, doc );
	}
}

QString ASCIIReporter::generateReport( MindMap * map )
{
	m_documentText.clear();

	mindmapHeaderReporter( map, &m_documentText );
	for( int idx = 0; idx < m_pageCols; ++idx )
		m_documentText.append('=');
	m_documentText.append(endLine);
	blockTextReporter( map->root(), &m_documentText );

	return m_documentText;
}

