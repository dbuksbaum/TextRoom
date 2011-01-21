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
#ifndef NODE_H
#define NODE_H

#include <QString>
namespace SxDomUtils
{
	/**
	* Simple node in an XML class.
	*/
	struct Node
	{
		/**
		* Construct an empty node with the @ref type set to TEXT.
		*/

		Node();
		/**
		* The tag that represents the node.
		*/
		QString nodeText;

		/**
		* Node types:
		* @li PROPERTY - A property of an element.
		* @li COMMENT - A comment node.
		* @li TEXT - A text node
		* @li CDATA - A data node.
		* @li ELEMENT - A normal element.
		* @li INVALID - An invalid element.
		*/
		enum Type {PROPERTY,COMMENT,TEXT,CDATA,ELEMENT,INVALID};

		/**
		* The type of the node.
		*/
		Type type;

		/**
		* The offset in the tree the node lies at.
		*/
		int index;

		/**
		* The tag of the property that should be retrived.
		*/
		QString property;
	};
}
#endif
