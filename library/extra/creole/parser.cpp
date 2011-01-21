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
#include "parser.h"
#include "wikilexer.h"
#include "parserobserverbase.h"
#include "xhtmlobserver.h"
#include "miniparser.h"

#include <QList>
#include <QStringList>
#include <QTextStream>
#include <QStack>

Parser::Parser()
: StateMachineBase(), m_newPara ( true ), m_inBold(false), m_inItallics(false), m_inUnderline(false), m_inCrossout(false), m_inTable(false), m_inCell(false),m_inTableHeader(false)
{

}


Parser::~Parser()
{
}


int currentListLevel( WikiLexer::TOKEN tok )
{
	if( tok == WikiLexer::TOKEN_OLIST_1 ) return 1;
	if( tok == WikiLexer::TOKEN_OLIST_2 ) return 2;
	if( tok == WikiLexer::TOKEN_OLIST_3 ) return 3;
	if( tok == WikiLexer::TOKEN_OLIST_4 ) return 4;
	if( tok == WikiLexer::TOKEN_OLIST_5 ) return 5;
	if( tok == WikiLexer::TOKEN_ULIST_1 ) return 1;
	if( tok == WikiLexer::TOKEN_ULIST_2 ) return 2;
	if( tok == WikiLexer::TOKEN_ULIST_3 ) return 3;
	if( tok == WikiLexer::TOKEN_ULIST_4 ) return 4;
	if( tok == WikiLexer::TOKEN_ULIST_5 ) return 5;

	return 0;
}


bool isOrderedListItem( WikiLexer::TOKEN tok )
{
	if( tok == WikiLexer::TOKEN_OLIST_1 ) return true;
	if( tok == WikiLexer::TOKEN_OLIST_2 ) return true;
	if( tok == WikiLexer::TOKEN_OLIST_3 ) return true;
	if( tok == WikiLexer::TOKEN_OLIST_4 ) return true;
	if( tok == WikiLexer::TOKEN_OLIST_5 ) return true;

	return false;
}
bool isUnOrderedListItem( WikiLexer::TOKEN tok )
{
	if( tok == WikiLexer::TOKEN_ULIST_1 ) return true;
	if( tok == WikiLexer::TOKEN_ULIST_2 ) return true;
	if( tok == WikiLexer::TOKEN_ULIST_3 ) return true;
	if( tok == WikiLexer::TOKEN_ULIST_4 ) return true;
	if( tok == WikiLexer::TOKEN_ULIST_5 ) return true;

	return false;
}

bool isHeading( WikiLexer::TOKEN token )
{
	if( token == WikiLexer::TOKEN_HEADING_1 ) return true;
	if( token == WikiLexer::TOKEN_HEADING_2 ) return true;
	if( token == WikiLexer::TOKEN_HEADING_3 ) return true;
	if( token == WikiLexer::TOKEN_HEADING_4 ) return true;
	if( token == WikiLexer::TOKEN_HEADING_5 ) return true;
	return false;
}

bool isListItem( WikiLexer::TOKEN tok )
{
	return (isUnOrderedListItem(tok) || isOrderedListItem(tok));
}

void Parser::parseFormatting( ParserObserverBase *observer, const QString &paragraph )
{
	Context ctx;
	ctx.lexer = new WikiLexer;
	ctx.observer = observer;
	ctx.nextState = new MiniParser;

	ctx.lexer->setInput( paragraph );
	while ( ctx.nextState != 0 )
		ctx.nextState->exec ( &ctx );

}

