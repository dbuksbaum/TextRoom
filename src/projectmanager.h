#ifndef __PROJECTMANAGER_H__
#define __PROJECTMANAGER_H__

#include <QtGui>
#include <QWidget>

#include "ui_projectmanager.h"

class TextRoom;
class NewProject;

class ProjectManager: public QDialog, public Ui::ProjectManager
{
	Q_OBJECT
	
public:
	ProjectManager(QWidget *parent = 0);
	QString openFile(QWidget *parent = 0);

private:
	Ui::ProjectManager ui;
	NewProject *newProject;
	TextRoom *textRoom;
	void readProjects();
	void writeProjects();
	void readPaths();
	void writePaths();
	void writeFiles();
	QString projectstotal;
	QStringList projects;
	QString filestotal;
	QStringList fileswithpaths;
	QStringList strippedFileName;
	QString pathstotal;
	QStringList paths;
	QString filename;
	
private slots:
	void addProject();
	void removeProject();
	void readFiles();
	void addFile();
	void removeFile();
};

#endif


