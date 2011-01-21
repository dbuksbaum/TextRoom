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
#include "dompath.h"
#include "elementtools.h"

#include <QRegExp>
#include <QStringList>
#include <QTextStream>
#include <QMap>

// static QRegExp propertyRegExp = QRegExp("([_\\d\\w]+)([.]|[[]([\\d]+)[]][.])([_\\d\\w]+)");
// static QRegExp textRegExp = QRegExp("([_\\d\\w]+)([#]|[[]([\\d]+)[]][#])(text)");
// static QRegExp commentRegExp = QRegExp("([_\\d\\w]+)([#]|[[]([\\d]+)[]][#])(comment)");
// static QRegExp cdataRegExp = QRegExp("([_\\d\\w]+)([#]|[[]([\\d]+)[]][#])(cdata)");
// static QRegExp nodeRegExp = QRegExp("([_\\d\\w]+)([[]([\\d]+)[]]|$)");

using namespace SxDomUtils;
namespace SxDomUtils {
	class DomPathPrivate : public QSharedData{
	public:
		NodeList path;
		QDomElement element;
	};
}

DomPath::DomPath( const QDomElement &elem, const QString &path )
{
	d = new DomPathPrivate();
	d->element = elem;
	setPath(path);
}

DomPath::DomPath( const QDomDocument &doc, const QString &path )
{
	d = new DomPathPrivate();
	d->element = doc.documentElement();
	setPath(path);
}

DomPath::DomPath( const DomPath & path )
{
	d = new DomPathPrivate();
	d->element = path.d->element;
	d->path = path.d->path;
}

DomPath DomPath::operator =( const DomPath & path )
{
	d->element = path.d->element;
	d->path = path.d->path;
	return *this;
}

bool DomPath::operator==( const DomPath &right )
{
	if( nodeInPath() == right.nodeInPath() )
		return true;
	else
		return false;
}

DomPath::operator QString() const
{
	return fullPath();
}

SxDomUtils::DomPath::~ DomPath( )
{
}
/*
if( contains [ or ] )
	nodeText = seek until first [
	index = seek until next ]
else
	nodeText = seek until . or seek until # or seek until end
if( next char == . )
	seek until end
	type = property
if( next char == # )
	if( text until end == text )
		type = text
	if( text until end == cdata )
		type = cdata
	if( text until end == comment )
		type = comment
if( next char == end )
	type = text
*/

SxDomUtils::Node parseNode( const QString &pathFragment )
{
	int parserStartIndex = 0;
	int parserEndIndex = pathFragment.indexOf('[');
	SxDomUtils::Node node;
	if( parserEndIndex != -1 )
	{
		node.nodeText = pathFragment.left(parserEndIndex);
		parserStartIndex = parserEndIndex + 1;
		parserEndIndex = pathFragment.indexOf( ']', parserStartIndex );
		if( parserEndIndex != -1 )
		{
			node.index = pathFragment.mid( parserStartIndex, parserEndIndex - parserStartIndex).toInt();
			parserStartIndex = parserEndIndex + 1;
		}
		else
		{
			qDebug("parser error, unterminated index");
			node.type = Node::INVALID;
			return node;
		}
		
		if( pathFragment.endsWith(']') )
		{
			node.type = Node::ELEMENT;
		}
	}
		
	parserEndIndex = pathFragment.indexOf('#', parserStartIndex );
	if( parserEndIndex != -1 ) // Text,Comment,CData
	{
		if( node.nodeText.isEmpty() )
			node.nodeText = pathFragment.mid( parserStartIndex, parserEndIndex - parserStartIndex);
		if( pathFragment.endsWith("text") )
		{
			node.type = Node::TEXT;
		}
		else if ( pathFragment.endsWith("cdata") )
		{
			node.type = Node::CDATA;
		}
		else if ( pathFragment.endsWith("comment") )
		{
			node.type = Node::COMMENT;
		}
		else
		{
			qDebug("parser error, invalid data type");
			node.type = Node::INVALID;
			return node;
		}
	}
	else
	{
		parserEndIndex = pathFragment.indexOf('.', parserStartIndex );
		if( parserEndIndex != -1 ) // property
		{
			node.type = Node::PROPERTY;
			if( node.nodeText.isEmpty() )
				node.nodeText = pathFragment.mid( parserStartIndex, parserEndIndex - parserStartIndex);
			node.property = pathFragment.mid( parserEndIndex + 1 );
		}
		else // Text
		{
			node.type = Node::ELEMENT;
			if( node.nodeText.isEmpty() )
				node.nodeText = pathFragment.mid( parserStartIndex);
		}
	}
	
// 	qDebug() << node.nodeText << node.property << node.index << node.type;
	
	return node;
}

