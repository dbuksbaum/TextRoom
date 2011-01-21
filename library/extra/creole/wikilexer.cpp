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
#include "wikilexer.h"
#include <qdebug.h>

#include <QIODevice>
#include <QStack>

WikiLexer::WikiLexer()
{
}


WikiLexer::~WikiLexer()
{
}

bool WikiLexer::match ( TOKEN tok )
{
	if ( next_token() == tok )
	{
		return true;
	}
	else
	{
		return false;
	}
}

WikiLexer::TOKEN WikiLexer::next_token( )
{
	QChar ch;
	m_lastToken = m_currentToken;
	m_lastChar = m_currentChar;
	m_currentChar = QChar();

	if ( matchString ( "~" ) )
	{
		if ( getChar ( &ch ) )
		{
			m_currentChar = ch;
			m_currentToken = TOKEN_TEXT;
		}
		else
			m_currentToken = TOKEN_EOF;
	}
	else if ( matchString ( "\n\n" ) )
		m_currentToken = TOKEN_PARA_BREAK;
	else if ( matchString ( "*****" ) )
		m_currentToken = TOKEN_ULIST_5;
	else if ( matchString ( "****" ) )
		m_currentToken = TOKEN_ULIST_4;
	else if ( matchString ( "***" ) )
		m_currentToken = TOKEN_ULIST_3;
	else if ( matchString ( "**" ) )
		m_currentToken = TOKEN_ULIST_2;
	else if ( matchString ( "*" ) )
		m_currentToken = TOKEN_ULIST_1;
	else if ( matchString ( "#####" ) )
		m_currentToken = TOKEN_OLIST_5;
	else if ( matchString ( "####" ) )
		m_currentToken = TOKEN_OLIST_4;
	else if ( matchString ( "###" ) )
		m_currentToken = TOKEN_OLIST_3;
	else if ( matchString ( "##" ) )
		m_currentToken = TOKEN_OLIST_2;
	else if ( matchString ( "#" ) )
		m_currentToken = TOKEN_OLIST_1;
	else if ( matchString ( "=====" ) )
		m_currentToken = TOKEN_HEADING_5;
	else if ( matchString ( "====" ) )
		m_currentToken = TOKEN_HEADING_4;
	else if ( matchString ( "===" ) )
		m_currentToken = TOKEN_HEADING_3;
	else if ( matchString ( "==" ) )
		m_currentToken = TOKEN_HEADING_2;
	else if ( matchString ( "=" ) )
		m_currentToken = TOKEN_HEADING_1;
	else if ( matchString ( "{{{" ) )
		m_currentToken = TOKEN_START_PRE;
	else if ( matchString ( "}}}" ) )
		m_currentToken = TOKEN_END_PRE;
	else if ( matchString ( "|=" ) )
		m_currentToken = TOKEN_TABLE_HEAD;
	else if ( matchString ( "|" ) )
		m_currentToken = TOKEN_TABLE_CELL;
	else if ( matchString ( "\n" ) )
		m_currentToken = TOKEN_NEWLINE;
	else if ( matchString ( "[[" ) )
		m_currentToken = TOKEN_START_LINK;
	else if ( matchString ( "]]" ) )
		m_currentToken = TOKEN_END_LINK;
	else if ( matchString ( "{{" ) )
		m_currentToken = TOKEN_START_IMAGE;
	else if ( matchString ( "}}" ) )
		m_currentToken = TOKEN_END_IMAGE;
	else if ( matchString ( "----" ) )
		m_currentToken = TOKEN_HRULE;
	else if ( matchString ( "\\\\" ) )
		m_currentToken = TOKEN_LINEBREAK;
	else if ( matchString ( "--" ) )
		m_currentToken = TOKEN_CROSSOUT;
	else if ( matchString ( "__" ) )
		m_currentToken = TOKEN_UNDERLINE;
	else if ( matchString ( "//" ) )
		m_currentToken = TOKEN_ITALICS;
	else if ( matchString ( ",," ) )
		m_currentToken = TOKEN_SUBSCRIPT;
	else if ( matchString ( "^^" ) )
		m_currentToken = TOKEN_SUPERSCRIPT;
	else if ( matchString ( "<<" ) )
		m_currentToken = TOKEN_START_PLACEHOLDER;
	else if ( matchString ( ">>" ) )
		m_currentToken = TOKEN_END_PLACEHOLDER;
	else if ( matchString ( "http://" ) )
		m_currentToken = TOKEN_URL_START;
	else if ( matchString ( "ftp://" ) )
		m_currentToken = TOKEN_URL_START;
	else if ( matchString ( "https://" ) )
		m_currentToken = TOKEN_URL_START;
	else if ( matchString ( "\t" ) || matchString ( " ") )
	{
		m_currentToken = TOKEN_WHITESPACE;
		m_currentChar = ' ';
	}
	else if ( getChar ( &ch ) )
	{
		m_currentChar = ch;
		m_currentToken = TOKEN_TEXT;
	}
	else
		m_currentToken = TOKEN_EOF;

	return m_currentToken;
}


bool WikiLexer::matchString ( const QString & string )
{
	QStack<QChar> stack;
	bool result = false;
	QChar buff;
	for ( int idx = 0; idx < string.length(); ++idx )
	{
		if ( getChar ( &buff ) )
		{
			result = ( buff == string.at ( idx ) );
			stack.push ( buff );
			m_currentChar = buff;
			if ( !result )
				break;
		}
		else
			break;
	}

	while ( !stack.isEmpty() && !result )
		ungetChar ( stack.pop() );

	if( result )
		m_tokenText = string;
	return result;
}

void WikiLexer::parse ( const QString &buffer )
{
        WikiLexer::TOKEN tok = TOKEN_TEXT;
	QString accumulator;
	setInput ( buffer );

	while ( tok != TOKEN_EOF )
	{
		tok = next_token();
		qDebug ( "Token %d", tok );
	}
}


QString WikiLexer::input() const
{
	return m_input;
}


void WikiLexer::setInput ( const QString& theValue )
{
	m_input = theValue;
	m_index = 0;
}

bool WikiLexer::getChar ( QChar * ch )
{
	if ( m_input.size() <= m_index )
	{
		( *ch ) = QChar();
		return false;
	}

	( *ch ) = m_input.at ( m_index );
	m_index++;
	return true;
}

void WikiLexer::ungetChar ( const QChar & ch )
{
	Q_UNUSED(ch);
	--m_index;
	if ( m_index < 0 )
		m_index = 0;
}


WikiLexer::TOKEN WikiLexer::currentToken() const
{
	return m_currentToken;
}


QChar WikiLexer::currentChar() const
{
	return m_currentChar;
}


WikiLexer::TOKEN WikiLexer::lastToken() const
{
	return m_lastToken;
}


QString WikiLexer::currentTokenAsText()
{
	if( m_currentToken == TOKEN_TEXT || m_currentToken == TOKEN_WHITESPACE )
		return m_currentChar;
	else
		return m_tokenText;
}


QChar WikiLexer::lastChar() const
{
	return m_lastChar;
}
