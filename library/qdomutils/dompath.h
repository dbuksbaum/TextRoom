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
#ifndef DOMPATH_H
#define DOMPATH_H

#include <node.h>
#include <QList>
#include <QDomNode>
#include <QSharedData>

/**
* A set of QDom tools that allow for easy traversal of the DOM.
* The entire toolset is built around the idea of "paths" in the XML.  Since nodes
* do not need to be unique, nodes are indexed.
* example: test/items/item[1] is the second item element in the items group.
*
* In the XML:
* @code
* <test>
*     <objects>
*             <object value="test1"/>
*             <object value="test2"/>
*             <object value="test3"/>
*     <objects>
* </test>
* @endcode
* The following path would contain the value "test3"
* @code
*  test/objects/object[2].value
* @endcode
*/
namespace SxDomUtils
{
	/**
	* Simple list of @ref Node objects.
	*/
	typedef QList<Node> NodeList;

	/**
	* The direct utilty class for manipulating QDom elements. A DOM path is a tokenised list
	* of child element names that can be used to find a particular node in a DOM.  DomPath objects are
	* rooted with a base QDomElement, and from there paths can be used to read values of children
	* of that element, or to return a new QDomElement for use with other paths.
	*
	* The path inside of the XML is similar to the way one would traverse a filesystem.  The
	* noted exception is that element names can be duplicated.  In this case we use an indexed
	* notation to figure out which element is to be accessed.  Each element is delimited by a '/'
	* charicter.  The path:
	* @code
	* /element/element
	* @endcode
	* would look like the following XML:
	* @code
	* <element>
	*	<element>
	* </element>
	* @endcode
	*
	* The next notation in the path is the '.' charicter.  This denotes an attribute of an XML element.
	* Attributes are unique so they will never have an index notation.  The following path:
	* @code
	* /element/element.attribute
	* @endcode
	* would look like the following XML:
	* @code
	* <element>
	*	<element attribute="some value">
	* </element>
	* @endcode
	*
	* There are special elements that can also be noted.  These are comments, cdata and text.
	* There can only be one of these per element, and are prefixed by a '#' charicter.
	  The following path:
	* @code
	* /element/element#text
	* @endcode
	* would look like the following XML:
	* @code
	* <element>
	*	<element>Some text</element>
	* </element>
	* @endcode
	*
	* To use a path to access a value inside of a QDomDocument the following method can be used:
	* @code
	* QDomDocument doc;
	* doc.setConent(someXML);
	* DomPath myPath( doc, "path/into/the/xml#text");
	* QString  myValue = myPath.getValue() );
	* @endcode
	* This will have a DomPath to a specific node's text property and can be used to access this
	* value.  Developers who wish to perform multiple operations on the node can also return the node
	* with @ref elementInPath as to not have to walk the DomPath over and over again.
	*
	* One other method of use is to use the current path to access children easier.  An example of this is below:
	* @code
	* QDomDocument doc;
	* doc.setContent(someXML);
	* DomPath myPath( doc, "path/into/the/xml");
	* QString otherValue = myPath.getValue("xml.value");
	* QString textValue = myPath.getValue("xml#text");
	* @endcode
	* This will return the value attribute of the XML node, as well as the text property.
	*/
	class DomPath
	{
		public:
		/**
		* Create a new DomPath that is rooted at the @ref QDomElement element elem.
		* The  path is optional.  If it is supplied it will be used as the default
		* path for @ref elementInPath, @ref elementListInPath and @ref count.
		*/
		DomPath( const QDomElement &elem = QDomElement(), const QString &path = QString::null );

		/**
		* Create a new DomPath with a @ref QDomDocument vs a @ref QDomElement
		*/
		DomPath( const QDomDocument &doc, const QString &path = QString::null );

		/**
		*/
		DomPath operator=( const DomPath &path);

		bool operator==( const DomPath &right );

		operator QString() const;

		DomPath(const DomPath &path);

		~DomPath();

		/**
		* Set the current path to path.  This path will then be used for
		* @ref elementInPath, @ref elementListInPath and @ref count.
		* Parser:
		* @li / - delimit a node
		* @li . - delimit a property
		* @li # - delimit a built-in
		* @li [ - start index
		* @li ] - end index
		**/
		bool setPath( const QString &path );

