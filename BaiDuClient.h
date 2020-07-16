#pragma once

#include "DiskHandleClient.h"
#include "curl/curl.h"
#include "FileStringTools.h"
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#pragma execution_character_set("utf-8")
class BaiDuClient : public DiskHandleClient
{
	Q_OBJECT

public:
	BaiDuClient(QObject *parent, QString name, QString ac, QString rc);
	BaiDuClient(QObject* parent, QString name, QString ac, QString rc, bool b);
	~BaiDuClient();
	QList<VirtualDisk::fileTree*> reToList(QString);
	QString getAc();
protected:
	CURL* BaiDuCurl;
	CURL* BaiDuCurl_Thread;
	const static QString fileUrl;
	const static QString tokenUrl;
	QString ac;
	QString rc;
	virtual void UpDateClose();
	virtual QList<VirtualDisk::fileTree*> getFileList(QString path);
	virtual QList<VirtualDisk::fileTree*> getFileList_Thread(QString path);

	void upDateAc();
	virtual void setLogin(QStringList);

};
