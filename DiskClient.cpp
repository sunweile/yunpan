#include "DiskClient.h"
#pragma execution_character_set("utf-8")
DiskClient::DiskClient(QObject *parent, QString path)
	: DiskHandleClient(parent)
{
	this->rootPath = path;
	isCanUsed = true;
}

DiskClient::~DiskClient()
{
}
void DiskClient::UpDateClose() {

}
QString DiskClient::getRoot() {
	return rootPath;
}

QList<VirtualDisk::fileTree*> DiskClient::getFileList_Thread(QString s) {
	return getFileList(s);
}

QList<VirtualDisk::fileTree*> DiskClient::getFileList(QString s) {
	if (!s.contains("/")) { s = s + "/"; }
	QDir dir(s);
	QList<VirtualDisk::fileTree*> l;
	if (!dir.exists()) { return l; }
	QFileInfoList list_ = dir.entryInfoList();
	for each (QFileInfo f in list_){
		if (f.fileName() == "." || f.fileName() == "..") { continue; }
		VirtualDisk::fileTree* f_ = new VirtualDisk::fileTree();
		f_->name = f.fileName();
		f_->parent = NULL;
		f_->date = f.metadataChangeTime().toString("yyyy/M/d h:m");
		if (f.isDir()) {
			f_->type = DIR;
			f_->list = NULL;
			f_->size = 0;
		}
		else {
			f_->type = TXT;
			f_->list = NULL;
			f_->size = f.size();
		}
		l.append(f_);
	}
	return l;
}