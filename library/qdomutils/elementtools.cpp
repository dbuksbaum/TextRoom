/*
    Copyright (C) Ian Reinhart Geiser  <geiseri@sourcextreme.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "elementtools.h"

using namespace SxDomUtils;

QList<QDomElement> SxDomUtils::elementsAtNode( const QDomNode &elem, const Node &node )
{
	QList<QDomElement> elementList;
	QDomNode elmentNode = elem;
	for( ; !elmentNode.isNull(); elmentNode = elmentNode.nextSibling())
	{
		if( elmentNode.nodeName() == node.nodeText )
			elementList.append( elmentNode.toElement() );
	}

	return elementList;
}

QDomNode SxDomUtils::elementAtNode( const QDomNode &elem, const Node &node )
{
	int idx = 0;
	QDomNode elmentNode = elem;
	for( ; !elmentNode.isNull(); elmentNode = elmentNode.nextSibling())
	{
		
		if( elmentNode.nodeName() == node.nodeText )
		{
			if( idx == node.index )
				return elmentNode;
			else
				++idx;
		}
	}
	return elmentNode;
}

QDomNode SxDomUtils::createNode( QDomNode &elem, const Node &node )
{
	if( elem.isNull () )
	{
		QDomDocument dom;
		QDomElement root = dom.appendChild(dom.createElement(node.nodeText)).toElement();
		elem = dom;
		return root;
	}

	QDomNode e = elementAtNode(elem.firstChild(), node);

	if( e.isNull() ) // not there create it
	{
		QDomDocument doc = elem.ownerDocument();
		return elem.appendChild(doc.createElement ( node.nodeText ));
	}
	return e;
}

void SxDomUtils::populateNode( const QDomNode &e, const Node &node, const QString &value )
{
	QDomNode elem = e;
	if( node.property.isEmpty() )
	{
		QDomDocument doc = elem.ownerDocument();
		if( node.type == Node::COMMENT )
		{
			// remove old #comment child
			QDomNode commentNode = elem.namedItem("#comment");
			if( !commentNode.isNull() )
				elem.removeChild(commentNode);
			// make new #comment child
			if( !value.isEmpty() )
				elem.appendChild(doc.createComment(value));
		}
		else if( node.type == Node::CDATA )
		{
			// remove old #cdata-section child
			QDomNode cdataNode = elem.namedItem("#cdata-section");
			if( !cdataNode.isNull() )
				elem.removeChild(cdataNode);
			// make new #cdata-section child
			if( !value.isEmpty() )
				elem.appendChild(doc.createCDATASection(value));
		}
		else/* if( node.type == Node::TEXT )*/
		{
			// remove old #text child
			QDomNode textNode = elem.namedItem("#text");
			if( !textNode.isNull() )
				elem.removeChild(textNode);
			// make new #text child
			if( !value.isEmpty() )
				elem.appendChild(doc.createTextNode(value));
		}
// 		else
// 			qDebug("dorked out %d", node.type);
	}
	else
	{
		QDomElement newElement = elem.toElement();
		
		if( value.isEmpty() )
		{
			newElement.removeAttribute(node.property);
		}
		else
		{
			newElement.setAttribute( node.property, value );
		}
		
	}
}

QString SxDomUtils::nodeValue( const QDomNode &elem, const Node &node )
{
	if( !node.property.isEmpty() )
	{
		QDomNode e = elem;
		const QDomElement domNode = e.toElement();
		return domNode.attribute( node.property, "" );
	}
	else if ( node.type == Node::COMMENT )
	{
		QDomNode domNode = elem.namedItem("#comment");
		return domNode.nodeValue();
	}
	else if ( node.type == Node::CDATA )
	{
		QDomNode domNode = elem.namedItem("#cdata-section");
		return domNode.nodeValue();
	}
	else
	{
		QDomNode domNode = elem.namedItem("#text");
		return domNode.nodeValue();
	}

}

void SxDomUtils::removeNode( const QDomNode &elem, const Node &node )
{
	QDomNode e = elem;
	if( !node.property.isEmpty() )
	{
		QDomElement domNode = e.toElement();
		domNode.removeAttribute( node.property );
	}
	else if ( node.type == Node::COMMENT )
	{
		QDomNode domNode = e.namedItem("#comment");
		e.removeChild( domNode );
	}
	else if ( node.type == Node::CDATA )
	{
		QDomNode domNode = e.namedItem("#cdata-section");
		e.removeChild( domNode );
	}
	else if ( node.type == Node::TEXT )
	{
		QDomNode domNode = e.namedItem("#text");
		e.removeChild( domNode );
	}
	else
	{
		QDomNode parent = e.parentNode();
		parent.removeChild( e );
	}

}