void Parser::exec ( Context* ctx )
{
	switch ( ctx->lexer->next_token() )
	{
		case WikiLexer::TOKEN_TEXT:  // accumulate text
		case WikiLexer::TOKEN_WHITESPACE:
		case WikiLexer::TOKEN_END_PRE:
		{
			if ( m_newPara )
			{
				ctx->observer->startParagraph();
				m_newPara = false;
			}
			if ( ! ( ctx->lexer->currentToken() == WikiLexer::TOKEN_WHITESPACE &&
			         ctx->lexer->lastToken() == WikiLexer::TOKEN_WHITESPACE ) )
				ctx->observer->addText ( ctx->lexer->currentTokenAsText() );
			break;
		}
		case WikiLexer::TOKEN_EOF:   // end paragraph and page
		{
			if ( ctx->lexer->lastToken() != WikiLexer::TOKEN_PARA_BREAK )
				ctx->observer->endParagraph();
			finaliseList(ctx);
			ctx->nextState = 0;

			break;
		}
		case WikiLexer::TOKEN_PARA_BREAK:  // end paragraph
		{
			finalisePara(ctx);
			finaliseList(ctx);
			finaliseTable(ctx);

			break;
		}
		case WikiLexer::TOKEN_HEADING_1:
		case WikiLexer::TOKEN_HEADING_2:
		case WikiLexer::TOKEN_HEADING_3:
		case WikiLexer::TOKEN_HEADING_4:
		case WikiLexer::TOKEN_HEADING_5:
		{
			QString heading;
			int currentHeadingLevel = ( ctx->lexer->currentToken() - WikiLexer::TOKEN_HEADING_1 ) + 1;
			finalisePara(ctx);
			finaliseList(ctx);
			finaliseTable(ctx);
			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				   ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK &&
			       ctx->lexer->currentToken() != WikiLexer::TOKEN_NEWLINE &&
			       !isHeading( ctx->lexer->currentToken()) )
				heading += ctx->lexer->currentTokenAsText();

			ctx->observer->drawHeading( currentHeadingLevel, heading );
			m_newPara = true;

			break;
		}
		case WikiLexer::TOKEN_NEWLINE:
		{
// 			ctx->observer->addText ( "\n" );
			break;
		}
		case WikiLexer::TOKEN_START_IMAGE:
		{
			QString link;
			QString title;
			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_END_IMAGE &&
				ctx->lexer->currentChar() != QChar('|') )
				link += ctx->lexer->currentTokenAsText();
			if( ctx->lexer->currentChar() != QChar('|') )
			{
				ctx->observer->drawImage(link,link);
				break;
			}

			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_END_IMAGE )
				title += ctx->lexer->currentTokenAsText();

			ctx->observer->drawImage(link,title);

			break;
		}
		case WikiLexer::TOKEN_START_LINK:
		{
			QString link;
			QString title;
			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_END_LINK &&
				ctx->lexer->currentChar() != QChar('|') )
				link += ctx->lexer->currentTokenAsText();
			if( ctx->lexer->currentChar() != QChar('|') )
			{
				ctx->observer->drawAnchor(link,link);
				break;
			}

			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_END_LINK )
				title += ctx->lexer->currentTokenAsText();

			ctx->observer->drawAnchor(link,title);

			break;
		}
		case WikiLexer::TOKEN_URL_START:
		{
			QString link = ctx->lexer->currentTokenAsText();
			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_WHITESPACE )
				link += ctx->lexer->currentTokenAsText();
			ctx->observer->drawAnchor(link,link);
			break;
		}
		case WikiLexer::TOKEN_START_PRE:
		{
			QString buffer;

			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_END_PRE )
				buffer += ctx->lexer->currentTokenAsText();

			if( buffer.contains("\n") )
			{
				finalisePara(ctx);
				finaliseList(ctx);
				finaliseTable(ctx);
				ctx->observer->startPreformatted();
			}
			else
				ctx->observer->startTypewriter();

			ctx->observer->addText ( buffer );

			if( buffer.contains("\n") )
				ctx->observer->endPreformatted();
			else
				ctx->observer->endTypewriter();

			break;
		}
		case WikiLexer::TOKEN_HRULE:
		{
			finalisePara(ctx);
			finaliseList(ctx);
			finaliseTable(ctx);
			ctx->observer->drawHrule();
			break;
		}

		case WikiLexer::TOKEN_LINEBREAK:
		{
			ctx->observer->drawLineBreak();
			break;
		}
		case WikiLexer::TOKEN_ITALICS:
		{
			if( ctx->lexer->lastChar() == QChar(':') )
			{	ctx->observer->addText ( "//" );
				break;
			}
			if( !m_inItallics )
			{
				ctx->observer->startItalics();
				m_inItallics = true;
			}
			else if( m_inItallics )
			{
				ctx->observer->endItalics();
				m_inItallics = false;
			}
			break;
		}
		case WikiLexer::TOKEN_UNDERLINE:
		{
			if( !m_inUnderline )
			{
				ctx->observer->startUnderline();
				m_inUnderline = true;
			}
			else if( m_inUnderline )
			{
				ctx->observer->endUnderline();
				m_inUnderline = false;
			}
			break;
		}
		case WikiLexer::TOKEN_CROSSOUT:
		{
			if( !m_inCrossout )
			{
				ctx->observer->startCrossout();
				m_inCrossout = true;
			}
			else if( m_inCrossout )
			{
				ctx->observer->endCrossout();
				m_inCrossout = false;
			}
			break;
		}
		case WikiLexer::TOKEN_OLIST_1:
		case WikiLexer::TOKEN_OLIST_2:
		case WikiLexer::TOKEN_OLIST_3:
		case WikiLexer::TOKEN_OLIST_4:
		case WikiLexer::TOKEN_OLIST_5:
		case WikiLexer::TOKEN_ULIST_1:
		case WikiLexer::TOKEN_ULIST_2:
		case WikiLexer::TOKEN_ULIST_3:
		case WikiLexer::TOKEN_ULIST_4:
		case WikiLexer::TOKEN_ULIST_5:
		{

			if( ctx->lexer->lastToken() != WikiLexer::TOKEN_NEWLINE && ctx->lexer->currentToken() == WikiLexer::TOKEN_ULIST_2)
			{
				if( !m_inBold )
				{
					ctx->observer->startBold();
					m_inBold = true;
				}
				else if( m_inBold )
				{
					ctx->observer->endBold();
					m_inBold = false;
				}
				break;
			}
			else
			{
				m_inList = true;
				finalisePara(ctx);

				int listLevel = currentListLevel(ctx->lexer->currentToken());
				bool orderedList = isOrderedListItem( ctx->lexer->currentToken() );

				QString buffer;
				while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
					ctx->lexer->currentToken() != WikiLexer::TOKEN_NEWLINE &&
					ctx->lexer->currentToken() != WikiLexer::TOKEN_PARA_BREAK )
					buffer += ctx->lexer->currentTokenAsText();
				items << ListItem(  listLevel, orderedList,  buffer);
				if( ctx->lexer->currentToken() == WikiLexer::TOKEN_EOF ||
					ctx->lexer->currentToken() == WikiLexer::TOKEN_PARA_BREAK )
					finaliseList(ctx);
				m_newPara = true;
			}
			break;
		}
		case WikiLexer::TOKEN_TABLE_HEAD:
		{
			finalisePara(ctx);
			if( !m_inTable )
			{
				m_inTable = true;
				m_inTableHeader = true;
				ctx->observer->startTable();
				ctx->observer->startTableRow();
				ctx->observer->startTableHeaderCell();
			}
			else if( ctx->lexer->lastToken() == WikiLexer::TOKEN_NEWLINE )
			{
				ctx->observer->endTableHeaderCell();
				ctx->observer->endTableRow();
				ctx->observer->startTableRow();
				ctx->observer->startTableHeaderCell();
			}
			else
			{
				ctx->observer->endTableHeaderCell();
				ctx->observer->startTableHeaderCell();
			}
			break;
		}
		
		case WikiLexer::TOKEN_TABLE_CELL:
		{
			finalisePara(ctx);
			if( !m_inTable )
			{
				m_inTable = true;
				m_inCell = true;
				ctx->observer->startTable();
				ctx->observer->startTableRow();
				ctx->observer->startTableCell();
			}
			else if( ctx->lexer->lastToken() == WikiLexer::TOKEN_NEWLINE )
			{
				if( m_inTableHeader )
				{
					ctx->observer->endTableHeaderCell();
					m_inTableHeader = false;
				}
				else
					ctx->observer->endTableCell();
				ctx->observer->endTableRow();
				ctx->observer->startTableRow();
				ctx->observer->startTableCell();
			}
			else
			{
				ctx->observer->endTableCell();
				ctx->observer->startTableCell();
			}
			break;
		}
		default:
			break;
	};
}

