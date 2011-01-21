/***************************************************************************
 *   Copyright (C) 2006 by Ian Reinhart Geiser   *
 *   geiseri@yahoo.com   *
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
#ifndef BASICPROPERTYEDITOR_H
#define BASICPROPERTYEDITOR_H

#include <QDialog>

namespace QModelAdaptor
{
	class QAdaptorManager;
}
namespace Ui
{
	class ContentsWidget;
}
class BlockPropertyModel;
class QAbstractItemModel;
class MindMap;
class RotatedProxyModel;

/**
A basic property editor that will change the title, text contents and the index of the current block.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class BasicPropertyEditor : public QDialog
{
	Q_OBJECT
public:
	BasicPropertyEditor(MindMap * mindmap, QWidget * guiParent);
	~BasicPropertyEditor();

	QStringList properties() const;

public slots:
	void updateMaximumIndex( int index );
	void setupModel( BlockPropertyModel *model );

private:
	Ui::ContentsWidget *m_contents;
	QModelAdaptor::QAdaptorManager *m_blockPropertyManager;
	QAbstractItemModel *m_shapes;
	RotatedProxyModel *m_proxyModel;
};

#endif
