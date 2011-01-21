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
#ifndef QTEXTDOCUMENTPARSER_H
#define QTEXTDOCUMENTPARSER_H

#include <parserobserverbase.h>
#include <QStack>

class QTextCursor;
class QTextList;
class QTextFrame;

/**
	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class QTextDocumentParserObserver : public ParserObserverBase
{
	public:
		QTextDocumentParserObserver( QTextCursor *cursor );

		~QTextDocumentParserObserver();

		virtual void addText( const QString& text );
		virtual void drawAnchor( const QString& url, const QString& title );
		virtual void drawHrule();
		virtual void drawImage( const QString& url, const QString& title );
		virtual void drawLineBreak();
		virtual void endBold();
		virtual void endCrossout();
		virtual void endItalics();
		virtual void endListItem();
		virtual void endOrderedList();
		virtual void endPage();
		virtual void endParagraph();
		virtual void endPreformatted();
		virtual void endTable();
		virtual void endTableCell();
		virtual void endTableHeaderCell();
		virtual void endTableRow();
		virtual void endTypewriter();
		virtual void endUnderline();
		virtual void endUnOrderedList();
		virtual void startBold();
		virtual void startCrossout();
		virtual void startItalics();
		virtual void startListItem();
		virtual void startOrderedList();
		virtual void startPage( const QString &title );
		virtual void startParagraph();
		virtual void startPreformatted();
		virtual void startTable();
		virtual void startTableCell();
		virtual void startTableHeaderCell();
		virtual void startTableRow();
		virtual void startTypewriter();
		virtual void startUnderline();
		virtual void startUnOrderedList();
		virtual void drawHeading( int level, const QString &text );
private:
	QTextCursor *m_cursor;
	QStack<QTextList*> m_listStack;
	QTextList *m_currentList;
	QTextFrame *m_topFrame;
	bool m_first;
};

#endif