		//QString path( ) const;

		/**
		* Set the current @ref QDomElement that will be accessed by the path.
		*/
		void setDomElement( const QDomElement &elem );

		/**
		* Returns the value the current path at a path.
		*/
		QString getValue() const;

                /**
                * Creates all of the child elements that complete a path.
                */
                QDomElement createElement() const;

		/**
		* Returns the value at the path, using the current element as the root.
		* NOTE: this will not modify the internal path.
		*/
		QString getValue( const QString &path ) const;

		/**
		* Sets a value at a path.
		*/
		void setValue( const QString &value );

		/**
		* Sets the value at the path, using the current element as the root node.
		* NOTE: this will not modify the internal path.
		*/
		void setValue( const QString &path, const QString &value );

		/**
		 * Returns a DomPath of a child path.
		 * NOTE: this will not modify the internal path.
		 */
		DomPath childPath( const QString &path ) const;
		
		/**
		* Returns the number of siblings on a path.  This is useful for iterating over a
		* group of siblings in a tree
		* @code
		* DomPath path( element, "list/item");
		* int max = path.count();
		* for( int idx = 0; idx < max; ++idx);
		* {
		*    QString val = path.getValue( QString("item[%1].property").arg(idx));
		* }
		* @endcode
		* This example will return all of the "item's" "property" in a "list".
		*/
		int count( ) const;

		/**
		* Returns the number of siblings on a path.
		*/
		int count(const QString &path) const;

		/**
		* Returns the XML that is contained in the QDomElement at the path,
		* using the current element as the root node.
		* NOTE: this will not modify the internal path.
		*/
		QString xml() const;

		/**
		* Removes an element from a path.
		*/
		void removeElement( );

		/**
		* Removes a child element from a path.
		*/
		void removeElement( const QString &path );

		/**
		* Returns the current QDomElement that is referenced by the path.
		* This is useful for building new @ref DomPath objects without dealing
		* with parent nodes.
		*/
		QDomElement elementInPath( ) const;

		/**
		* Returns the current QDomElement that is referenced by the path,
		* using the current element as the root.
		*/
		QDomElement elementInPath( const QString &path ) const;

		/**
		* Returns the top level @ref QDomElement in a node.
		*/
		QList<QDomElement> elementListInPath( ) const;

		/**
		* Returns the last @ref Node in a path.
		*/
		Node lastNode() const;

		/**
		* The first node in the path.
		*/
		NodeList::Iterator begin();
		/**
		* The first node in the path.
		*/
		NodeList::ConstIterator begin() const;
		/**
		* The end of the path.
		*/
		NodeList::Iterator end();
		/**
		* The end of the path.
		*/
		NodeList::ConstIterator end() const;

		/**
		* Return the children of the path as a QStringList
		*/
		QStringList elementChildren() const;

		/**
		* Return a list of the elements properties.
		*/
		QStringList elementProperties() const;

		/**
		* Return the parent of the current path.
		*/
		QString elementParent() const;

		/**
		* Return the full path from the current DomPath to the document root.
		*/
		QString fullPath() const;

		/**
		 * Returns the name of the property if any that is being read.
		 */
		QString property() const;
		
		private:
			QDomNode nodeInPath() const;
			QSharedDataPointer<class DomPathPrivate> d;
	};

	/**
	* Convienence method that returns the value at a path.
	* @code
	* QDomElement someElement = doc.documentElement();
	* QString value = getValue(someElement, "path/in/xml.property");
	* @endcode
	*/
	QString getValue(const QDomElement &elem, const QString &path);

	/**
	* Convienence method that sets a value at a path.
	*/
	void setValue(const QDomElement &elem, const QString &path, const QString &value );

	/**
	* Convienence method that returns the number of siblings on a path.
	*/
	int count(const QDomElement &elem, const QString &path);

	/**
	* Returns a QDomElement at a path.  This can be used as a base for other paths.
	*/
	QDomElement getElement( const QDomElement &elem, const QString &path );

	/**
	* Removes a QDomElement at a path.
	*/
	void removeElement( const QDomElement &elem, const QString &path );
}
#endif

