#ifndef __PROJECTMANAGER_H__
#define __PROJECTMANAGER_H__

#include <QtGui>
#include <QWidget>

#include "ui_projectmanager.h"

class TextRoom;
class NewProject;
class NewFile;

class ProjectManager: public QDialog, public Ui::ProjectManager
{
	Q_OBJECT
	
public:
	ProjectManager(QWidget *parent = 0);
	QString getFile(QWidget *parent = 0);

private:
	Ui::ProjectManager ui;
	NewProject *newProject;
	NewFile *newFile;
	ProjectManager *projectmanager;
	void readProjects();
	void writeProjects();
	void writeFiles();
	QString projectstotal;
	QStringList projects;
	QString filestotal;
	QStringList files;
	QString propertiestotal;
	QStringList properties;
	
private slots:
	void addProject();
	void removeProject();
	void readFiles();
	void readStats();
	void addNewFile();
	void removeFile();
};

#endif


