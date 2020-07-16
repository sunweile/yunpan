#pragma once
#include <QList>
#include "VirtualDisk.h"
#pragma execution_character_set("utf-8")
class ReadDataFile {
public:
	static QList<VirtualDisk*>* getList();
	static VirtualDisk* ReadLine(QString);
	static void setLoginData(QStringList sl);

};

