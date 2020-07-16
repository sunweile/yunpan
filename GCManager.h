#pragma once

#include <QObject>
#include <QTimer>
#include "VirtualDisk.h"
#pragma execution_character_set("utf-8")

class GCManager : public QObject
{
	Q_OBJECT

public:
	GCManager(QObject *parent);
	~GCManager();
private:
	QTimer* t;
public slots:
	void gcfile();
};
