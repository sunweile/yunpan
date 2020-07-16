#include "FtpClient.h"
#pragma execution_character_set("utf-8")
FtpClient::FtpClient(QObject *parent)
	: DiskHandleClient(parent)
{
	ftpCurl = NULL;
	ftpCurl_Thread = NULL;
	ftpCurl = curl_easy_init();
	this->url = "ftp://127.0.0.1";
	this->port = 21;
	this->user = "2930657262@qq.com";
	this->pass = "09978qwe";
	getFileList_Thread("");
}

FtpClient::FtpClient(QObject* parent, QString url, QString port, QString user, QString pass)
	: DiskHandleClient(parent)
{
	ftpCurl = NULL;
	bb = false;
	ftpCurl_Thread = NULL;
	this->url = url.trimmed();
	this->port = port.toInt();
	this->user = user.trimmed();
	this->pass = pass.trimmed();
	this->isCanUsed = true;
	Client_Once = new FtpClient(parent, url, port, user, pass, true);
}

FtpClient::FtpClient(QObject* parent, QString url, QString port, QString user, QString pass,bool b)
	: DiskHandleClient(parent)
{
	ftpCurl = NULL;
	bb = b;
	work = false;
	ftpCurl_Thread = NULL;
	this->url = url.trimmed();
	this->port = port.toInt();
	this->user = user.trimmed();
	this->pass = pass.trimmed();
	this->isCanUsed = true;
	this->start();
}

FtpClient::~FtpClient() {
	if (ftpCurl != NULL) {
		curl_easy_cleanup(ftpCurl);
	}
}

QList<VirtualDisk::fileTree*> FtpClient::getFileList(QString path) {
	if (ftpCurl == NULL) {
		ftpCurl = curl_easy_init();
	}
	char urlc[1024];
	FileStringTools::getChar(url + path + "/", urlc);

	QString port = QString::number(this->port);
	char portc[6];
	FileStringTools::getChar(port, portc);

	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	QString re = "";

	qDebug() << urlc;
	qDebug() << portc;
	qDebug() << userc;
	qDebug() << passc;
	qDebug() << upc;
	curl_easy_setopt(ftpCurl, CURLOPT_URL, urlc);
	curl_easy_setopt(ftpCurl, CURLOPT_PORT, portc);
	curl_easy_setopt(ftpCurl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(ftpCurl, CURLOPT_CUSTOMREQUEST, "LIST");
	curl_easy_setopt(ftpCurl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(ftpCurl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(ftpCurl);
	curl_easy_reset(ftpCurl);
	qDebug() << re;
	if (ok == 0 && re.trimmed() != "") {
		if (isUnix(re)) {
			return getUnixFileList(re);
		}
		return getMsDosFileList(re);
	}
	else {
		return QList<VirtualDisk::fileTree*>();
	}
}


QList<VirtualDisk::fileTree*> FtpClient::getFileList_Thread(QString path) {
	if (ftpCurl_Thread == NULL) {
		ftpCurl_Thread = curl_easy_init();
	}
	char urlc[1024];
	FileStringTools::getChar(url+path + "/",urlc);

	QString port = QString::number(this->port);
	char portc[6];
	FileStringTools::getChar(port, portc);

	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = {0};
	sprintf(upc,"%s:%s",userc,passc);
	QString re = "";

	qDebug() << urlc;
	qDebug() << portc;
	qDebug() << userc;
	qDebug() << passc;
	qDebug() << upc;
	curl_easy_setopt(ftpCurl_Thread, CURLOPT_URL, urlc);
	curl_easy_setopt(ftpCurl_Thread, CURLOPT_PORT, portc);
	curl_easy_setopt(ftpCurl_Thread, CURLOPT_USERPWD, upc);
	curl_easy_setopt(ftpCurl_Thread, CURLOPT_CUSTOMREQUEST, "LIST");
	curl_easy_setopt(ftpCurl_Thread, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(ftpCurl_Thread, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(ftpCurl_Thread);
	curl_easy_reset(ftpCurl_Thread);
	qDebug() << re;
	if (ok == 0 && re.trimmed() != "") {
		if (isUnix(re)) {
			return getUnixFileList(re);
		}
		return getMsDosFileList(re);
	}
	else {
		return QList<VirtualDisk::fileTree*>();
	}
}


void FtpClient::UpDateClose() {

}

bool FtpClient::isUnix(QString s) {
	if (s.at(0) == 'd' || s.at(0) == '-') {
		return true;
	}
	return false;
}

QList<VirtualDisk::fileTree*> FtpClient::getMsDosFileList(QString s) {
	QList<VirtualDisk::fileTree*> re;
	s = s.replace("\r\n", "\n").replace("\uE466","");
	QStringList s_ = s.split("\n");
	for (int j = 0; j < s_.size()-1; j++) {
		QString s__ = s_.at(j);
		QStringList ls = s__.split(" ");
		QStringList ss;
		for (int i = 0; i < ls.size(); i++) {
			if (ls.at(i) != "") {
				ss.append(ls[i]);
			}
		}
		if (ss.size() < 2) { continue; }
		QString rq = ss.at(0);
		QStringList rql = rq.split("-");
		QString sj = ss.at(1);
		int h = -1;
		int m = 0;
		QChar d = 0;
		QString sj_ = "";
		for (int i = 0; i < sj.size(); i++) {
			QChar c = sj.at(i);
			if (c == 'A') {

			}
			else if (c == 'P') {
				h += 12;
			}
			else if (c == 'M' || c == ':') {
				if (h != -1) {
					if (h > 9) {
						sj_ += "0" + QString::number(h) + "-" + QString::number(m);
					}
					else {
						sj_ += QString::number(h) + "-" + QString::number(m);
					}
				}
			}
			else {
				if (h == -1) {
					if (d == 0) {
						d = c;
					}
					else {
						QString h_ = "";
						h_.append(c).append(d);
						h = h_.toInt();
					}
				}
				else {
					if (d == 0) {
						d = c;
					}
					else {
						QString m_ = "";
						m_.append(c).append(d);
						m = m_.toInt();
					}
				}
			}
		}
		if (sj_ == "") {
			if (h != -1) {
				if (h > 9) {
					sj_ += "0" + QString::number(h) + "-" + QString::number(m);
				}
				else {
					sj_ += QString::number(h) + "-" + QString::number(m);
				}
			}
		}
		QString date = "20" + rql.at(2) + "-" + rql.at(1) + "-" + rql.at(0) + "-" + sj_;
		long long int size = 0;
		QString name = ss.at(3);
		VirtualDisk::fileTree* f = new VirtualDisk::fileTree();
		if (ss.at(2).toUpper() != "<DIR>") {
			size = ss.at(2).toLongLong();
			f->type = TXT;
		}
		else {
			f->type = DIR;
		}
		f->date = date;
		f->list = NULL;
		f->size = size;
		f->name = name;
		f->parent = NULL;
		f->path = "";
		f->isLocal = false;
		f->isSame = false;
		re.append(f);
	}
	return re;
}

QList<VirtualDisk::fileTree*> FtpClient::getUnixFileList(QString s) {

	QList<VirtualDisk::fileTree*> re;
	return re;
}