#include "projectmanager.h"
#include "newproject.h"
#include <QtGui>
#include <QWidget>
#include "textroom.h"

ProjectManager::ProjectManager(QWidget *parent)
	:QDialog(parent)
{
	ui.setupUi(this);
	newProject = new NewProject(this);
	readProjects();
	readFiles();
	connect(ui.newProjectButton, SIGNAL( clicked() ), this, SLOT( addProject() ) );
	connect(ui.removeProjectButton, SIGNAL( clicked() ), this, SLOT( removeProject() ) );
	connect(ui.listWidget, SIGNAL( currentRowChanged(int) ), this, SLOT( readFiles() ) );
	connect(ui.addFileButton, SIGNAL( clicked() ), this, SLOT( addFile() ) );
	connect(ui.removeFileButton, SIGNAL( clicked() ), this, SLOT( removeFile() ) ); 
	connect(ui.openFileButton, SIGNAL( clicked() ), this, SLOT( accept() ) );
}

void ProjectManager::addProject()
{
	QString projectName = newProject->createNewProject(this);
	new QListWidgetItem(projectName, ui.listWidget); 
	projects << projectName;
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
		projects.removeAt(ui.listWidget->currentRow());
		ui.listWidget->takeItem(ui.listWidget->currentRow());
		writeProjects();
		readFiles();
	}
}

void ProjectManager::readProjects()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	projectstotal = settings.value("ProjectManager/Projects", "").toString();
	if (projectstotal != "")
	{
		projects = projectstotal.split("; ", QString::SkipEmptyParts);
			for (int i = 0; i != projects.count(); ++i)
			{
			new QListWidgetItem(projects[i], ui.listWidget); 
			}
		ui.listWidget->setCurrentRow(0);
	}
	readFiles();
}

void ProjectManager::writeProjects()
{
		#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	QString projectstotalwrite = "";
	projectstotalwrite = projects.join("; ");
	settings.setValue("ProjectManager/Projects", projectstotalwrite);
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
	filestotal = fileswithpaths.join(" + ");
	settings.setValue("ProjectManager/Files" + currentproject, filestotal);
	readFiles();
}

void ProjectManager::readFiles()
{
	#ifdef Q_OS_WIN32
	QSettings settings(QDir::homePath()+"/Application Data/"+qApp->applicationName()+".ini", QSettings::IniFormat);
#else

	QSettings settings;
#endif
	fileswithpaths.clear();
	int currRow = ui.listWidget->currentRow();
	QString currentproject;
	currentproject.setNum(currRow);
	int currFile = ui.fileListWidget->currentRow();
	QString currentfile;
	currentfile.setNum(currFile);
	ui.fileListWidget->clear();
	filestotal = settings.value("ProjectManager/Files" + currentproject, "").toString();
		if (filestotal != "")
		{
			fileswithpaths = filestotal.split(" + ", QString::SkipEmptyParts);
			for (int i = 0; i != fileswithpaths.count(); ++i)
				{
					new QListWidgetItem(QFileInfo(fileswithpaths[i]).fileName(), ui.fileListWidget);
				}
		}

	ui.fileListWidget->setCurrentRow(0);
}

void ProjectManager::addFile()
{
	filename = QFileDialog::getOpenFileName(this, tr("Add File"), QDir::homePath());
	readFiles();
	fileswithpaths << filename;
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
		int currFile = ui.fileListWidget->currentRow();
		fileswithpaths.removeAt(currFile);
		writeFiles();
	}
}

QString ProjectManager::openFile(QWidget *parent)
{
	ProjectManager *pm = new ProjectManager(parent);
	pm->setModal(true);
	QString result;
	if (pm->exec() == QDialog::Accepted)
	{
		result = pm->fileswithpaths[pm->ui.fileListWidget->currentRow()];
	}

	return result;
}