void Parser::turnOffTextFormats( Context* ctx )
{
	if( m_inBold )
	{
		ctx->observer->endBold();
		m_inBold = false;
	}
	if( m_inItallics )
	{
		ctx->observer->endItalics();
		m_inItallics = false;
	}
	if( m_inUnderline )
	{
		ctx->observer->endUnderline();
		m_inUnderline = false;
	}
	if( m_inCrossout )
	{
		ctx->observer->endCrossout();
		m_inCrossout = false;
	}
}

void Parser::finaliseList(Context * ctx)
{
	if(items.count() > 0 )
	{
		int listLevel = 0;
		QStack<bool> endStack;
		foreach( ListItem item, items)
		{
			if( item.level > listLevel )
			{
				endStack.push( item.ordered );
				if( item.ordered )
					ctx->observer->startOrderedList();
				else
					ctx->observer->startUnOrderedList();
			}
			else if( item.level < listLevel )
			{
				bool ordered = endStack.pop( );
				if( ordered )
					ctx->observer->endOrderedList();
				else
					ctx->observer->endUnOrderedList();
				ctx->observer->endListItem();
				ctx->observer->endListItem();
			}
			else 
				ctx->observer->endListItem();
			
			ctx->observer->startListItem();
			parseFormatting(ctx->observer, item.text );
			
			listLevel = item.level;
		}
		while( endStack.count() )
		{
			bool ordered = endStack.pop( );
			if( ordered )
				ctx->observer->endOrderedList();
			else
				ctx->observer->endUnOrderedList();
			ctx->observer->endListItem();
		}
		
		items.clear();
	}
}

void Parser::finalisePara(Context * ctx)
{
	turnOffTextFormats(ctx);
	if( !m_newPara )
	{
		ctx->observer->endParagraph();
		m_newPara = true;
	}

}

void Parser::finaliseTable( Context * ctx )
{
	if( m_inTable )
	{
		if( m_inTableHeader )
		{
			ctx->observer->endTableHeaderCell();
			m_inTableHeader = false;
		}
		else
			ctx->observer->endTableCell();
		
		ctx->observer->endTableRow();
		ctx->observer->endTable();
		m_inTable = false;
	}
}

