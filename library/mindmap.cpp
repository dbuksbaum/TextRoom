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
#include "mindmap.h"
#include "blockpropertymodel.h"
#include "block.h"
#include "createblockcommand.h"
#include "blockpropertymodel.h"
#include "reparentblockcommand.h"
#include "deleteblockcommand.h"
#include "deletegroupcommand.h"
#include "cutgroupcommand.h"
#include "copygroupcommand.h"
#include "pasteblockcommand.h"
#include "positionitemscommand.h"
#include "changecolorgroupcommand.h"
#include "changefontgroupcommand.h"
#include "changeshapegroupcommand.h"
#include "movecommand.h"
#include "movegroupcommand.h"
#include "dompath.h"
#include "variantdompath.h"
#include "documentoptions.h"

#include <QUndoStack>
#include <QGraphicsScene>
#include <QTextStream>
#include <QAction>
#include <QIcon>
#include <QMessageBox>
#include <QImageWriter>
#include <QPainter>
#include <QImage>
#include <QApplication>
#include <QFileInfo>
#include <QDateTime>
#include <QProgressDialog>
#include <QTimer>

#include <math.h>

#if QT_VERSION >= 0x040300
#include <QSvgGenerator>
#endif

MindMap::MindMap( QObject *parent)
: SxFile(parent), m_root(0)
{
	QMap<QString,QString> supportedFiles;
	supportedFiles["flo"] = "Mindmaps";
	setSupportedFiles( supportedFiles );
	setBackupOnSave(true);
	setAutoSaveTimeout(5);

	m_commandStack = new QUndoStack(this);
	connect( m_commandStack, SIGNAL(cleanChanged( bool )), this, SLOT(slotCommandStackCleanChanged( bool )));
	m_propertyModel = new BlockPropertyModel(this, m_commandStack);
	m_scene = new QGraphicsScene(this);
	m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
}


MindMap::~MindMap()
{}

void MindMap::clearDocument( )
{
	QList<Block*> blockList;
	foreach( QGraphicsItem *item, scene()->items())
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
			blockList << block;
	}

	foreach( Block *block, blockList)
		block->detatch();

	qDeleteAll( blockList );
}

void MindMap::recalculateUUIDs( )
{
	foreach( QGraphicsItem *item, scene()->items())
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
		{
			block->calculateUUID();
			block->updateContents();
		}
	}
}

void MindMap::moveItem( Block * node, const QPointF & delta )
{
	m_commandStack->push(new MoveCommand(node->id(),delta,this));
}

void MindMap::slotReparentBlocks( Block * newParent, Block * child )
{
	m_commandStack->push(new ReparentBlockCommand(newParent->id(),child->id(),this));
}


void MindMap::createNode(  Block *parentNode, const QPointF & pos )
{
	m_commandStack->push(new CreateBlockCommand(parentNode->id(),pos,this));
}


void MindMap::deleteNode( Block * block )
{
	m_commandStack->push(new DeleteBlockCommand(block->id(), this));
}


void MindMap::cutNode( Block * block )
{
	m_commandStack->push(new CutGroupCommand(QList<QByteArray>() << block->id(), this));
}


void MindMap::copyNode( Block * block )
{
	m_commandStack->push(new CopyGroupCommand(QList<QByteArray>() << block->id(), this));
}


void MindMap::pasteNode( Block * block )
{
	m_commandStack->push(new PasteBlockCommand( this ));
}

Block *MindMap::resolveNodeByID( const QByteArray & id )
{
	QList<QGraphicsItem *> items = scene()->items();
	foreach( QGraphicsItem *item, items)
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
			if( block->id() == id )
			{
				return block;
			}
	}
	return 0;
}

Block *MindMap::resolveNodeByPath( const QByteArray & path )
{
	Block *current = root();
	foreach( QByteArray node, path.split('.'))
	{
		current = current->child(node.toInt());
	}
	return current;
}

QGraphicsScene* MindMap::scene() const
{
	return m_scene;
}

Block* MindMap::root() const
{
	return m_root;
}

void MindMap::setRoot( Block * node )
{
	m_root = node;
}

void MindMap::setupRootBlock( Block *block )
{
	setRoot( block );

	if( root() == 0 )
		return;

	root()->setTitle(tr("Main Thesis") );
	root()->setTopLevelNode( 1 );
	root()->setPos(scene()->sceneRect().center());
	root()->setShapeType( Block::Ellipse );
	root()->setMindmap(this);
	scene()->addItem(root());
	block->setSelected(true);
}


void MindMap::itemSelectionChanged( )
{
	if( selectedNode() )
	{
		emit maxIndex(selectedNode()->maxIndex() );
		propertyModel()->setBlock(selectedNode());
	}

}
BlockPropertyModel* MindMap::propertyModel() const
{
	return m_propertyModel;
}

