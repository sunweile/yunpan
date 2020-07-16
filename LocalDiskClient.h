#pragma once

#include <QObject>
#include "DiskHandleClient.h"
#pragma execution_character_set("utf-8")
class LocalDiskClient : public DiskHandleClient
{
	Q_OBJECT

public:
	LocalDiskClient(QObject *parent);
	~LocalDiskClient();

protected:
	QString pf;
	//virtual void UpDateClose();
	//virtual QList<VirtualDisk::fileTree*> getFileList(QString path);
};
