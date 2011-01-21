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
#include "floparserobserver.h"
#include "block.h"
#include "mindmap.h"

FloParserObserver::FloParserObserver(MindMap *mindMap, const QString& baseAnchorUrl): ParserObserverBase(baseAnchorUrl), m_map(mindMap), m_currentBlock(0)
{
}


FloParserObserver::~FloParserObserver()
{
}


void FloParserObserver::addText(const QString& text)
{
	if( m_currentBlock )
	{
		m_currentBlock->setText( m_currentBlock->text() + "\n\n" + text );
	}
}

void FloParserObserver::drawAnchor(const QString& url, const QString& title)
{
}

void FloParserObserver::drawHeading(int level, const QString& text)
{
}

void FloParserObserver::drawHrule()
{
}

void FloParserObserver::drawImage(const QString& url, const QString& title)
{
}

void FloParserObserver::drawLineBreak()
{
}

void FloParserObserver::endBold()
{
}

void FloParserObserver::endCrossout()
{
}

void FloParserObserver::endItalics()
{
}

void FloParserObserver::endListItem()
{
}

void FloParserObserver::endOrderedList()
{
}

void FloParserObserver::endPage()
{
}

void FloParserObserver::endParagraph()
{
}

void FloParserObserver::endPreformatted()
{
}

void FloParserObserver::endTable()
{
}

void FloParserObserver::endTableCell()
{
}

void FloParserObserver::endTableHeaderCell()
{
}

void FloParserObserver::endTableRow()
{
}

void FloParserObserver::endTypewriter()
{
}

void FloParserObserver::endUnderline()
{
}

void FloParserObserver::endUnOrderedList()
{
}

void FloParserObserver::startBold()
{
}

void FloParserObserver::startCrossout()
{
}

void FloParserObserver::startItalics()
{
}

void FloParserObserver::startListItem()
{
}

void FloParserObserver::startOrderedList()
{
}

void FloParserObserver::startPage(const QString& title)
{
	Block *block = new Block(0, m_map->scene() );
	block->setTitle( title );
	block->setMindmap( m_map );
	m_currentBlock = block;
}

void FloParserObserver::startParagraph()
{

}

void FloParserObserver::startPreformatted()
{
}

void FloParserObserver::startTable()
{
}

void FloParserObserver::startTableCell()
{
}

void FloParserObserver::startTableHeaderCell()
{
}

void FloParserObserver::startTableRow()
{
}

void FloParserObserver::startTypewriter()
{
}

void FloParserObserver::startUnderline()
{
}

void FloParserObserver::startUnOrderedList()
{
}

