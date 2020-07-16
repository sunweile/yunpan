#pragma once

#include <QString>
#include <QTextCodec>
#pragma execution_character_set("utf-8")
class FileStringTools
{
public:
	static QString getFileType(QString& s);
	static QString getSize(long long s);
	static void getChar(QString s, char* c);
	static size_t getRep(void* ptr, size_t size, size_t nmemb, void* re);
	static size_t setReq(void* ptr, size_t size, size_t nmemb, void* re);
	static void getLocalChar(QString s, char* c);
	static QString getPathWithoutDiskName(QString p);

};

