#include "LoginView.h"
#include "MainWindows.h"
#include <QtWidgets/QApplication>
#include <QFontDatabase>
#include <QTextCodec>
#include "FileStreamView.h"

#include "FileWorker.h"
#include "FtpClient.h"
#include "ReadDataFile.h"

#include "curl/curl.h"
#include "WebView.h"
#include "GCManager.h"
#pragma execution_character_set("utf-8")


QList<VirtualDisk::fileTree*> deleteFileList;
QList<VirtualDisk::fileTree*> deleteFileList_;

QMap<QString, QIcon>* FileButton::IconsMap = new QMap<QString, QIcon>();
const QString BaiDuClient::fileUrl = "https://pan.baidu.com/rest/2.0/xpan/file?method=list&access_token=";
const QString BaiDuClient::tokenUrl = "https://openapi.baidu.com/oauth/2.0/token?grant_type=refresh_token&refresh_token=";
int main(int argc, char *argv[])
{

	
	QApplication a(argc, argv);
	CURL* curl = curl_easy_init();
	QString ac = "121.10faa32424995acb56cdfab70bed47ae.YmNWjXCiw3C7dAqVQyoSoHc14445tE9kxbCjuwe.3JZQNA";
	QString url = "https://pan.baidu.com/rest/2.0/xpan/file?method=filemanager&opera=copy&access_token=" + ac;
	QString post = "async=2&filelist=[{\"path\":\"/shanggu/skse.zip\",\"dest\":\"/shanggu\",\"newname\":\"sgg.zip\",\"ondup\":\"fail\"}]";
	char urlc[1024];
	char postc[1024];
	FileStringTools::getChar(url, urlc);
	FileStringTools::getChar(post, postc);
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postc);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "pan.baidu.com");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	qDebug() << re;

	//FtpClient* ftp = new FtpClient(NULL);

	//QFtp* fp = new QFtp(NULL);
	
	//fe->setNewWork(FileStreamView::COPY, QList<QString>(), "");
	//fe->start();

	QFontDatabase::addApplicationFont("./fonts/msyh.ttf");
	
	//QTextCodec* codec = QTextCodec::codecForName("GB2312");

	//QTextCodec::setCodecForLocale(codec);
	QList<VirtualDisk*>* vdl = ReadDataFile::getList();
	FileStreamView* fsv = new FileStreamView(NULL);
	fsv->hide();
	fsv->setVdl(vdl);
	MainWindows* w = new MainWindows(NULL, fsv, vdl);
	GCManager* gc = new GCManager(NULL);
	w->show();
	
	return a.exec();
	
}



