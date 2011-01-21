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
#ifndef ELEMENTTOOLS_H
#define ELEMENTTOOLS_H

#include <node.h>
#include <QDomNode>
#include <QList>

namespace SxDomUtils
{

	/**
	* Returns the QDomNode that has the name and index defined in @ref Node.
	* The following code
	* @code
	* Node node; // node.nodeText = "choice", node.index = 1
	* QDomNode elem; // XML element at test/options/choice
	* elementAtNode(elem,node) // would return the second choice QDOMNode
	* @endcode
	* applied to the following XML
	* @code
	* <test>
	* <options>
	* <choice value = "apple"/>
	* <choice value = "orange"/>
	* </options>
	* </test>
	* @endcode
	*/
	QDomNode elementAtNode( const QDomNode &elem, const Node &node );

	QList<QDomElement> elementsAtNode( const QDomNode &elem, const Node &node );

	QDomNode createNode( QDomNode &elem, const Node &node );

	void populateNode( const QDomNode &elem, const Node &node, const QString &value );

	QString nodeValue( const QDomNode &elem, const Node &node );

	void removeNode( const QDomNode &elem, const Node &node );

}
#endif
