#pragma once

#include "DiskHandleClient.h"
#include "curl/curl.h"
#include "FileStringTools.h"
#pragma execution_character_set("utf-8")
class JianGuoClient : public DiskHandleClient
{
	Q_OBJECT

public:
	JianGuoClient(QObject* parent, QString user, QString pass);
	JianGuoClient(QObject* parent, QString user, QString pass, bool b);
	~JianGuoClient();
	QList<VirtualDisk::fileTree*> reToList(QString);
	QString getUser();
	QString getPass();
protected:

	CURL* JianGuoCurl;
	CURL* JianGuoCurl_Thread;
	QString user;
	QString pass;
	virtual void UpDateClose();
	virtual QList<VirtualDisk::fileTree*> getFileList(QString path);
	virtual QList<VirtualDisk::fileTree*> getFileList_Thread(QString path);
};
