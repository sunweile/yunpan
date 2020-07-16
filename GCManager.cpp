#include "GCManager.h"
#pragma execution_character_set("utf-8")
GCManager::GCManager(QObject *parent)
	: QObject(parent)
{
	t = new QTimer(this);
	connect(t, SIGNAL(timeout()), this, SLOT(gcfile()));
	t->start(60000*60*6);
}

GCManager::~GCManager()
{
}

void GCManager::gcfile() {
	for each (VirtualDisk::fileTree * f in deleteFileList_) {
		f->deleteSelf();
	}
	deleteFileList_ = deleteFileList;
}