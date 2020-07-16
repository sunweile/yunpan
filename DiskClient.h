#pragma once

#include "DiskHandleClient.h"
#pragma execution_character_set("utf-8")
class DiskClient : public DiskHandleClient
{
	Q_OBJECT

public:
	DiskClient(QObject *parent,QString path);
	~DiskClient();
protected:
	virtual void UpDateClose();
	QString getRoot();
	virtual QList<VirtualDisk::fileTree*> getFileList(QString path);
	virtual QList<VirtualDisk::fileTree*> getFileList_Thread(QString path);

};