bool DomPath::setPath( const QString &path )
{

	// / - delimit a node
	foreach( QString token, path.split('/', QString::SkipEmptyParts) )
	{
		SxDomUtils::Node node = parseNode(token);
		if( node.type != Node::INVALID )
			d->path.append(node);
		else
		{
			qWarning("parser error %s", qPrintable(token) );
			d->path.clear();
			return false;
		}
		/*
		// 1    3    4
		// node[idx].property - property
		if( propertyRegExp.exactMatch(token) )
		{
			node.nodeText = propertyRegExp.cap(1);
			node.index = propertyRegExp.cap(3).toInt();
			node.property = propertyRegExp.cap(4);
			node.type = Node::PROPERTY;
			d->path.append(node);
		}
		// 1    3    4
		// node[idx]#text - text
		else if ( textRegExp.exactMatch(token) )
		{
			node.nodeText = textRegExp.cap(1);
			node.index = textRegExp.cap(3).toInt();
			node.type = Node::TEXT;
			d->path.append(node);
		}
		// 1    3    4
		// node[idx]#comment - comment
		else if ( commentRegExp.exactMatch(token) )
		{
			node.nodeText = commentRegExp.cap(1);
			node.index = commentRegExp.cap(3).toInt();
			node.type = Node::COMMENT;
			d->path.append(node);
		}
		// 1    3    4
		// node[idx]#cdata - cdata
		else if ( cdataRegExp.exactMatch(token) )
		{
			node.nodeText = cdataRegExp.cap(1);
			node.index = cdataRegExp.cap(3).toInt();
			node.type = Node::CDATA;
			d->path.append(node);
		}
		// 1    3
		// node[idx] - node
		else if ( nodeRegExp.exactMatch(token) )
		{
			node.nodeText = nodeRegExp.cap(1);
			node.index = nodeRegExp.cap(3).toInt();
			node.type = Node::ELEMENT;
			d->path.append(node);

		}
		else // Parse error
		{
			qWarning("parser error %s", qPrintable(token) );
			d->path.clear();
			return false;
		}
		*/
		
	}
        createElement();
	return true;
}

QDomElement DomPath::createElement() const
{
	QDomNode current = d->element;
	QDomNode newNode;
	// walk path
	// check if node is present, if not add it
	NodeList::ConstIterator it = begin();
	if( it == end() )
		return current.toElement();
	current = elementAtNode( d->element, (*it) );
	it++;
	for( ; it != end(); ++it )
	{
		for(int idx = 0; idx <= (*it).index; ++idx)
		{
			newNode = createNode(current, (*it) );
		}
		current = newNode;
	}
	return current.toElement();
}

QDomElement DomPath::elementInPath( ) const
{
	return nodeInPath().toElement();
}

QDomNode DomPath::nodeInPath() const
{
	QDomNode currentNode = d->element;
	int max = d->path.size() - 1;
	int idx = 0;
	foreach( Node node, d->path )
	{
                currentNode = elementAtNode(currentNode, node );
		if(  idx < max)
			currentNode = currentNode.firstChild();
		++idx;
	}
	return currentNode;
}

QDomElement DomPath::elementInPath( const QString &path ) const
{
	DomPath newPath( elementInPath(), path );
	return newPath.elementInPath();
}

QList<QDomElement> DomPath::elementListInPath( ) const
{
	QDomNode currentNode = elementInPath( );
	Node node = d->path.last();
	return elementsAtNode(currentNode, node);
}

bool isEmpty( const QDomElement& elem )
{
	if( elem.hasChildNodes())
		return false;
	if( elem.hasAttributes() )
		return false;
	if( !elem.nodeValue().isEmpty() )
		return false;
	return true;
}

int DomPath::count( ) const
{
	Node node = d->path.last();
	if( node.type == Node::ELEMENT)
	{
		QList<QDomElement> elems = elementListInPath();
		int cnt = elems.count();
	
		if( cnt == 1 && isEmpty( elems[0] ) ) return 0;
		return cnt;
	}
	else
	{
		if( getValue().isEmpty() )
			return 0;
		else
			return 1;
	}
}

int DomPath::count( const QString & path ) const
{
	DomPath newPath( elementInPath(), path );
	return newPath.count();
}

QString DomPath::getValue() const
{
	QDomElement elem = elementInPath();
	Node last = lastNode();
	return nodeValue( elem, last);
}

QString DomPath::getValue( const QString &path ) const
{
	DomPath newPath( elementInPath(), path );
	return newPath.getValue();
}

