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
#ifndef WIKILEXER_H
#define WIKILEXER_H

#include <QString>

class QIODevice;

/**
A scanner/lexer for wiki markup.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class WikiLexer
{
	public:
		enum TOKEN { TOKEN_EOF, TOKEN_PARA_BREAK, TOKEN_TEXT, TOKEN_NEWLINE,
		             TOKEN_ULIST_1, TOKEN_ULIST_2, TOKEN_ULIST_3, TOKEN_ULIST_4, TOKEN_ULIST_5,
		             TOKEN_OLIST_1, TOKEN_OLIST_2, TOKEN_OLIST_3, TOKEN_OLIST_4, TOKEN_OLIST_5,
		             TOKEN_HEADING_1, TOKEN_HEADING_2, TOKEN_HEADING_3, TOKEN_HEADING_4, TOKEN_HEADING_5,
		             TOKEN_START_PRE, TOKEN_END_PRE,
		             TOKEN_TABLE_HEAD, TOKEN_TABLE_CELL,
		             TOKEN_START_LINK, TOKEN_END_LINK,
		             TOKEN_START_IMAGE, TOKEN_END_IMAGE,
		             TOKEN_START_PLACEHOLDER, TOKEN_END_PLACEHOLDER,
		             TOKEN_UNDERLINE,
		             TOKEN_ITALICS,
		             TOKEN_HRULE,
		             TOKEN_CROSSOUT,
		             TOKEN_SUPERSCRIPT,
			     TOKEN_SUBSCRIPT,
		             TOKEN_LINEBREAK,
		             TOKEN_WHITESPACE,
			     TOKEN_URL_START
	           };

		WikiLexer();
		~WikiLexer();


		TOKEN next_token( );
		bool match ( TOKEN tok );

		void parse ( const QString &buffer );

		void setInput ( const QString& theValue );
		QString input() const;

		bool getChar ( QChar *ch );
		void ungetChar ( const QChar &ch );
		bool matchString ( const QString &string );

		TOKEN currentToken() const;

		QChar currentChar() const;

		QString currentTokenAsText( );

		TOKEN lastToken() const;
		QChar lastChar() const;

	private:
		TOKEN m_currentToken;
		TOKEN m_lastToken;

		QString m_tokenText;

		QString m_input;
		QChar m_currentChar;
		QChar m_lastChar;
		int m_index;
};

#endif
