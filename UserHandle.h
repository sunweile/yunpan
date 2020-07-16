#pragma once

#include "VirtualDisk.h"
#pragma execution_character_set("utf-8")
class SearchWork : public QThread {
	Q_OBJECT
public:
	SearchWork(QList<VirtualDisk::fileTree*>*, VirtualDisk::fileTree*, QString);
	void run();
	void setStop();
	void search(VirtualDisk::fileTree*, QString);
private:
	bool isStop;
	QString name;
	QList<VirtualDisk::fileTree*>* list;
	VirtualDisk::fileTree* file;

};

class UserHandle {

public:
	QList<VirtualDisk::fileTree*>* search(QString& name);
	void copy(QString& files, QString& path);
	void move(QString& files, QString& path);
	void rename(QString& path, QString& name);
	void remove(QString& path, bool isDelete);
	void newFile(QString& name, QString& type);
	void newDir(QString& name);
	void open(QString s);
	bool upDate();
	int FileLen();
	QString getWorkDir();
	VirtualDisk::fileTree* getFiles();
	VirtualDisk::fileTree* getFiles(QString);
	void setVd(VirtualDisk* s);
	VirtualDisk* getVd();
	void notSearch();
private:
	QString workDir;
	VirtualDisk* vd;
	QStringList chooseList;

	QStringList jpb;//剪切板
	SearchWork* work;
};

