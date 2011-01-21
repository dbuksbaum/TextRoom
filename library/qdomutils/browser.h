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
#include <qdialog.h>
#include <qdom.h>

class QTreeWidgetItem;
class QListWidgetItem;

namespace SxDomUtils {
/**
* A QDialog that can browse an QDom and show the currently selected node's path.
* @image html node_browser.png Node browser
*/
class NodeBrowser : public QDialog
{
Q_OBJECT
/**
* Current path that the browser has selected.
*/
Q_PROPERTY( QString currentPath READ currentPath )

public:
	/**
	* Construct a new NodeBrowser widget.
	*/
	NodeBrowser( QWidget *parent );
	virtual ~NodeBrowser( );
	
	/**
	* Set the current DOM Element to browse from the view.
	*/
	void setRoot( const QDomElement &elem  );
	
	/**
	* Return the currently selected path.
	*/
	QString currentPath() const;
    
private slots:
	void itemClicked( QTreeWidgetItem *itm );
	void propertyClicked( QListWidgetItem *itm );

private:
	class NodeBrowserPrivate *d;
};

}
