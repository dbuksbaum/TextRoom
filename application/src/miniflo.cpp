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
#include "miniflo.h"
#include "block.h"
#include "mindmap.h"
#include "blockpropertymodel.h"
#include "asciiexportdialog.h"
#include "asciireporter.h"
#include "basicpropertyeditor.h"
#include "floparserobserver.h"
#include "textroom.h"

#include <QDir>
#include <QGraphicsScene>
#include <QDockWidget>
#include <QUndoView>
#include <QTreeView>
#include <QDataWidgetMapper>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QImageWriter>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>
#include <QSettings>
#include <QLibrary>
#include <QPictureIO>
#include <QSpinBox>
#include <QDomDocument>

#include <qdebug.h>

const QString windowTitleTemplate = "MiniFlo - (%1)[*]";

MiniFlo::MiniFlo(QWidget *parent)
	: QDialog(parent)
{
	m_ui.setupUi(this);
	m_file = new MindMap(this);

        QPlastiqueStyle * style = new QPlastiqueStyle();
        MiniFlo::setStyle(style);

	m_ui.graphicsView->setScene(m_file->scene());
	m_ui.graphicsView->setMindmap(m_file);

	setupDocks();
	setupModel();
	setupMiniFlo();

	connect( m_ui.graphicsView, SIGNAL( reparentBlocks(Block*,Block*)),
	         m_file, SLOT(slotReparentBlocks(Block*,Block*)));
	connect( m_ui.graphicsView, SIGNAL( selectionChanged()),
	         m_file, SLOT(itemSelectionChanged()));
	connect( m_file, SIGNAL(fileLoaded( const QString& )),
	         this, SLOT(fileLoaded(const QString &)));
}

void MiniFlo::on_actionSave_activated( )
{
	qDebug() << QPictureIO::inputFormats() << QPictureIO::outputFormats();
	m_file->slotSaveFile();
}


void MiniFlo::on_actionLoad_activated( )
{
	m_file->slotOpenFile();
}

void MiniFlo::on_actionArrangeChildren_activated()
{
	m_file->arrangeBlocks();
}

void MiniFlo::setupDocks( )
{
}

void MiniFlo::setupModel( )
{
	m_file->propertyModel()->setBlock(m_file->root());
}

void MiniFlo::on_actionReparentIdea_activated( )
{
	m_ui.graphicsView->setMode( MindMapView::Reparent );
}

void MiniFlo::on_actionRemoveIdea_activated( )
{
	m_file->deleteSelection();
}

void MiniFlo::on_actionCut_activated( )
{
	m_file->cutSelection();
}

void MiniFlo::on_actionNew_activated( )
{
	m_file->slotNewFile();
}

void MiniFlo::on_actionCopy_activated( )
{
	m_file->copySelection();
}

void MiniFlo::on_actionPaste_activated( )
{
	m_file->pasteNode(m_file->selectedNode());
}

void MiniFlo::on_actionQuit_activated( )
{
	accept();
}

void MiniFlo::on_actionAddIdea_activated( )
{
	m_file->createChildOnSelection();
}

QString generateImageFilter()
{
	QList<QByteArray> formats = QImageWriter::supportedImageFormats();
	QStringList returnFormats;
	const QString filterTemplate = "*.%1";
	foreach( QString format, formats )
		returnFormats += filterTemplate.arg(format);

#if QT_VERSION >= 0x040300
	returnFormats += "*.svg";
#endif
	return returnFormats.join(" ");
}

void MiniFlo::on_actionInsertAsOutline_activated( )
{
	ASCIIExportDialog::exportMindmap( m_file );
}

void MiniFlo::on_actionSelectAll_activated( )
{
	m_file->selectAllBlocks();
	on_graphicsView_selectionChanged();
}

void MiniFlo::closeEvent( QCloseEvent * event )
{
	if( m_file->queryCloseCurrentFile() )
	{
		QSettings settings;
		settings.setValue("MiniFlo/Geometry", geometry() );
		event->accept();
	}
	else
		event->accept();
}

void MiniFlo::on_actionReload_activated( )
{
	m_file->slotReloadFile();
}

void MiniFlo::setupMiniFlo( )
{
	QDesktopWidget desktop;
	QSettings settings;

	setGeometry( settings.value("MiniFlo/Geometry",
	                            desktop.availableGeometry(this).adjusted(25,25,-50,-50)).value<QRect>() );
}

void MiniFlo::updateWindowTitle( const QString & fileName )
{
	setWindowTitle( windowTitleTemplate.arg(fileName));
}

void MiniFlo::fileLoaded( const QString & fileName )
{
	m_file->root()->setSelected(true);
	m_ui.graphicsView->setZoomView(100);
	m_ui.graphicsView->ensureVisible( m_file->root() );
	updateWindowTitle( fileName );
	m_file->scene()->update();
}

void MiniFlo::on_actionColorIdea_activated( )
{
	m_file->colorSelection();
}


void MiniFlo::on_actionChangeType_activated( )
{
	m_file->changeShapeSelection();
}

void MiniFlo::on_actionProperties_activated( )
{
	BasicPropertyEditor editor( m_file, this);
	editor.setupModel( m_file->propertyModel() );
	editor.exec();
}

void MiniFlo::on_graphicsView_selectionChanged( )
{
	int items = m_file->selectedNodes().size();
	if( items == 0 )
	{
		m_ui.actionCut->setEnabled(false);
		m_ui.actionCopy->setEnabled(false);
		m_ui.actionPaste->setEnabled(true);
		m_ui.actionAddIdea->setEnabled(false);
		m_ui.actionRemoveIdea->setEnabled(false);
		m_ui.actionColorIdea->setEnabled(false);
		m_ui.actionChangeType->setEnabled(false);
		m_ui.actionProperties->setEnabled(false);
		m_ui.actionReparentIdea->setEnabled(false);
	}
	else if( items == 1 )
	{
		m_ui.actionCut->setEnabled(true);
		m_ui.actionCopy->setEnabled(true);
		m_ui.actionPaste->setEnabled(true);
		m_ui.actionAddIdea->setEnabled(true);
		m_ui.actionRemoveIdea->setEnabled(true);
		m_ui.actionColorIdea->setEnabled(true);
		m_ui.actionChangeType->setEnabled(true);
		m_ui.actionProperties->setEnabled(true);
		m_ui.actionReparentIdea->setEnabled(true);
	}
	else
	{
		m_ui.actionCut->setEnabled(true);
		m_ui.actionCopy->setEnabled(true);
		m_ui.actionPaste->setEnabled(true);
		m_ui.actionAddIdea->setEnabled(false);
		m_ui.actionRemoveIdea->setEnabled(true);
		m_ui.actionColorIdea->setEnabled(true);
		m_ui.actionChangeType->setEnabled(true);
		m_ui.actionProperties->setEnabled(false);
		m_ui.actionReparentIdea->setEnabled(false);
	}
}
