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
#include "browser.h"
#include "ui_browser_base.h"
#include <qlineedit.h>
#include <QHBoxLayout>
#include <dompath.h>
#include <QTreeWidget>
#include <QListWidget>
#include <xmlwalker.h>
#include <qpushbutton.h>
#include <qlayout.h>
using namespace SxDomUtils;

namespace SxDomUtils {
	class NodeBrowserPrivate {
	public:
		Ui::NodeBrowserBase browser;
		XMLNodeItem *node;
		QDomNode doc;
		QString domPath;
	};
}

NodeBrowser::NodeBrowser( QWidget *parent ) : QDialog(parent)
{
	d = new NodeBrowserPrivate();
	d->node = 0L;
	d->browser.setupUi(this);
	connect( d->browser.nodes, SIGNAL( currentChanged(QTreeWidgetItem*) ), this, SLOT( itemClicked(QTreeWidgetItem*) ) );
	connect( d->browser.properties, SIGNAL( currentChanged(QListWidgetItem*) ), this, SLOT( propertyClicked(QListWidgetItem*) ) );
	connect( d->browser.buttonOk, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( d->browser.buttonCancel, SIGNAL( clicked() ), this, SLOT( reject() ) );
}

NodeBrowser::~NodeBrowser( )
{
	delete d;
}

void NodeBrowser::setRoot( const QDomElement &elem )
{
	d->doc = elem;
	delete d->node;
	d->node = new SxDomUtils::XMLNodeItem( d->browser.nodes, d->doc );
	d->browser.nodes->setCurrentItem( d->browser.nodes->topLevelItem(0) );
	itemClicked(d->browser.nodes->topLevelItem(0));
}

void NodeBrowser::itemClicked( QTreeWidgetItem *itm )
{
	d->browser.properties->clear();
	
	if( itm == 0) return;
	
	d->domPath = d->node->path("",itm);
	d->browser.path->setText(d->domPath);
	
	QDomNode node = SxDomUtils::getElement( d->doc.toElement(), d->domPath ); 
	if( !node.isNull() )
	{
		QDomNamedNodeMap map = node.attributes();
		int count = map.count();
		for( int idx = 0; idx < count; ++idx)
		d->browser.properties->addItem( map.item(idx).nodeName() );
	}
}

void NodeBrowser::propertyClicked( QListWidgetItem *itm )
{
	d->browser.path->setText( d->domPath + "." + itm->text() );
}

QString NodeBrowser::currentPath() const
{
	return d->browser.path->text();
}

