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
#include "qtextdocumentparserobserver.h"
#include <QTextCursor>
#include <QApplication>
#include <QTextList>
#include <QTextFrame>
#include <QTextFrameFormat>

QTextDocumentParserObserver::QTextDocumentParserObserver(QTextCursor *cursor): ParserObserverBase(), m_cursor(cursor), m_currentList(0), m_topFrame(0), m_first(false)
{
}


QTextDocumentParserObserver::~QTextDocumentParserObserver()
{
}


void QTextDocumentParserObserver::addText( const QString& text )
{
	m_cursor->insertText(text);
}

void QTextDocumentParserObserver::drawAnchor( const QString& url, const QString& title )
{
	QTextBlockFormat blockFormat = m_cursor->blockFormat();
	QTextCharFormat charFormat = m_cursor->charFormat();
	QTextCharFormat urlFormat = charFormat;
	urlFormat.setAnchor(true);
	urlFormat.setAnchorHref( url );
	urlFormat.setUnderlineColor( Qt::blue );
	urlFormat.setUnderlineStyle( QTextCharFormat::SingleUnderline );
	m_cursor->insertText(title, urlFormat);
	m_cursor->setBlockFormat(blockFormat);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::drawHrule()
{
	QTextBlockFormat blockFormat = m_cursor->blockFormat();
	QTextCharFormat charFormat = m_cursor->charFormat();
	m_cursor->insertHtml("<hr>");
	m_cursor->insertBlock(blockFormat,charFormat);
}

void QTextDocumentParserObserver::drawImage( const QString& url, const QString& title )
{

}

void QTextDocumentParserObserver::drawLineBreak()
{
	QTextBlockFormat blockFormat = m_cursor->blockFormat();
	QTextCharFormat charFormat = m_cursor->charFormat();
	m_cursor->insertBlock(blockFormat,charFormat);
}

void QTextDocumentParserObserver::endBold()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontWeight(QFont::Normal);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::endCrossout()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontStrikeOut(false);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::endItalics()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontItalic(false);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::startListItem()
{
	if( m_first )
	{
		m_first = false;
	}
	else
	{
		QTextBlockFormat blockFormat = m_cursor->blockFormat();
		QTextCharFormat charFormat = m_cursor->charFormat();
		m_cursor->insertBlock(blockFormat,charFormat);
	}
}

void QTextDocumentParserObserver::endListItem()
{
}

void QTextDocumentParserObserver::startOrderedList()
{
	QTextListFormat fmt;
	fmt.setIndent(0);
	if( !m_listStack.isEmpty() )
		fmt = m_listStack.top()->format();
	fmt.setIndent(fmt.indent() + 1);
	fmt.setStyle( QTextListFormat::ListDecimal );
	m_currentList = m_cursor->insertList( fmt );
	m_listStack.push( m_currentList );
	m_first = true;
}

void QTextDocumentParserObserver::startUnOrderedList()
{
	QTextListFormat fmt;
	fmt.setIndent(0);
	if( !m_listStack.isEmpty() )
		fmt = m_listStack.top()->format();
	fmt.setIndent(fmt.indent() + 1);
	fmt.setStyle( QTextListFormat::ListDisc );
	m_currentList = m_cursor->insertList( fmt );
	m_listStack.push( m_currentList );
	m_first = true;
}

void QTextDocumentParserObserver::endOrderedList()
{
	m_listStack.pop();
}

void QTextDocumentParserObserver::endUnOrderedList()
{
	m_listStack.pop();
}

void QTextDocumentParserObserver::endPage()
{
	m_cursor->endEditBlock();
}

void QTextDocumentParserObserver::endParagraph()
{
}

void QTextDocumentParserObserver::endPreformatted()
{
	m_cursor->setPosition(m_topFrame->lastPosition());
}

void QTextDocumentParserObserver::endTable()
{

}

void QTextDocumentParserObserver::endTableCell()
{

}

void QTextDocumentParserObserver::endTableHeaderCell()
{

}

void QTextDocumentParserObserver::endTableRow()
{

}

void QTextDocumentParserObserver::endTypewriter()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontFamily( QApplication::font().family() );
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::endUnderline()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontUnderline(false);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::startBold()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontWeight(QFont::Bold);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::startCrossout()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontStrikeOut(true);
	m_cursor->setCharFormat(charFormat);
}


void QTextDocumentParserObserver::startItalics()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontItalic(true);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::startPage( const QString &title )
{
	m_cursor->beginEditBlock();
}

void QTextDocumentParserObserver::startParagraph()
{
	m_cursor->insertBlock(QTextBlockFormat(), QTextCharFormat() );
}

void QTextDocumentParserObserver::startPreformatted()
{
	m_topFrame = m_cursor->currentFrame();
	QTextCharFormat charFormat = m_cursor->charFormat();
	QTextFrameFormat frameStyle = m_cursor->currentFrame()->frameFormat();
	charFormat.setFontFamily("courier new");
	charFormat.setFontFixedPitch(true);
	frameStyle.setBorderStyle( QTextFrameFormat::BorderStyle_Dotted );
	frameStyle.setBorder(1);
	frameStyle.setPadding(3);

	m_cursor->insertFrame( frameStyle );
	m_cursor->setCharFormat( charFormat );
}

void QTextDocumentParserObserver::startTable()
{

}

void QTextDocumentParserObserver::startTableCell()
{

}

void QTextDocumentParserObserver::startTableHeaderCell()
{

}

void QTextDocumentParserObserver::startTableRow()
{

}

void QTextDocumentParserObserver::startTypewriter()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontFamily("courier new");
	charFormat.setFontFixedPitch(true);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::startUnderline()
{
	QTextCharFormat charFormat = m_cursor->charFormat();
	charFormat.setFontUnderline(true);
	m_cursor->setCharFormat(charFormat);
}

void QTextDocumentParserObserver::drawHeading( int level, const QString & text )
{
	QTextBlockFormat blockFormat = m_cursor->blockFormat();
	QTextCharFormat charFormat = m_cursor->charFormat();

	QTextCharFormat headerFormat = charFormat;

	headerFormat.setProperty(QTextFormat::FontSizeAdjustment, 5 - level );
 	headerFormat.setFontWeight( QFont::Bold );
	m_cursor->insertBlock(blockFormat,headerFormat);
	m_cursor->insertText(text);
	m_cursor->setCharFormat(charFormat);
	m_cursor->setBlockFormat(blockFormat);
}
