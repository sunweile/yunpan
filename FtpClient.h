#pragma once

#include "DiskHandleClient.h"
#include "curl/curl.h"
#include "FileStringTools.h"
#pragma execution_character_set("utf-8")
class FtpClient : public DiskHandleClient
{
	Q_OBJECT

public:
	FtpClient(QObject* parent);
	FtpClient(QObject* , QString, QString, QString, QString);
	FtpClient(QObject* parent, QString url, QString port, QString user, QString pass, bool b);
	~FtpClient();
private:
	QList<VirtualDisk::fileTree*> getMsDosFileList(QString);
	QList<VirtualDisk::fileTree*> getUnixFileList(QString);
	bool isUnix(QString);
protected:
	CURL* ftpCurl;
	CURL* ftpCurl_Thread;
	QString url;
	int port;
	QString user;
	QString pass;
	virtual void UpDateClose();
	virtual QList<VirtualDisk::fileTree*> getFileList(QString path);
	virtual QList<VirtualDisk::fileTree*> getFileList_Thread(QString path);
};