QAction * MindMap::undoAction( )
{
	QAction *action =  m_commandStack->createUndoAction(this);
	action->setIcon(QIcon(":/library/icons/edit-undo.svg"));
	action->setShortcuts(QKeySequence::Undo);
	return action;
}

QAction * MindMap::redoAction( )
{
	QAction *action = m_commandStack->createRedoAction(this);
	action->setIcon(QIcon(":/library/icons/edit-redo.svg"));
	action->setShortcuts(QKeySequence::Redo);
	return action;
}


QUndoStack* MindMap::commandStack() const
{
	return m_commandStack;
}


Block *MindMap::selectedNode() const
{
	return selectedNodes().value(0);
}

#include <QTime>
#include <qdebug.h>

bool MindMap::loadData( QIODevice * iodevice )
{
	QDomDocument document;
	QString error;
	int line;
	int col;
	QTime timer;
	timer.start();

	if( document.setContent( iodevice, &error, &line, &col ) )
	{
		qDebug() << "Set content" << timer.elapsed();

		propertyModel()->setBlock(0);
		clearDocument();

		int blockCount = SxDomUtils::count( document.documentElement(), QLatin1String("mindmap/nodes/node"));
		int connCount = SxDomUtils::count( document.documentElement(), QLatin1String("mindmap/connections/connection"));

		QProgressDialog progress(tr("Loading mindmap..."), 0, 0, blockCount + connCount, QApplication::activeWindow());
		progress.setWindowModality(Qt::WindowModal);

		VariantDomPath mindmapProperties( document.documentElement(), QLatin1String("mindmap/properties"));
		m_properties = mindmapProperties.loadProperties();

		VariantDomPath mindmapImages( document.documentElement(), QLatin1String("mindmap/images/properties"));
		m_images = mindmapImages.loadProperties();

		timer.restart();
		for( int idx = 0; idx < blockCount; ++idx)
		{
			progress.setValue( idx );
			QApplication::processEvents();
			SxDomUtils::DomPath blockPath( document.documentElement(),
			                               QString("mindmap/nodes/node[%1]").arg(idx));
			Block *block = Block::loadBlock(blockPath, scene());
			if( block )
			{
				if( block->topLevelNode())
					setRoot(block);
				block->setMindmap(this);
			}
		}
		qDebug() << "blocks document" << timer.elapsed();
		timer.restart();

		QString startPathTemplate = QLatin1String("connection/node[%1].start");
		QString endPathTemplate = QLatin1String("connection/node[%1].end");
		QString connPathTemplate = QLatin1String("mindmap/connections/connection[%1]");

		for( int idx = 0; idx < connCount; ++idx)
		{
			progress.setValue( idx + blockCount);
			QApplication::processEvents();

			SxDomUtils::DomPath connPath( document.documentElement(), connPathTemplate.arg(idx));
			int nodeCount = connPath.count( "connection/node" );
			for( int nodeIdx = 0; nodeIdx < nodeCount; ++nodeIdx )
			{
				Block *start = resolveNodeByID( connPath.getValue( startPathTemplate.arg(nodeIdx) ).toLatin1() );
				Block *end = resolveNodeByID( connPath.getValue( endPathTemplate.arg(nodeIdx) ).toLatin1() );
				if( start == 0)
					qWarning( "No such start block %s", qPrintable(connPath.getValue( startPathTemplate.arg(nodeIdx) )));
				if( end == 0)
					qWarning( "No such end block %s", qPrintable(connPath.getValue( endPathTemplate.arg(nodeIdx) )));
				end->setParentNode(start);
			}
		}
		qDebug() << "connections document" << timer.elapsed();

		progress.setValue(connCount+blockCount);

		root()->setSelected(true);
		recalculateUUIDs();
		commandStack()->clear();
		itemSelectionChanged();
		emit modelChanged(propertyModel());
		return true;
	}
	else
	{
		QMessageBox::critical(0, tr("Error"), tr("Parse error \"%1\" at %2,%3")
			.arg(error).arg(line).arg(col), QMessageBox::Ok, QMessageBox::NoButton);
		return false;
	}
}

