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
#ifndef XHTMLOBSERVER_H
#define XHTMLOBSERVER_H

#include <parserobserverbase.h>
#include <QStringList>
#include <QSet>

class QXmlStreamWriter;
/**
Observer that will output XHTML to a text stream.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class XHTMLObserver : public ParserObserverBase
{
	public:
		XHTMLObserver ( const QString &baseAnchorUrl, QXmlStreamWriter *outstream );

		~XHTMLObserver();

		void addText ( const QString& text );
		void endPage();
		void endParagraph();

		void startPage( const QString &title );
		void startParagraph();

		void startHeading( int level );
		void endHeading( int level );
		virtual void drawHeading( int level, const QString &text );


		virtual void startPreformatted( );
		virtual void endPreformatted();
		virtual void startTypewriter();
		virtual void endTypewriter();

		virtual void startBold();
		virtual void endBold();
		virtual void startItalics();
		virtual void endItalics();
		virtual void startUnderline();
		virtual void endUnderline();
		virtual void startCrossout();
		virtual void endCrossout();

		virtual void drawHrule();
		virtual void drawLineBreak();
		virtual void drawAnchor( const QString &url, const QString &title );
		virtual void drawImage( const QString &url, const QString &title );


		virtual void startOrderedList();
		virtual void endOrderedList();
		virtual void startUnOrderedList();
		virtual void endUnOrderedList();
		virtual void startListItem();
		virtual void endListItem();

		virtual void startTable();
		virtual void endTable();
		virtual void startTableRow();
		virtual void endTableRow();
		virtual void startTableHeaderCell();
		virtual void endTableHeaderCell();
		virtual void startTableCell();
		virtual void endTableCell();

		void setElementClasses ( const QStringList& theValue );
		QStringList elementClasses() const;
	
private:
	void writeElementClasses();
	QXmlStreamWriter *m_out;
	QStringList m_elementClasses;
	QSet<QString> m_headers;
};

#endif
