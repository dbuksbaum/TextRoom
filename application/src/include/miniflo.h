/***************************************************************************
 *   Copyright (C) 2006-2008 by Ian Reinhart Geiser                        *
 *   geiseri@yahoo.com                                                     *
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
#ifndef MINIFLO_H
#define MINIFLO_H

#include <QDialog>

#include "ui_miniflo.h"

class Block;
class MindMap;
class QGraphicsScene;
class QAbstractItemModel;
class QTreeView;
class BlockPropertyModel;

class MiniFlo: public QDialog {
Q_OBJECT
public:
    MiniFlo(QWidget *parent = 0);

public slots:
	void on_actionArrangeChildren_activated();
	void on_actionReparentIdea_activated();
	void on_actionRemoveIdea_activated();
	void on_actionAddIdea_activated();
	void on_actionSelectAll_activated();
	void on_actionColorIdea_activated();
	void on_actionChangeType_activated();
	void on_actionProperties_activated();
	void on_actionInsertAsOutline_activated();
	void on_graphicsView_selectionChanged();
	void on_actionNew_activated();
	void on_actionSave_activated();
	void on_actionLoad_activated();
	void on_actionCut_activated();
	void on_actionCopy_activated();
	void on_actionPaste_activated();
	void on_actionQuit_activated();
	void on_actionReload_activated();
	void updateWindowTitle( const QString &fileName );
	void fileLoaded( const QString &fileName );

protected:
	void closeEvent ( QCloseEvent * event );

private:
	void setupDocks();
	void setupModel();
	void setupMiniFlo();

	Ui::MiniFlo m_ui;

	QTreeView *m_propertiesView;
	MindMap *m_file;
	QSlider *m_slider;
};

#endif
