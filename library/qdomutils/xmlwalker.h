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
#include <qstring.h>
#include <qdom.h>
#include <QList>

class QTreeWidgetItem;
class QTreeWidget;
namespace SxDomUtils 
{
	class XMLNodeItem
	{
	public:
		XMLNodeItem( QTreeWidget *parent, const QDomNode &node );
		XMLNodeItem( XMLNodeItem *parent, int offset, const QDomNode &node );
		~XMLNodeItem( );
		QString path( const QString &root, QTreeWidgetItem *itm) const;
		
	private:
		void init( const QDomNode &node, int offset );
		XMLNodeItem *m_parent;
		QTreeWidgetItem *m_item;
		QList<XMLNodeItem*> m_children;
	};
}
