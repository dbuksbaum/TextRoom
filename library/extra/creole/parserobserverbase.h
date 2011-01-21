/***************************************************************************
 *   Copyright (C) 2007 by Ian Reinhart Geiser                             *
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
#ifndef PARSEROBSERVERBASE_H
#define PARSEROBSERVERBASE_H

#include <QString>

/**
Base class for parser observers.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class ParserObserverBase
{
	public:
		ParserObserverBase( const QString &baseAnchorUrl = QString() );

		virtual ~ParserObserverBase();

		virtual void addText( const QString& text ) = 0;
		virtual void drawAnchor( const QString& url, const QString& title ) = 0;
		virtual void drawHrule() = 0;
		virtual void drawImage( const QString& url, const QString& title ) = 0;
		virtual void drawLineBreak() = 0;
		virtual void endBold() = 0;
		virtual void endCrossout() = 0;
		virtual void endItalics() = 0;
		virtual void endListItem() = 0;
		virtual void endOrderedList() = 0;
		virtual void endPage() = 0;
		virtual void endParagraph() = 0;
		virtual void endPreformatted() = 0;
		virtual void endTable() = 0;
		virtual void endTableCell() = 0;
		virtual void endTableHeaderCell() = 0;
		virtual void endTableRow() = 0;
		virtual void endTypewriter() = 0;
		virtual void endUnderline() = 0;
		virtual void endUnOrderedList() = 0;
		virtual void startBold() = 0;
		virtual void startCrossout() = 0;
		virtual void startItalics() = 0;
		virtual void startListItem() = 0;
		virtual void startOrderedList() = 0;
		virtual void startPage( const QString &title ) = 0;
		virtual void startParagraph() = 0;
		virtual void startPreformatted() = 0;
		virtual void startTable() = 0;
		virtual void startTableCell() = 0;
		virtual void startTableHeaderCell() = 0;
		virtual void startTableRow() = 0;
		virtual void startTypewriter() = 0;
		virtual void startUnderline() = 0;
		virtual void startUnOrderedList() = 0;
		virtual void drawHeading( int level, const QString &text ) = 0;
protected:
	const QString m_baseAnchorUrl;
};

#endif
