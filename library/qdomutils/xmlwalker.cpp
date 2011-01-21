/*
    Copyright (C) Ian Reinhart Geiser  <geiseri@sourcextreme.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include "xmlwalker.h"
#include <QTreeWidget>
#include <qmap.h>


using namespace SxDomUtils;

XMLNodeItem::XMLNodeItem( QTreeWidget *parent, const QDomNode &node )
{
    m_parent = 0L;
    m_item = new QTreeWidgetItem( parent );
    init(node, 0);
}

XMLNodeItem::XMLNodeItem( XMLNodeItem *parent, int offset, const QDomNode &node ) : m_parent(parent)
{
    m_item = new QTreeWidgetItem( m_parent->m_item );
    init(node, offset);
}


void XMLNodeItem::init( const QDomNode &node, int offset )
{
    QMap<QString,int> currentIndex;
    
    QDomNode current = node.firstChild();
    for( ; !current.isNull(); current = current.nextSibling() )
        m_children.append( new XMLNodeItem( this, currentIndex[current.nodeName()]++, current) );

    if( offset != 0 )
        m_item->setText(0,QString("%1[%2]").arg(node.nodeName()).arg(offset));
    else
        m_item->setText(0,node.nodeName());
}

XMLNodeItem::~XMLNodeItem( )
{
	qDeleteAll(m_children);
	m_children.clear();
	delete m_item;
}

QString XMLNodeItem::path( const QString &root, QTreeWidgetItem *itm) const
{
    QString childPathNoIndex = "%1/%2";
    QString currentText = m_item->text(0);
    
    QString currentPath;
    if( currentText == "#text" || currentText == "#comment" || currentText == "#cdata")
        currentPath = root + currentText;
    else
        currentPath = childPathNoIndex.arg(root).arg(currentText);
         
    if( m_item == itm )
    {
        if( currentPath[0] == '/' ) currentPath.remove(0,1);
        return currentPath;
    }
    
    foreach( XMLNodeItem *item, m_children )
    {
        QString currentChild = item->m_item->text(0);
        QString newPath = item->path( currentPath, itm );  
        if( !newPath.isEmpty() ) return newPath;
    }
    return QString::null;
}

