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
#include "asciiexportdialog.h"
#include "ui_asciiexport.h"
#include "mindmap.h"
#include "asciireporter.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

ASCIIExportDialog::ASCIIExportDialog(QWidget *parent)
		: QDialog(parent)
{
	m_reporter = new ASCIIReporter;
	m_ui = new Ui::ASCIIExportDialog();
	m_ui->setupUi(this);
}

ASCIIExportDialog::~ASCIIExportDialog()
{
	delete m_reporter;
	delete m_ui;
}

void ASCIIExportDialog::on_filePath_editingFinished( )
{
	m_filePath = m_ui->filePath->text();
}

void ASCIIExportDialog::on_selectFile_clicked( )
{
	QString fileName = QFileDialog::getSaveFileName(
					QApplication::activeWindow(), tr("Select export file"),
					m_filePath,
					tr("Text (*.txt)"));
	if( !fileName.isEmpty() )
		m_filePath = fileName;
	m_ui->filePath->setText( m_filePath );
}

void ASCIIExportDialog::exportMindmap( MindMap * map )
{
	ASCIIExportDialog dlg( QApplication::activeWindow() );
	dlg.m_mindMap = map;
	dlg.m_ui->filePath->setText( map->getProperty("asciireport.path",
										map->generateFilePath("txt")).toString() );
	dlg.m_ui->tabSize->setValue( map->getProperty("asciireport.tabsize", 5).toInt() );
	dlg.m_ui->pgCols->setValue( map->getProperty("asciireport.pgcols", 80).toInt() );

	dlg.updateReport();
	dlg.exec();

	map->setProperty("asciireport.path", dlg.m_ui->filePath->text());
	map->setProperty("asciireport.tabsize", dlg.m_ui->tabSize->value());
	map->setProperty("asciireport.pgcols", dlg.m_ui->pgCols->value());

	if( dlg.m_filePath.isEmpty() )
		return;

	QFile exportFile( dlg.m_filePath );
	if( exportFile.open(QIODevice::WriteOnly) )
	{
		QTextStream ts(&exportFile);
		ts << dlg.m_reporter->generateReport( map );
	}
	else
	{
		QMessageBox::critical(&dlg, "Error", QString("Could not save file."), QMessageBox::Ok, QMessageBox::NoButton);
	}
	exportFile.close();
}

void ASCIIExportDialog::on_tabSize_valueChanged( int value )
{
	m_reporter->setTabSize(value);
	m_ui->preview->setPlainText( m_reporter->generateReport( m_mindMap ) );
}

void ASCIIExportDialog::on_pgCols_valueChanged( int value )
{
	m_reporter->setPageCols(value);
	m_ui->preview->setPlainText( m_reporter->generateReport( m_mindMap ) );
	m_ui->preview->setLineWrapColumnOrWidth( value );
}

MindMap* ASCIIExportDialog::mindMap() const
{
	return m_mindMap;
}

void ASCIIExportDialog::setMindMap(MindMap* theValue)
{
	m_mindMap = theValue;
}

void ASCIIExportDialog::updateReport( )
{
	m_reporter->setPageCols( m_ui->pgCols->value() );
	m_reporter->setTabSize( m_ui->tabSize->value() );
	m_filePath = m_ui->filePath->text();
	m_ui->preview->setPlainText( m_reporter->generateReport( m_mindMap ) );
}