QString DomPath::xml() const
{
	QString returnString;
	QTextStream ts( &returnString, QIODevice::WriteOnly );
	ts << d->element << endl;
	return returnString;
}

void DomPath::setValue( const QString &value )
{
	QDomNode current = createElement();

        // at the last value set the property
	populateNode( current, lastNode(), value );
}

void DomPath::setValue( const QString &path, const QString &value )
{
	
	childPath(path).setValue(value);
}

DomPath DomPath::childPath( const QString &path ) const
{
	QDomElement element = createElement();
	
	DomPath chPath( element, path);
	return chPath;
}

void DomPath::removeElement( )
{
	QDomElement elem = elementInPath();
	Node last = lastNode();
	removeNode( elem, last);
}

void DomPath::removeElement( const QString &path )
{
	DomPath newPath( elementInPath(), path);
	childPath(path).removeElement();
}

void DomPath::setDomElement( const QDomElement & elem )
{
	d->element = elem;
}

Node DomPath::lastNode( ) const
{
	return d->path.last();
}

NodeList::Iterator DomPath::begin( )
{
	return d->path.begin();
}

NodeList::ConstIterator DomPath::begin( ) const
{
	return d->path.begin();
}

NodeList::Iterator DomPath::end( )
{
	return d->path.end();
}

NodeList::ConstIterator DomPath::end( ) const
{
	return d->path.end();
}

QStringList DomPath::elementChildren() const
{
	QStringList children;
	QMap<QString,int> nodeCount;
	QDomNodeList nodeList = nodeInPath().childNodes();
	int size = nodeList.size();
	for( int idx = 0; idx < size; ++idx )
	{
		QDomElement child = nodeList.at( idx ).toElement();
		if( !child.isNull() )
		{
			QString path = child.nodeName();
			if( nodeCount[path]  != 0 )
				children << path + "[" + QString::number(nodeCount[path] ) + "]";
			else
				children << path;
			nodeCount[child.nodeName()] = nodeCount[child.nodeName()] + 1;
		}
	}
	return children;
}

QStringList DomPath::elementProperties() const
{
	QStringList properties;
	QDomNamedNodeMap attribMap = elementInPath().attributes();
	for( int idx = 0; idx < attribMap.size(); ++idx )
	{
		QDomAttr attr = attribMap.item( idx ).toAttr();
		properties << attr.nodeName();
	}

	return properties;
}

QString DomPath::elementParent() const
{
	QDomElement parent = elementInPath( ).parentNode().toElement();
	int index = 0;
	QDomElement sibling = parent.previousSiblingElement( parent.nodeName() );
	while( !sibling.isNull() )
	{
		index++;
		sibling = sibling.previousSiblingElement( parent.nodeName() );
	}
	if( index == 0 )
		return parent.nodeName();
	else
		return parent.nodeName() + "[" + QString::number(index) + "]";
}

QString DomPath::fullPath() const
{
	QString path;

	QDomNode parent = nodeInPath( );
	while( !parent.isNull() )
	{
		int index = 0;
		QDomElement sibling = parent.previousSiblingElement( parent.nodeName() );
		while( !sibling.isNull() )
		{
			index++;
			sibling = sibling.previousSiblingElement( parent.nodeName() );
		}
		if( index == 0 )
			path = parent.nodeName() + "/" + path;
		else
			path = parent.nodeName() + "[" + QString::number(index) + "]/" + path;
		parent = parent.parentNode().toElement();
	}
	if( path.endsWith("/") )
		path.chop( 1 );
	if( d->path.size() != 0 )
	{
		if( lastNode().type == Node::PROPERTY )
			path += "." + lastNode().property;
		if( lastNode().type == Node::TEXT )
			path += "#text";
		if( lastNode().type == Node::CDATA )
			path += "#cdata";
		if( lastNode().type == Node::COMMENT )
			path += "#comment";
	}
	return path;
}

QString DomPath::property() const
{
	return lastNode().property;
}

QString SxDomUtils::getValue(const QDomElement &elem, const QString &path)
{
	DomPath dom( elem, path );
	return dom.getValue();
}

void SxDomUtils::setValue(const QDomElement &elem, const QString &path, const QString &value )
{
	DomPath dom( elem, path );
	dom.setValue(value);
}

int SxDomUtils::count(const QDomElement &elem, const QString &path)
{
	DomPath dom( elem, path );
	return dom.count();
}

QDomElement SxDomUtils::getElement( const QDomElement &elem, const QString &path )
{
	DomPath dom( elem, path );
	return dom.elementInPath();
}

void SxDomUtils::removeElement( const QDomElement &elem, const QString &path )
{
	DomPath dom( elem, path );
	dom.removeElement();
}






