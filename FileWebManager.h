#pragma once

#include <QThread>
#include <QFile>
#include "curl/curl.h"
#pragma execution_character_set("utf-8")
class FileWebHandle {
public:
	unsigned long long fileSize;
	unsigned long long maxFileSize;
	QDataStream* file;


};

class FileWebManager : public QThread
{
	Q_OBJECT

public:
	FileWebManager(QObject *parent);
	~FileWebManager();
	FileWebHandle* setDownloadWork(QString path, long long size, long long start, QString url);
	FileWebHandle* setDownloadWork(QString path, long long size, long long start, QString url, QString user, QString pass);

	long long getSize();
	void doStop();
	void doRun();
	void doOver();
	bool download();
	bool isSuccess();
	void run();
	void reset();
	static size_t wirtefunc(void* ptr, size_t size, size_t nmemb, void* stream);
	static int progressfunc(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow);
private:
	long long maxSize;
	long long size;
	long long finishsize;
	bool success;
	bool stopping;
	bool stop;
	bool over;
	CURL* curl;
	long long star;
	QString url;
	QString path;
	QString user;
	QString pass;
	bool isDownload;
	FileWebHandle* fh;
};

