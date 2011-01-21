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
#include "xhtmlobserver.h"
#include <QXmlStreamWriter>

XHTMLObserver::XHTMLObserver ( const QString &baseAnchorUrl,  QXmlStreamWriter *outstream ) : ParserObserverBase(baseAnchorUrl), m_out(outstream)
{
	m_elementClasses << "wiki";
}


XHTMLObserver::~XHTMLObserver()
{
}


void XHTMLObserver::addText ( const QString& text )
{
	m_out->writeCharacters( text );
}

void XHTMLObserver::endPage()
{
	m_out->writeEndElement();
}

void XHTMLObserver::endParagraph()
{
	m_out->writeEndElement();
}

void XHTMLObserver::startPage( const QString &title )
{
	QString id = title;
	id.remove(' ');
	m_out->writeStartElement("div");
	m_out->writeAttribute("id", id);
	writeElementClasses( );

}

void XHTMLObserver::startParagraph()
{
	m_out->writeStartElement("p");
	writeElementClasses( );
}

void XHTMLObserver::startHeading(int level)
{
	m_out->writeStartElement(QString("<h%1>").arg(level));
	writeElementClasses( );
}

void XHTMLObserver::endHeading(int level)
{
	m_out->writeEndElement();
}

void XHTMLObserver::startPreformatted()
{
	m_out->writeStartElement("pre");
	writeElementClasses( );
}

void XHTMLObserver::endPreformatted()
{
	m_out->writeEndElement();
}

void XHTMLObserver::drawHrule()
{
	m_out->writeEmptyElement("hr");
	writeElementClasses( );
}

void XHTMLObserver::startBold()
{
	m_out->writeStartElement("strong");
	writeElementClasses( );
}

void XHTMLObserver::endBold()
{
	m_out->writeEndElement();
}

void XHTMLObserver::startItalics()
{
	m_out->writeStartElement("em");
	writeElementClasses( );
}

void XHTMLObserver::endItalics()
{
	m_out->writeEndElement();
}

void XHTMLObserver::startUnderline()
{
	m_out->writeStartElement("u");
	writeElementClasses( );
}

void XHTMLObserver::endUnderline()
{
	m_out->writeEndElement();
}

void XHTMLObserver::drawAnchor(const QString & url, const QString & title)
{
	m_out->writeStartElement("a");
	if( url.startsWith("http://") )
	{
		m_out->writeAttribute("href", url );
	}
	else
	{
		m_out->writeAttribute("href", m_baseAnchorUrl + url );
	}
	writeElementClasses( );
	m_out->writeCharacters(title);
	m_out->writeEndElement();

}

void XHTMLObserver::drawImage(const QString & url, const QString & title)
{
	m_out->writeEmptyElement("img");
	if( url.startsWith("http://") )
	{
		m_out->writeAttribute("src", url );
	}
	else
	{
		m_out->writeAttribute("src", m_baseAnchorUrl + url );
	}
	m_out->writeAttribute("alt", title);
	writeElementClasses( );
	
}

void XHTMLObserver::startCrossout( )
{
	m_out->writeStartElement("strike");
	writeElementClasses( );
	
}

void XHTMLObserver::endCrossout( )
{
	m_out->writeEndElement();
}

void XHTMLObserver::startTypewriter( )
{
	m_out->writeStartElement("tt");
	writeElementClasses( );
}

void XHTMLObserver::endTypewriter( )
{
	m_out->writeEndElement();
}

void XHTMLObserver::drawLineBreak( )
{
	m_out->writeEmptyElement("br");
	writeElementClasses( );
}

void XHTMLObserver::startOrderedList( )
{
	m_out->writeStartElement("ol");
	writeElementClasses( );
}

void XHTMLObserver::endOrderedList( )
{
	m_out->writeEndElement();
}

void XHTMLObserver::startUnOrderedList( )
{
	m_out->writeStartElement("ul");
	writeElementClasses( );
}

void XHTMLObserver::endUnOrderedList( )
{
	m_out->writeEndElement();

}

void XHTMLObserver::startListItem( )
{
	m_out->writeStartElement("li");
	writeElementClasses( );
}

void XHTMLObserver::endListItem( )
{
	m_out->writeEndElement();
}

void XHTMLObserver::startTable()
{
	m_out->writeStartElement("table");
	writeElementClasses( );
}

void XHTMLObserver::endTable()
{
	m_out->writeEndElement();

}

void XHTMLObserver::startTableRow()
{
	m_out->writeStartElement("tr");
	writeElementClasses( );
}

void XHTMLObserver::endTableRow()
{
	m_out->writeEndElement();

}

void XHTMLObserver::startTableHeaderCell()
{
	m_out->writeStartElement("th");
	writeElementClasses( );
}

void XHTMLObserver::endTableHeaderCell()
{
	m_out->writeEndElement();

}

void XHTMLObserver::startTableCell()
{
	m_out->writeStartElement("td");
	writeElementClasses( );
}

void XHTMLObserver::endTableCell()
{
	m_out->writeEndElement();

}

void XHTMLObserver::drawHeading( int level, const QString & text )
{
	// <h1 id=FooBarBaz>Foo Bar Baz</h1>
	QString id = text;
	id.prepend("id_");
	id.replace(' ', '_');
	id.replace('(', '_');
	id.replace(')', '_');
	id.replace('.', '_');
	id.replace(',', '_');
	
	while( m_headers.contains( id ) )
		id += '_';
	
	m_out->writeStartElement( QString("h%1").arg(level) );
	m_out->writeAttribute("id", id);
	writeElementClasses( );
	m_out->writeCharacters(text);
	m_out->writeEndElement();
	m_headers << id;
}


QStringList XHTMLObserver::elementClasses() const
{
	return m_elementClasses;
}


void XHTMLObserver::setElementClasses ( const QStringList& theValue )
{
	m_elementClasses = theValue;
}

void XHTMLObserver::writeElementClasses( )
{
        if( !m_elementClasses.isEmpty() )
                m_out->writeAttribute("class", m_elementClasses.join(" "));
}
