#include "JianGuoClient.h"
#include <QXmlStreamReader>

#pragma execution_character_set("utf-8")
JianGuoClient::JianGuoClient(QObject *parent, QString user, QString pass)
	: DiskHandleClient(parent)
{
	JianGuoCurl = NULL;
	bb = false;
	JianGuoCurl_Thread = NULL;
	this->user = user.trimmed();
	this->pass = pass.trimmed();
	this->isCanUsed = true;
	Client_Once = new JianGuoClient(parent, user, pass, true);

}

JianGuoClient::JianGuoClient(QObject* parent, QString user, QString pass, bool b)
	: DiskHandleClient(parent)
{
	JianGuoCurl = NULL;
	bb = b;
	JianGuoCurl_Thread = NULL;
	this->user = user.trimmed();
	this->pass = pass.trimmed();
	this->isCanUsed = true;
	work = false;
	this->start();
}

JianGuoClient::~JianGuoClient()
{
}

QList<VirtualDisk::fileTree*> JianGuoClient::getFileList_Thread(QString path) {
	if (JianGuoCurl_Thread == NULL) {
		JianGuoCurl_Thread = curl_easy_init();
	}
	char urlc[1024];
	FileStringTools::getChar("https://dav.jianguoyun.com/dav/"+ FileStringTools::getPathWithoutDiskName(path), urlc);
	QString re = "";
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	qDebug() << urlc;
	
	curl_easy_setopt(JianGuoCurl_Thread, CURLOPT_URL, urlc);
	curl_easy_setopt(JianGuoCurl_Thread, CURLOPT_USERPWD, upc);
	curl_easy_setopt(JianGuoCurl_Thread, CURLOPT_CUSTOMREQUEST, "PROPFIND");
	curl_easy_setopt(JianGuoCurl_Thread, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(JianGuoCurl_Thread, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(JianGuoCurl_Thread);
	curl_easy_reset(JianGuoCurl_Thread);
	qDebug() << re;
	if (ok == 0 && re.trimmed() != "") {
		return reToList(re);
	}
	else {
		return QList<VirtualDisk::fileTree*>();
	}
}

QList<VirtualDisk::fileTree*> JianGuoClient::getFileList(QString path) {
	if (JianGuoCurl == NULL) {
		JianGuoCurl = curl_easy_init();
	}
	char urlc[1024];
	qDebug() << path;
	FileStringTools::getChar("https://dav.jianguoyun.com/dav/" + FileStringTools::getPathWithoutDiskName(path), urlc);
	QString re = "";
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	qDebug() << urlc;
	curl_easy_setopt(JianGuoCurl, CURLOPT_URL, urlc);
	curl_easy_setopt(JianGuoCurl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(JianGuoCurl, CURLOPT_CUSTOMREQUEST, "PROPFIND");
	curl_easy_setopt(JianGuoCurl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(JianGuoCurl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(JianGuoCurl);
	curl_easy_reset(JianGuoCurl);
	qDebug() << re;
	if (ok == 0 && re.trimmed() != "") {
		return reToList(re);
	}
	else {
		return QList<VirtualDisk::fileTree*>();
	}
}

QString JianGuoClient::getUser() {
	return user;
}

QString JianGuoClient::getPass() {
	return pass;
}

void JianGuoClient::UpDateClose() {

}

QList<VirtualDisk::fileTree*> JianGuoClient::reToList(QString re) {
	bool b = false;
	VirtualDisk::fileTree* f = NULL;
	QList<VirtualDisk::fileTree*> fl;
	QXmlStreamReader xsr(re);
	while (!xsr.atEnd()) {
		if (xsr.isStartElement() && b) {
			if (xsr.name() == "response") {
				f = new VirtualDisk::fileTree();
			}
			else if (xsr.name() == "getlastmodified"){
				QLocale lo(QLocale::C);
				//Wed, 03 Jun 2020 02:09:04 GMT
				QString da = xsr.readElementText();
				qDebug() << da.split(" GMT")[0].split(", ")[1];
				f->date = lo.toDateTime(da.split(" GMT")[0].split(", ")[1], "dd MMM yyyy hh:mm:ss").toString("yyyy/M/dd hh:mm:ss");
			}
			else if (xsr.name() == "getcontentlength") {
				f->size = xsr.readElementText().toLongLong();
			}
			else if (xsr.name() == "getcontenttype") {
				if (xsr.readElementText() == "httpd/unix-directory") {
					f->type = DIR;
				}
				else {
					f->type = TXT;
				}
			}
			else if (xsr.name() == "displayname") {
				f->name = xsr.readElementText();
			}
		}
		else if (xsr.isEndElement() && xsr.name() == "response") {
			if (!b) {
				b = true;
			}
			else {
				fl.push_back(f);
			}
		}
		xsr.readNext();
	}
	return fl;

}

