#pragma once

#include <QThread>
#include "VirtualDisk.h"
#include "ReadDataFile.h"

#pragma execution_character_set("utf-8")
class DiskHandleClient : public QThread
{
	Q_OBJECT
protected:
	VirtualDisk::fileTree* filesBf;

public:
	DiskHandleClient(QObject*parent);
	~DiskHandleClient();
	VirtualDisk::fileTree* getFile();
	void openUpDate();
	void closeUpDate();
	void upDateOnceWork(VirtualDisk::fileTree* file, QString path);
	void upDateOnce(VirtualDisk::fileTree* file, QString path);

	bool canUsed();
	virtual void setLogin(QStringList);
protected:
	bool bb = false;
	bool work = false;
	VirtualDisk::fileTree* work_f;
	QString work_p;
	QString rootPath;
	DiskHandleClient* Client_Once;

	bool isCanUsed;
	void run();
	bool UpDateOpen();
	void UpDateClose();                        ////子类实现，清理files
	bool upDateWithPath(VirtualDisk::fileTree* file, QString path, int l);  ////子类实现，递归更新files
    virtual QList<VirtualDisk::fileTree*> getFileList(QString path);
    virtual QList<VirtualDisk::fileTree*> getFileList_Thread(QString path);
	QString getRoot();
	VirtualDisk::fileTree* files;
	bool lock;
	bool isUpDate;
};
