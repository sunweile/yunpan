#include "FileWebManager.h"
#include "FileStringTools.h"
#include <QFile>
#include <QDataStream>
#pragma execution_character_set("utf-8")
FileWebManager::FileWebManager(QObject *parent)
	: QThread(parent)
{
	fh = NULL;
	reset();
}

FileWebManager::~FileWebManager()
{
}

void FileWebManager::reset() {
	if (fh != NULL) {
		delete fh;
	}
	stop = false;
	stopping = false;
	path = "";
	size = 0;
	fh = NULL;
	star = 0;
	url = "";
	isDownload = false;
	over = false;
}

long long FileWebManager::getSize() {
	return finishsize;
}

void FileWebManager::doStop() {
	stop = true;
}

void FileWebManager::doOver() {
	over = true;
}
void FileWebManager::doRun() {
	stop = false;
}


FileWebHandle* FileWebManager::setDownloadWork(QString path, long long size, long long start, QString url) {
	this->user = "";
	this->pass = "";
	this->success = false;
	this->path = path;
	this->size = size;
	this->fh = new FileWebHandle();
	this->fh->maxFileSize = size;
	this->fh->fileSize = 0;
	QFile f(path);
	if (f.exists()) {
		this->fh->fileSize = f.size();
	}
	this->star = start;
	this->url = url;
	this->isDownload = true;
	this->over = false;
	return fh;
}

FileWebHandle* FileWebManager::setDownloadWork(QString path, long long size, long long start, QString url, QString user, QString pass) {
	this->user = user;
	this->pass = pass;
	this->success = false;
	this->path = path;
	this->size = size;
	this->fh = new FileWebHandle();
	this->fh->maxFileSize = size;
	this->fh->fileSize = 0;
	QFile f(path);
	if (f.exists()) {
		this->fh->fileSize = f.size();
	}
	this->star = start;
	this->url = url;
	this->isDownload = true;
	this->over = false;
	return fh;
}


void FileWebManager::run() {
	while (url == "") {
		msleep(100);
	}
	QFile* f = new QFile(path);
	f->open(QIODevice::WriteOnly | QIODevice::Append);
	if (f->isOpen()) {
		QDataStream* in = new QDataStream(f);
		fh->file = in;
		curl = curl_easy_init();
		while (!download()) {
			msleep(500);
			while (stop) {
				stopping = true;
				msleep(500);
				if (over) {
					break;
				}
			}
			stopping = false;
			if (over) {
				break;
			}
		}
		curl_easy_cleanup(curl);
		//this->fh->file = NULL;
		if (over) {
			//remove(path.toStdString().c_str());
			//return;
			this->success = false;
			f->close();
			return;
		}
		while (fh->fileSize - 1 != size) {
			msleep(500);
			if (over) {
				//remove(path.toStdString().c_str());
				//return;
				this->success = false;
				f->close();
				return;
			}
		}
		this->success = true;
		f->close();
	}
}

bool FileWebManager::download() {
	char range[64] = { 0 };
	if (this->star + fh->fileSize-1 == this->star + this->size) {
		return true;
	}
	sprintf(range, "%ld-%ld", this->star + fh->fileSize, this->star + this->size);
	char urlc[2048] = { 0 };
	FileStringTools::getChar(url, urlc);
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	if (user != "") {
		char userc[256];
		char passc[128];
		FileStringTools::getChar(user, userc);
		FileStringTools::getChar(pass, passc);
		char upc[384] = { 0 };
		sprintf(upc, "%s:%s", userc, passc);
		curl_easy_setopt(curl, CURLOPT_USERPWD, upc);

	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, wirtefunc);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)fh);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
	curl_easy_setopt(curl, CURLOPT_AUTOREFERER, 1L);
	curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, 1L);
	curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, 5L);
	curl_easy_setopt(curl, CURLOPT_RANGE, range);
	curl_easy_setopt(curl, CURLOPT_TIMEOUT, 30);
	curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 1);
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
	curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, progressfunc);
	curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, this);
	CURLcode retcCode = curl_easy_perform(curl);
	if (retcCode == 0) {
		return true;
	}
	else {
		return false;
	}
}

size_t FileWebManager::wirtefunc(void* ptr, size_t size, size_t nmemb, void* stream) {
	((FileWebHandle*)stream)->file->writeRawData((char*)ptr, size * nmemb);
	//fwrite(ptr, size, nmemb, ((FileWebHandle*)stream)->file);
	
	((FileWebHandle*)stream)->fileSize += size * nmemb;
	return size * nmemb;
}

int FileWebManager::progressfunc(void* clientp, curl_off_t dltotal, curl_off_t dlnow, curl_off_t ultotal, curl_off_t ulnow) {
	((FileWebManager*)clientp)->maxSize = dltotal;
	((FileWebManager*)clientp)->finishsize = dlnow;
	if (((FileWebManager*)clientp)->stop) {
		if (!((FileWebManager*)clientp)->stopping) {
			curl_easy_pause(((FileWebManager*)clientp)->curl, CURLPAUSE_ALL);
			((FileWebManager*)clientp)->stopping = true;
		}
		return 1;
	}
	else if (((FileWebManager*)clientp)->stopping){
		curl_easy_pause(((FileWebManager*)clientp)->curl, CURLPAUSE_CONT);
		((FileWebManager*)clientp)->stopping = false;
		return 0;
	}
	return 0;
}

bool FileWebManager::isSuccess() {
	return success;
}