bool MindMap::saveData( QIODevice * iodevice )
{
	QTextStream ts(iodevice);
	QDomDocument document("mindmap");
	QDomNode root = document.appendChild( document.createElement( "mindmap" ) );
	int index = 0;
	QList<QGraphicsItem *> items = scene()->items();
	QTime time;
	time.start();
	QString blockPathTemplate = QLatin1String("mindmap/nodes/node[%1]");
	QString connPathTemplate = QLatin1String("mindmap/connections/connection[%1]");

	VariantDomPath mindmapProperties( document.documentElement(), QLatin1String("mindmap/properties"));
	mindmapProperties.saveProperties(m_properties);

	VariantDomPath mindmapImages( document.documentElement(), QLatin1String("mindmap/images/properties"));
	mindmapImages.saveProperties( m_images );


	QProgressDialog progress(tr("Saving mindmap..."), 0, 0, items.count(), QApplication::activeWindow());
	progress.setWindowModality(Qt::WindowModal);

	foreach( QGraphicsItem *item, items)
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
		{
			SxDomUtils::DomPath blockPath( root.toElement(), blockPathTemplate.arg(index));
			SxDomUtils::DomPath connPath( root.toElement(), connPathTemplate.arg(index));
			block->saveBlock( blockPath, connPath );
			index++;
		}
		progress.setValue(index);
		QApplication::processEvents();
	}
	progress.setValue(items.count());

	qDebug() << "Save " << time.elapsed();
	ts << document.toString();
	m_commandStack->setClean();
	return true;
}

void MindMap::initData( )
{
	propertyModel()->setBlock(0);
	clearDocument();
	m_properties.clear();
	m_commandStack->setClean();
	QTimer::singleShot(0, this, SLOT(configureDocument()));

	setupRootBlock(new Block());
	propertyModel()->setBlock(root());
	emit modelChanged(propertyModel());
}

QList< Block * > MindMap::selectedNodes( ) const
{
	QList<Block*> blocks;
	QList<QGraphicsItem *> items = scene()->selectedItems();
	foreach( QGraphicsItem *item, items)
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
		{
			blocks << block;
		}
	}
	return blocks;
}

QList< QByteArray > MindMap::selectedNodeIds( ) const
{
	QList<QByteArray> blocks;
	QList<QGraphicsItem *> items = scene()->selectedItems();
	foreach( QGraphicsItem *item, items)
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
		{
			blocks << block->id();
		}
	}
	return blocks;
}


void MindMap::clearSelection( )
{
	scene()->clearSelection();
}

void MindMap::moveSelection( const QPointF & delta )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	if( nodeIds.count() == 1)
		m_commandStack->push(new MoveCommand(nodeIds[0],delta,this));
	else
		m_commandStack->push(new MoveGroupCommand(nodeIds,delta,this));
}

void MindMap::deleteSelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	if( nodeIds.count() == 1)
		m_commandStack->push(new DeleteBlockCommand(nodeIds[0], this));
	else
		m_commandStack->push(new DeleteGroupCommand(nodeIds, this));
}

void MindMap::selectRootNode( )
{
	clearSelection();
	m_root->setSelected(true);
	itemSelectionChanged();
}

void MindMap::copySelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	m_commandStack->push(new CopyGroupCommand(nodeIds, this));
}

void MindMap::cutSelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	m_commandStack->push(new CutGroupCommand(nodeIds, this));
}

void MindMap::slotCommandStackCleanChanged( bool state )
{
	setModified( !state );
}

void MindMap::createChildOnSelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	m_commandStack->push(new CreateBlockCommand(nodeIds[0],QPoint(),this));
}

void MindMap::exportImage( const QString & exportFile )
{
	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QImage exportImage(scene()->itemsBoundingRect().size().toSize(), QImage::Format_ARGB32_Premultiplied);
	exportImage.fill(0xFFFFFF);
	QPainter painter(&exportImage);
	painter.setRenderHint(QPainter::Antialiasing);
	scene()->render(&painter);
	QApplication::restoreOverrideCursor();

	QFileInfo fileInfo(currentFile());
	exportImage.setText("Description", "Generated by Flo");
	exportImage.setText("Date", QDateTime::currentDateTime().toString() );
	exportImage.setText("Original File", fileInfo.completeBaseName() );

	QFileInfo exportFileInfo( exportFile );
	if( !exportImage.save(exportFile, exportFileInfo.completeSuffix().toUpper().toLatin1().constData() ) )
	{
		QMessageBox::critical(QApplication::activeWindow(), tr("Error saving image..."),tr("The image %1 could not be saved.").arg(exportFile), QMessageBox::Ok, QMessageBox::NoButton);
	}
}

#if QT_VERSION >= 0x040300
void MindMap::exportSVG( const QString & exportFile )
{
	QFile buffer(exportFile);
	if( !buffer.open(QIODevice::WriteOnly) )
	{
		QMessageBox::critical(QApplication::activeWindow(), tr("Error saving image..."), buffer.errorString(), QMessageBox::Ok, QMessageBox::NoButton);
		return;
	}

	QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
	QSvgGenerator svgImage;
	svgImage.setResolution(600);
	svgImage.setSize(scene()->itemsBoundingRect().size().toSize());
	svgImage.setOutputDevice(&buffer);
	QPainter painter(&svgImage);
	painter.setRenderHint(QPainter::Antialiasing);
	scene()->render(&painter);
	QApplication::restoreOverrideCursor();
}
#endif

