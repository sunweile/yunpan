#include "UserHandle.h"
#pragma execution_character_set("utf-8")

int UserHandle::FileLen() {
	return vd->getFiles(workDir)->size;
}

VirtualDisk::fileTree* UserHandle::getFiles() {
	return vd->getFiles(workDir);
}

VirtualDisk::fileTree* UserHandle::getFiles(QString p) {
	return vd->getFiles(p);
}

void UserHandle::open(QString s) {
	workDir = s;
	vd->upDatePath(s);
}
QString UserHandle::getWorkDir() {
	return workDir;
}
bool UserHandle::upDate() {
	if (vd->getType() == DISK) {
		//return vd->upDatePath(workDir);
	}
	return false;
}

void UserHandle::setVd(VirtualDisk* s) {
	vd = s;
}

VirtualDisk* UserHandle::getVd() {
	return vd;
}

void UserHandle::rename(QString& path, QString& name) {
	vd->getFiles(path)->name = name;
	QFile::rename(path, workDir + "/" + name);
}
void UserHandle::copy(QString& files, QString& path) {
	QFile::copy(files, path);
}
void UserHandle::move(QString& files, QString& path) {
	QFile::rename(files, path);
}

QList<VirtualDisk::fileTree*>* UserHandle::search(QString& name) {
	if (work != NULL) {
		work->setStop();
	}
	QList<VirtualDisk::fileTree*>* fl = new QList<VirtualDisk::fileTree*>();
	work = new SearchWork(fl, getFiles(), name);
	return fl;
}

void UserHandle::notSearch() {
	if (work != NULL) {
		work->setStop();
	}
}

SearchWork::SearchWork(QList<VirtualDisk::fileTree*>* l, VirtualDisk::fileTree* f, QString n) {
	list = l;
	file = f;
	name = n;
	isStop = false;
	f->isSame = true;
	start();
}

void SearchWork::run() {
	if (file == NULL) { delete list; return; }
	search(file, name);
	while (!isStop) {
		sleep(1000);
	}
	file->deleteSelf();
	delete list;
}
void SearchWork::setStop() {
	isStop = true;
}

void SearchWork::search(VirtualDisk::fileTree* f, QString n) {
	QList<VirtualDisk::fileTree*> l;
	if (f == NULL || f->type != DIR || isStop) { return; }
	for (int i = 0; i < f->size; i++) {
		if (f->list[i]->name.contains(n)) {
			list->append(f->list[i]);
		}
		if (f->list[i]->type == DIR){
			l.append(f->list[i]);
		}
	}
	for each (VirtualDisk::fileTree * fv in l) {
		search(fv, n);
	}
	return;
}
