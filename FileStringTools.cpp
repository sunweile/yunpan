#include "FileStringTools.h"
#include <QUrl>
#include <QDeBug>
#pragma execution_character_set("utf-8")


QString FileStringTools::getFileType(QString& s) {
	s = s.toUpper();
	if (s == "PNG" || s == "JPG" || s == "JPEG" || s == "BMP" || s == "GIF") {
		return s + "图像文件";
	}
	else if (s == "TXT") {
		return "文本文档";
	}
	else if (s == "MP3" || s == "MIDI" || s == "WMA" || s == "VQF" || s == "AMR") {
		return s + "音乐文件";
	}
	else if (s == "AVI" || s == "MOV" || s == "RMVB" || s == "RM" || s == "FLV" || s == "MP4" || s == "3GP") {
		return s + "视频文件";
	}
	return s + "格式文件";
}
QString FileStringTools::getSize(long long s) {

	QString s1 = "字节";
	long long size = s;
	if (size / 1024 != 0) {
		s1 = "KB";
		size = size / 1024;
	}
	if (size / 1024 != 0) {
		s1 = "MB";
		size = size / 1024;
	}
	if (size / 1024 != 0) {
		s1 = "GB";
		size = size / 1024;
	}
	if (size / 1024 != 0) {
		s1 = "TB";
		size = size / 1024;
	}
	return QString::number(size) + s1;
}

void FileStringTools::getChar(QString str,char* c) {
	char* chStr = c;
	QByteArray ba = QUrl(str).toEncoded();
	memset(chStr, 0, ba.length());
	memcpy(chStr, ba.data(), ba.length());
	chStr[ba.length()] = '\0';
}

void FileStringTools::getLocalChar(QString s, char* c) {
	char* chStr = c;
#ifdef WIN32
	QTextCodec* pCodec = QTextCodec::codecForName("gb2312");
	s.replace("/", "\\");
#else
	QTextCodec* pCodec = QTextCodec::codecForName("utf8");
#endif
	QByteArray ba = pCodec->toUnicode(s.toLocal8Bit().data()).toLocal8Bit();
	memset(chStr, 0, ba.length());
	memcpy(chStr, ba.data(), ba.length());
	chStr[ba.length()] = '\0';
}

size_t FileStringTools::getRep(void* ptr, size_t size, size_t nmemb, void* re) {
	char* ch = (char*)malloc(size * nmemb);
	memset(ch, 0, size * nmemb);
	memcpy(ch, ptr, size * nmemb);
	QTextCodec* pCodec = QTextCodec::codecForName("utf8");
	QString str = pCodec->toUnicode(ch);
	((QString*)re)->append(str.split("�")[0]);
	qDebug() << str;
	qDebug() << size;
	qDebug() << nmemb;
	free(ch);
	return size * nmemb;
}

size_t FileStringTools::setReq(void* ptr, size_t size, size_t nmemb, void* re) {


	return nmemb * size;
}

QString FileStringTools::getPathWithoutDiskName(QString p) {
	QStringList sl = p.replace("://", "+:kk:+").replace("//","/").split("/");
	QString r = sl[1].replace("+:kk:+", "://");;
	for (int i = 2; i < sl.size(); i++) {
		r += "/" + sl[i].replace("+:kk:+", "://");

	}
	return r;
}