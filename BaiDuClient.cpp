#include "BaiDuClient.h"
#pragma execution_character_set("utf-8")
BaiDuClient::BaiDuClient(QObject *parent, QString name, QString ac, QString rc)
	: DiskHandleClient(parent)
{
	isCanUsed = false;
	bb = false;
	BaiDuCurl = NULL;
	BaiDuCurl_Thread = NULL;
	if (rc == "") {
		
	}
	else {
		this->ac = ac;
		this->rc = rc;
		upDateAc();
		Client_Once = new BaiDuClient(parent, name, ac, rc, true);
	}
	

}
BaiDuClient::BaiDuClient(QObject* parent, QString name, QString ac, QString rc,bool b)
	: DiskHandleClient(parent)
{
	bb = b;
	BaiDuCurl = NULL;
	work = false;
	BaiDuCurl_Thread = NULL;
	this->ac = ac;
	this->rc = rc;
	isCanUsed = true;
	start();
}

BaiDuClient::~BaiDuClient()
{
}

void BaiDuClient::UpDateClose() {

}

void BaiDuClient::upDateAc() {
	if (BaiDuCurl == NULL) {
		BaiDuCurl = curl_easy_init();
	}
	char urlc[1024];
	FileStringTools::getChar(tokenUrl + rc + "&client_id=dT3XIFSZU8jK7smucwAuypwe&client_secret=QsrhuBbz3Um5lbdOG9fnQ2XEwQf5iVfq", urlc);
	QString re = "";

	qDebug() << urlc;
	curl_easy_setopt(BaiDuCurl, CURLOPT_URL, urlc);
	curl_easy_setopt(BaiDuCurl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(BaiDuCurl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(BaiDuCurl);
	curl_easy_reset(BaiDuCurl);
	qDebug() << re;
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson((re.split("}")[0] + "}").toLatin1());
		if (json["error"].isUndefined() && json["errno"].isUndefined()) {
			ac = json["access_token"].toString();
			rc = json["refresh_token"].toString();
			isCanUsed = true;
		}
	}
	return;
}


QList<VirtualDisk::fileTree*> BaiDuClient::getFileList_Thread(QString path) {
	if (BaiDuCurl_Thread == NULL) {
		BaiDuCurl_Thread = curl_easy_init();
	}
	char urlc[1024];
	FileStringTools::getChar(fileUrl + ac+(path == "" ? "" : "&dir=/"+ FileStringTools::getPathWithoutDiskName(path)) + "&start=0&limit=10&web=web", urlc);
	
	QString re = "";

	qDebug() << urlc;
	curl_easy_setopt(BaiDuCurl_Thread, CURLOPT_URL, urlc);
	curl_easy_setopt(BaiDuCurl_Thread, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(BaiDuCurl_Thread, CURLOPT_USERAGENT, "pan.baidu.com");
	curl_easy_setopt(BaiDuCurl_Thread, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(BaiDuCurl_Thread, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(BaiDuCurl_Thread);
	curl_easy_reset(BaiDuCurl_Thread);
	qDebug() << re;
	if (ok == 0 && re.trimmed() != "") {
		return reToList(re);
	}
	else {
		return QList<VirtualDisk::fileTree*>();
	}
}

QList<VirtualDisk::fileTree*> BaiDuClient::getFileList(QString path) {
	if (BaiDuCurl == NULL) {
		BaiDuCurl = curl_easy_init();
	}
	char urlc[1024];
	FileStringTools::getChar(fileUrl + ac + (path == "" ? "" : "&dir=/" + FileStringTools::getPathWithoutDiskName(path))+"&start=0&limit=10&web=web", urlc);
	QString re = "";

	qDebug() << urlc;
	curl_easy_setopt(BaiDuCurl, CURLOPT_URL, urlc);
	curl_easy_setopt(BaiDuCurl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(BaiDuCurl, CURLOPT_USERAGENT, "pan.baidu.com");
	curl_easy_setopt(BaiDuCurl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(BaiDuCurl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(BaiDuCurl);
	curl_easy_reset(BaiDuCurl);
	qDebug() << re;
	if (ok == 0 && re.trimmed() != "") {
		return reToList(re);
	}
	else {
		return QList<VirtualDisk::fileTree*>();
	}
}

void BaiDuClient::setLogin(QStringList s) {
	ac = s[3];
	rc = s[4];
	isCanUsed = true;

	ReadDataFile::setLoginData(s);
}


QList<VirtualDisk::fileTree*> BaiDuClient::reToList(QString re) {
	QList<VirtualDisk::fileTree*> lf;
	int d = 0;
	int d_ = 0;
	QString s = "";
    for (QChar c : re) {
		if (c == '{' && d_ == 0) {
			d++;
		}
		else if (c == '}' && d_ == 0){
			d--;
		}
		else if (c == "\"" && d_ == 0){
			d_ = 1;
		}
		else if (c == "\"" && d_ == 1) {
			d_ = 0;
		}
		s.append(c);
		if (d == 0) {
			break;
		}
	}
	qDebug() << s;

	//ss.replace("\\/", "/");
	QJsonDocument json = QJsonDocument::fromJson(s.toUtf8());
	if (json["errno"].toInt() == 0) {
		QJsonArray l = json["list"].toArray();
        for (QJsonValue v : l) {
			QJsonObject o = v.toObject();
			VirtualDisk::fileTree* f = new VirtualDisk::fileTree();
			f->name = o["server_filename"].toString();
			f->type = o["isdir"].toInt() == 0 ? TXT : DIR;
			if (f->type == TXT) {
				f->size = o["size"].toInt();
				f->downloadMessage = QString::number(o["fs_id"].toVariant().toULongLong());
			}
			else {
				f->size = 0;
			}
			f->list = NULL;
			f->parent = NULL;
			lf.append(f);
			
		}
	}
	return lf;
}

QString BaiDuClient::getAc() {
	return ac;
}
