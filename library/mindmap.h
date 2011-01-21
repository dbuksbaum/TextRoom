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
#ifndef MINDMAP_H
#define MINDMAP_H

#include <sxfile.h>

#include <QPointF>
#include <QSizeF>
#include <QPointer>
#include <QHash>
#include <QVariant>
#include <QPrinter>
#include <QImage>

class QGraphicsScene;
class BlockPropertyModel;
class Block;
class QUndoStack;
class BlockPropertyModel;
class QDomDocument;

/**
This is the mind map data file.  This will handle the undo/redo operations for the data file, and will provide a way to detect if the document has been modfied.

	@author Ian Reinhart Geiser <geiseri@yahoo.com>
*/
class MindMap : public SxFile
{
	Q_OBJECT
public:
	MindMap( QObject *parent = 0);
	~MindMap();
	void clearDocument();
	void recalculateUUIDs();
	void deleteNode( Block *block );
	void cutNode( Block *block );
	void copyNode( Block *block );
	void pasteNode( Block *block );
	Block *resolveNodeByID( const QByteArray &id );
	Block *resolveNodeByPath( const QByteArray &path );
	QGraphicsScene* scene() const;
	Block* root() const;
	void setRoot( Block *node );
	void setupRootBlock( Block *block);
	BlockPropertyModel* propertyModel() const;
	QAction *undoAction();
	QAction *redoAction();

	QList<QAction*> blockActions( ) const;
	void setBlockActions( const QList<QAction*> &actions );

	QUndoStack* commandStack() const;

	Block *selectedNode() const;
	QList<Block*> selectedNodes() const;
	QList<Block*> allNodes() const;
	QList< QByteArray > selectedNodeIds( ) const;

	void exportImage( const QString &exportFile );
#if QT_VERSION >= 0x040300
	void exportSVG( const QString &exportFile  );
#endif

  void placeChildren( );

signals:
	void maxIndex(int idx);
	void modelChanged( BlockPropertyModel *model);

public slots:
	void slotReparentBlocks( Block *newParent, Block *child);
	void createNode( Block *parentNode, const QPointF &pos );
	void selectRootNode();
	void itemSelectionChanged( );
	void clearSelection( );
	void moveItem( Block *node, const QPointF &delta );
	void moveSelection( const QPointF &delta );
	void deleteSelection( );
	void copySelection( );
	void cutSelection( );
	void colorSelection( );
	void changeFontSelection( );
	void changeShapeSelection( );
	void arrangeBlocks();
	void selectAllBlocks();
	void createChildOnSelection();
	void slotCommandStackCleanChanged( bool state);
	void configureDocument( );

public:
	QVariant getProperty( const QString &propertyName, const QVariant &defaultValue = QVariant() ) const;
	void setProperty( const QString &propertyName, const QVariant &value );

	QImage imageAttachment( const QString &name  ) const;
	void setImageAttachment( const QString &name, const QImage &value );
	void removeImageAttachment( const QString &name );
	QStringList imageAttachments() const;

protected:
	virtual bool loadData( QIODevice *iodevice );
	virtual bool saveData( QIODevice *iodevice );
	virtual void initData( );

private:
	QGraphicsScene *m_scene;
	Block *m_root;
	QUndoStack *m_commandStack;
	BlockPropertyModel *m_propertyModel;
	QHash<QString,QVariant> m_properties;
	QHash<QString,QVariant> m_images;
	QList<QAction*> m_blockActions;
};

#endif
