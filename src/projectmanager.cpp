#include "projectmanager.h"
#include "newproject.h"
#include "newfile.h"
#include <QtGui>
#include <QWidget>
#include "textroom.h"

ProjectManager::ProjectManager(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	newProject = new NewProject(this);
	newFile = new NewFile(this);
	readProjects();
	readFiles();
	readStats();
	connect(ui.newProjectButton, SIGNAL( clicked() ), this, SLOT( addProject() ) );
	connect(ui.removeProjectButton, SIGNAL( clicked() ), this, SLOT( removeProject() ) );
	connect(ui.listWidget, SIGNAL( currentRowChanged(int) ), this, SLOT( readFiles() ) );
	connect(ui.fileListWidget, SIGNAL( currentRowChanged(int) ), this, SLOT( readStats() ) );
	connect(ui.newFileButton, SIGNAL( clicked() ), this, SLOT( addNewFile() ) );
	connect(ui.removeFileButton, SIGNAL( clicked() ), this, SLOT( removeFile() ) ); 
	connect(ui.openFileButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

void ProjectManager::addProject()
{
	QString projectName = newProject->createNewProject(this);
	new QListWidgetItem(projectName, ui.listWidget); 
	writeProjects();
}

void ProjectManager::removeProject()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	QMessageBox::StandardButton ret;
	int currRow = ui.listWidget->currentRow();
	QString currentproject;
	currentproject.setNum(currRow);
	QString lastproject;
	lastproject.setNum(ui.listWidget->count());
	ret = QMessageBox::warning(this, tr("Project Manager"), tr("Are you sure you want to remove\n" "this project. It is undoable."), 
										QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		for (int i = currRow; i != ui.listWidget->count(); ++i)
		{
			QString currentproject;
			currentproject.setNum(i);
			QString nextproject;
			nextproject.setNum(i+1);
			settings.setValue("ProjectManager/Files" + currentproject, settings.value("ProjectManager/Files" + nextproject));
		}
		settings.remove("ProjectManager/Files" + lastproject);
		ui.listWidget->takeItem(currRow);
		writeProjects();
	}
}

void ProjectManager::readProjects()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	projectstotal = settings.value("ProjectManager/Projects", "New Project").toString();
	if (projectstotal != "")
	{
		projects = projectstotal.split("; ", QString::KeepEmptyParts);
			for (int i = 0; i != projects.count(); ++i)
			{
			new QListWidgetItem(projects[i], ui.listWidget); 
			}
		ui.listWidget->setCurrentRow(0);
	}
}

void ProjectManager::writeProjects()
{
		#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	QString projectstotalwrite = "";
	QString filestotalwrite = "";
	for (int i = 0; i != ui.listWidget->count(); ++i)
	{
		projectstotalwrite = projectstotalwrite + ui.listWidget->item(i)->text();
		projectstotalwrite = projectstotalwrite + "; ";
	}
	settings.setValue("ProjectManager/Projects", projectstotalwrite);
	writeFiles();
}

void ProjectManager::writeFiles()
{
		#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	int currRow = ui.listWidget->currentRow();
	QString currentproject;
	currentproject.setNum(currRow);
	QString filewrite = "";
	for (int i = 0; i != ui.fileListWidget->count(); ++i)
	{
		filewrite = filewrite + ui.fileListWidget->item(i)->text();
		filewrite = filewrite + " + "; 
	}
	settings.setValue("ProjectManager/Files" + currentproject, filewrite);
}

void ProjectManager::readFiles()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	int currRow = ui.listWidget->currentRow();
	QString currentproject;
	currentproject.setNum(currRow);
	ui.fileListWidget->clear();
	filestotal = settings.value("ProjectManager/Files" + currentproject, "New File").toString();
		files = filestotal.split(" + ", QString::KeepEmptyParts);
		for (int i = 0; i != files.count(); ++i)
			{
				new QListWidgetItem(files[i], ui.fileListWidget); 
			}
	ui.fileListWidget->setCurrentRow(0);
}

void ProjectManager::addNewFile()
{
	QString fileName = newFile->createNewFile(this);
	new QListWidgetItem(fileName, ui.fileListWidget); 
	writeFiles();
}

void ProjectManager::removeFile()
{
#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	QMessageBox::StandardButton ret;
	ret = QMessageBox::warning(this, tr("Project Manager"), tr("Are you sure you want to remove\n" "this file. It is undoable."), 
										QMessageBox::Yes | QMessageBox::No);
	if (ret == QMessageBox::Yes)
	{
		int currRow = ui.fileListWidget->currentRow();
		QString currentfile;
		currentfile.setNum(currRow);
		settings.remove("ProjectManager/Stats" + currentfile);
		ui.fileListWidget->takeItem(currRow);
		writeFiles();
	}
}

void ProjectManager::readStats()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	int currRow = ui.fileListWidget->currentRow();
	QString currentfile;
	currentfile.setNum(currRow);
	QString currentfilename = ui.fileListWidget->currentItem()->text();
	ui.propertyListWidget->clear();
	propertiestotal = settings.value("ProjectManager/Stats" + currentfile,  "Unsaved + 0 +  ").toString();
	properties = propertiestotal.split(" + ", QString::KeepEmptyParts);
	new QListWidgetItem("File: " + properties[0], ui.propertyListWidget); 
	new QListWidgetItem("Word Count: " + properties[1], ui.propertyListWidget); 
	new QListWidgetItem("Notes: " + properties[2], ui.propertyListWidget);
}

QString ProjectManager::getFile(QWidget *parent)
{
	ProjectManager *projectmanager = new ProjectManager(parent);
	projectmanager->setModal(true);
	QString file;
	if (projectmanager->exec() == QDialog::Accepted)
	{
		file = projectmanager->fileListWidget->currentItem()->text();
	}
	return file;
}