QVariant MindMap::getProperty( const QString & propertyName, const QVariant &defaultValue ) const
{
	if( m_properties.contains(propertyName) )
		return m_properties[propertyName];
	else
		return defaultValue;
}

void MindMap::setProperty( const QString & propertyName, const QVariant & value )
{
	m_properties[propertyName] = value;
}

void MindMap::selectAllBlocks( )
{
	foreach( QGraphicsItem *item, scene()->items())
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
			block->setSelected( true );
	}
}

void MindMap::configureDocument( )
{
	DocumentOptions doc(QApplication::activeWindow());
	doc.setupGui(this);
	if( doc.exec() == QDialog::Accepted)
	{
		doc.configureMindmap();
		setModified(true);
	}
}

void MindMap::placeChildren()
{
// 	QApplication::setOverrideCursor(Qt::BusyCursor);
// 	qDebug("place children");
// 	root()->placeChildren(-2.0*3.14, 0);
// 	QApplication::restoreOverrideCursor();


	QApplication::setOverrideCursor(Qt::BusyCursor);
	Block *block = root();
	if( block )
	{
		if (block->childCount() != 0)
		{
			int idxmiddle = 0;
			int idx = 0;
			qreal cumulated = 0;
			qreal totalsize = block->recursiveChildHeight();

			qreal bestratio = ( block->childCount() > 0 ) ?  block->recursiveChildHeight():0;
			bestratio = fabs( totalsize - 2.0 * bestratio );

			foreach( Block *child, block->children() )
			{
				cumulated += child->recursiveChildHeight();

				qreal newratio = fabs( totalsize - 2.0 * cumulated);

				if (newratio > bestratio)
				{
					idxmiddle = idx - 1;
					cumulated -= child->recursiveChildHeight();
					break;
				}

				bestratio = newratio;
				idx++;
			}

			qreal sizeleft = cumulated;
			qreal sizeright = totalsize - cumulated;
			qreal nesting = 10.0;
			qreal binspace = 50.0;
			qreal orig = 0.0;

			// process the branches on the left
			orig = block->y() + block->boundingRect().height()/2.0 + nesting/2.0 - sizeleft/2.0;
			for (int i=0; i <= idxmiddle; i++)
			{
				Block* tmpitem = block->children().at(i);
				tmpitem->placeChildren( QPointF(block->x() - binspace - tmpitem->boundingRect().width(), orig), false);
				tmpitem->updateConnections();
				orig += tmpitem->recursiveChildHeight();
			}

			// process the branches on the right
			orig = block->y() + block->boundingRect().height()/2.0 - nesting/2.0 + sizeright/2.0;
			for ( int i = idxmiddle + 1; i < block->childCount(); i++)
			{
				Block* tmpitem = block->children().at(i);
				tmpitem->placeChildren( QPointF( block->x() + binspace + block->boundingRect().width(), orig), true);
				tmpitem->updateConnections();
				orig -= tmpitem->recursiveChildHeight();
			}
		}
	}
	QApplication::restoreOverrideCursor();

}

QImage MindMap::imageAttachment( const QString &name  ) const
{
	return m_images[name].value<QImage>();
}

void MindMap::setImageAttachment( const QString &name, const QImage &value )
{
	m_images[name] = value;
}

QStringList MindMap::imageAttachments() const
{
	return m_images.keys();
}

void MindMap::removeImageAttachment( const QString &name )
{
	m_images.remove(name);
}

void MindMap::arrangeBlocks( )
{
		m_commandStack->push(new PositionItemsCommand( this));
}

void MindMap::colorSelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	m_commandStack->push(new ChangeColorGroupCommand( nodeIds, this));
}

void MindMap::changeFontSelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	m_commandStack->push(new ChangeFontGroupCommand( nodeIds, this));
}

void MindMap::changeShapeSelection( )
{
	QList<QByteArray> nodeIds = selectedNodeIds();
	if( nodeIds.count() == 0)
		return;
	m_commandStack->push(new ChangeShapeGroupCommand( nodeIds, this));

}

QList< QAction * > MindMap::blockActions( ) const
{
	return m_blockActions;
}

void MindMap::setBlockActions( const QList< QAction * > & actions )
{
	m_blockActions = actions;
}

QList< Block * > MindMap::allNodes( ) const
{
	QList<Block*> blocks;
	QList<QGraphicsItem *> items = scene()->items();
	foreach( QGraphicsItem *item, items)
	{
		Block *block = qgraphicsitem_cast<Block*>(item);
		if( block )
		{
			blocks << block;
		}
	}
	return blocks;

}


