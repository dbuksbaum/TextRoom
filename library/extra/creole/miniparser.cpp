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

MiniParser::MiniParser()
: StateMachineBase(), m_newPara(false), m_inBold(false), m_inItalics(false), m_inUnderline(false), m_inCrossout(false)
{

}


MiniParser::~MiniParser()
{
}


void MiniParser::exec ( Context* ctx )
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
			turnOffTextFormats(ctx);
			ctx->nextState = 0;

			break;
		}
		case WikiLexer::TOKEN_PARA_BREAK:  // end paragraph
		{
			turnOffTextFormats(ctx);
			break;
		}
		case WikiLexer::TOKEN_NEWLINE:
		{
			ctx->observer->addText ( "\n" );
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
			turnOffTextFormats(ctx);
			QString buffer;

			while( ctx->lexer->next_token() != WikiLexer::TOKEN_EOF &&
				ctx->lexer->currentToken() != WikiLexer::TOKEN_END_PRE )
				buffer += ctx->lexer->currentTokenAsText();

			if( buffer.contains("\n") )
				ctx->observer->startPreformatted();
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
			turnOffTextFormats(ctx);
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
			{
				ctx->observer->addText ( "//" );
				break;
			}
			if( !m_inItalics )
			{
				ctx->observer->startItalics();
				m_inItalics = true;
			}
			else if( m_inItalics )
			{
				ctx->observer->endItalics();
				m_inItalics = false;
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
		case WikiLexer::TOKEN_ULIST_2:
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
		default:
			break;
	};
}

void MiniParser::turnOffTextFormats( Context* ctx )
{
	if( m_inBold )
	{
		ctx->observer->endBold();
		m_inBold = false;
	}
	if( m_inItalics )
	{
		ctx->observer->endItalics();
		m_inItalics = false;
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
