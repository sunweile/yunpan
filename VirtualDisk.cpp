#include "VirtualDisk.h"

#include "FtpClient.h"
#include "DiskClient.h"
#include "BaiDuClient.h"
#include "JianGuoClient.h"
#pragma execution_character_set("utf-8")

VirtualDisk::VirtualDisk():QThread(NULL){
	name = "D:";
	//类型  0自定义私有云，1百度，2阿里，。。
	type = DISK;
	files = new fileTree();
	files->list = NULL;
	files->size = 0;
	files->name = "D:";
	diskName = "D:/";
	start();
	upDate();
	/*
	if (type = FTP) {
		dhc = new FtpClient(this);
	}
	dhc->start();
	*/
}
VirtualDisk::VirtualDisk(yunType t, QString n) :QThread(NULL) {
	name = n;
	type = t;
	files = new fileTree();
	files->list = NULL;
	files->size = 0;
	files->name = n;
	diskName = n+"/";
	dhc = NULL;

	if (type == DISK) {
		dhc = new DiskClient(this, n);
	}
	upDate();
	dhc->start();
	start();


}


VirtualDisk::VirtualDisk(yunType y, QString n, QString u, QString p, QString ur, QString pa) :QThread(NULL) {
	name = u;
	type = y;
	files = new fileTree();
	files->list = NULL;
	files->size = 0;
	files->name = u;
	diskName = n;
	
	if (type == FTP) {
		dhc = new FtpClient(this,u,p,ur,pa);
	}
	upDate();
	dhc->start();
	start();

}

VirtualDisk::VirtualDisk(yunType y, QString n, QString u, QString ac, QString rc) :QThread(NULL) {
	name = n;
	type = y;
	files = new fileTree();
	files->list = NULL;
	files->size = 0;
	files->name = "";
	diskName = n;

	if (type == BAI_DU) {
		dhc = new BaiDuClient(this, u, ac, rc);
	}
	upDate();
	dhc->start();
	start();

}

VirtualDisk::VirtualDisk(yunType y, QString n, QString u, QString p) :QThread(NULL) {
	name = n;
	type = y;
	files = new fileTree();
	files->list = NULL;
	files->size = 0;
	files->name = "";
	diskName = n;

	if (type == JIAN_GUO) {
		dhc = new JianGuoClient(this, u, p);
	}
	upDate();
	dhc->start();
	start();

}

VirtualDisk::~VirtualDisk() {

}

QString VirtualDisk::getName() {
	return name;
}
QString VirtualDisk::getDiskName() {
	return diskName;
}

QString VirtualDisk::getBz() {
	return bz;
}

int VirtualDisk::getType() {
	return type;
}

QString VirtualDisk::getWorkPath() {
	return workPath;
}

void VirtualDisk::upDate() {
	//if (type == DISK) {
	//	upDateDisk();
	//}
}
void VirtualDisk::upDateDisk() {
	upDateDiskWithPath(diskName,files,2);
}
bool VirtualDisk::upDatePath(QString path) {
	if (!path.contains("/")) { path = path + "/"; }
	if (path.contains("://")) {
		path = path.replace("://", "+:kk:+");
		QStringList pathl = path.split("/");
		pathl.removeFirst();
		path = "";
		for each (QString s in pathl)
		{
			path += "/" + s;
		}
	}
	VirtualDisk::fileTree* f = getFiles(path);
	dhc->upDateOnceWork(f, path);
	return false;
}
bool VirtualDisk::upDatePath_(QString path) {
	if (!path.contains("/")) { path = path + "/"; }
	if (path.contains("://")) {
		path = path.replace("://", "+:kk:+");
		QStringList pathl = path.split("/");
		pathl.removeFirst();
		path = "";
		for each (QString s in pathl)
		{
			path += "/" + s;
		}
	}
	VirtualDisk::fileTree* f = getFiles(path);
	dhc->upDateOnce(f, path);
	return false;
}
void VirtualDisk::run() {
	while (true) {
		if (dhc != NULL) {
			files = dhc->getFile();
		}
		msleep(100);
		/*
		filesBf->list = NULL;
		filesBf->size = 0;
		filesBf->name = "D:";
		upDateDiskWithPath(diskName, filesBf, -1);
		fileTree* tmp = files;
		files = filesBf;
		filesBf = new fileTree();
		clean(tmp);*/
	}
}
bool VirtualDisk::upDateDiskWithPath(QString& path, fileTree* files,int dd) {
	bool kb = true;
	if (dd == 0) { return true; }
	dd--;
	QDir dir(path);
	if (!dir.exists()) { return true; }
	QFileInfoList list_ = dir.entryInfoList();
	QFileInfoList list;
	for each (QFileInfo e in list_)
	{
		if (e.fileName() != ".." && e.fileName() != ".") {
			list.append(e);
		}
	}
	QFileInfoList sls;
	if (files != NULL) {
		for (int i = 0; i < list.size(); i++) {
			int b = false;
			for (int j = 0; j < files->size; j++) {
				if (list.at(i).fileName() == files->list[j]->name) {
					b = true;
					break;
				}
			}
			if (!b) {
				if (!sls.contains(list.at(i))) {
					sls.append(list.at(i));
				}
			}
		}
		for (int j = 0; j < files->size; j++) {
			bool b = false;
			for (int i = 0; i < list.size(); i++) {
				if (list.at(i).fileName() == files->list[j]->name) {
					b = true;
					break;
				}
			}
			if (!b) {
				clean(files->list[j]);
				files->list[j] = NULL;
			}
		}
	}
	fileTree** fts = new fileTree*[list.size()];
	int j = 0;
	if (files == NULL || files->list == NULL) { j = -1; }
	for (int i = 0; i < list.size() || i < files->size; i++) {
		if (j >= 0) {
			if (j == files->size) {
				j = -1;
			}
		}
		if (j >= 0 && files->list != NULL) {
			QDir dir1(getNetPath(files->list[j]));
			if (files->list[j] != NULL && dir1.exists()) {
				fts[i] = files->list[j];
				if (fts[i]->type == DIR) {
					upDateDiskWithPath(getNetPath(fts[i]), fts[i], dd);
				}
				
			}
			else {
				kb = false;
				i--;
			}
			j++;
		}else if ((-j-1) < sls.size()){
			kb = false;
			fts[i] = new fileTree();
			fts[i]->name = sls.at(-j-1).fileName();
			fts[i]->parent = files;
			fts[i]->date = sls.at(-j - 1).metadataChangeTime().toString("yyyy/M/d h:m");

			if (sls.at(-j-1).isDir()) {
				fts[i]->type = DIR;
				fts[i]->size = 0;
				upDateDiskWithPath(sls.at(-j-1).filePath(), fts[i], dd);
			}else {
				fts[i]->type = TXT;
				fts[i]->size = sls.at(-j-1).size();
			}
			j--;
		}
	}
	delete[] (files->list);
	files->size = list.size();
	files->list = fts;
	return kb;
}

void VirtualDisk::clean(fileTree* file) {
	if (file->isSearch) { return; }
	if (file->list != NULL) {
		for (int i = 0; i < file->size; i++) {
			clean(file->list[i]);
		}
	}
	delete file;
}
QString VirtualDisk::getTypeName() {
	switch (type){
		case DISK:
			return "Disk";
		case FTP:
			return "Ftp";
		case SMB:
			return "SMB";
		case SEA_FILE:
			return "SeaFile";
		case BAI_DU:
			return "BAIDU";
		case _360:
			return "360";
		case TENG_XUN:
			return "TENGXUN";
		case _115:
			return "115";
		case JIAN_GUO:
			return "JIANGUO";
	}
}

VirtualDisk::fileTree* VirtualDisk::getFiles() {
	if (dhc != NULL) {
		while (true) {
			VirtualDisk::fileTree* files_ = dhc->getFile();
			if (files_ != NULL) {
				files = files_;
				files->name = name;
				break;
			}
			else {
				if (files == NULL) {
					files = new VirtualDisk::fileTree();
					files->name = name;
					files->list = NULL;
					files->size = 0;
				}
				break;
			}
		}
	}
	return files;
}

VirtualDisk::fileTree* VirtualDisk::getFiles(VirtualDisk::fileTree* file, QString& path) {
	VirtualDisk::fileTree* f = file;
	if (f == NULL) { return NULL; }
	if (path == f->name) { return f; }
	QStringList list = path.replace("://","+:kk:+").split("/");
	for (int i = 1; i < list.size(); i++) {
		QString n = list.at(i);
		n = n.replace("+:kk:+", "://");
		if (n.isEmpty()) { continue; }
		int j = 0;
		while (j < f->size) {
			if (n == f->list[j]->name) {
				f = f->list[j];
				j = -1;
				break;
			}
			j++;
		}
		if (j != -1) {
			return NULL;
		}
	}
	return f;
}

VirtualDisk::fileTree* VirtualDisk::getFiles(QString& path) {
	return getFiles(getFiles(), path);
}

VirtualDisk::fileTree* VirtualDisk::getFiles( QString& dir,  QString& path) {
	return getFiles(getFiles(dir), path);
}

bool VirtualDisk::isSame(VirtualDisk::fileTree* file) {
	if (getLastTime(file) == getLastTimeWithLocalPath(getLoaclPath(file))) {
		return true;
	}
	return false;
}

bool VirtualDisk::isSame(QString& path) {
	VirtualDisk::fileTree* f = getFiles(path);
	if (getLastTime(f) == getLastTimeWithLocalPath(getLoaclPath(f))) {
		return true;
	}
	return false;
}

bool VirtualDisk::isSame(QString& dir, QString& path) {
	VirtualDisk::fileTree* f = getFiles(dir, path);
	if (getLastTime(f) == getLastTimeWithLocalPath(getLoaclPath(f))) {
		return true;
	}
	return false;
}
QString VirtualDisk::getLastTime(VirtualDisk::fileTree* file) {
	if (file == NULL) { return ""; }
	return file->date;
}

QString VirtualDisk::getLastTime(QString& path) {
	VirtualDisk::fileTree* f = getFiles(path);
	if (f == NULL) { return ""; }
	return f->date;
}

QString VirtualDisk::getLastTime(QString& dir, QString& path) {
	VirtualDisk::fileTree* f = getFiles(dir, path);
	if (f == NULL) { return ""; }
	return f->date;
}

QString VirtualDisk::getLastTimeWithLocalPath(QString& path) {
	if (path.isEmpty()) { return ""; }
	QFileInfo file(path);
	return file.lastModified().toString("yyyy_MM_dd_hh_mm_ss");
}

QString VirtualDisk::getLoaclPath(QString& dir, QString& path) {
	VirtualDisk::fileTree* f = getFiles(dir, path);
	return getLoaclPath(f);
}

QString VirtualDisk::getLoaclPath(QString& path) {
	VirtualDisk::fileTree* f = getFiles(path);
	return getLoaclPath(f);
}

QString VirtualDisk::getLoaclPath(VirtualDisk::fileTree* file) {
	QString path = file->path;
	if (path == "defeat") {
		QString wp = getWorkPath();
		wp += getNetPath(file);
		return wp;
	}
	QStringList list = path.split("/");
	VirtualDisk::fileTree* f = file;
	for (int i = 0; i < list.size(); i++) {
		if (list.at(i) == ".") {
		}else if (list.at(i) == "..") {
			f = getParentDir(f);
		}else {
			break;
		}
	}
	return getLoaclPath(f)+"/"+path;
}

QString VirtualDisk::getNetPath(VirtualDisk::fileTree* file) {
	QString path = "";
	for (VirtualDisk::fileTree* f = file; f != NULL; f = getParentDir(f)) {
		path == f->name + "/" + path;
	}
	return path;
}

VirtualDisk::fileTree* VirtualDisk::getParentDir(VirtualDisk::fileTree* file) {
	return file->parent;
}

long long VirtualDisk::getFileSize(QString& path) {
	VirtualDisk::fileTree* f = getFiles(path);
	return getFileSize(f);
}

long long VirtualDisk::getFileSize( QString& dir,  QString& path) {
	VirtualDisk::fileTree* f = getFiles(dir, path);
	return getFileSize(f);
}

long long VirtualDisk::getFileSize(VirtualDisk::fileTree* file) {
	return file->size;
}

QStringList* VirtualDisk::getDir(QString dir) {
	VirtualDisk::fileTree* f = getFiles(dir);
	if (f == NULL || f->type != DIR) { return NULL; }
	QStringList* sl = NULL;
	for (int i = 0; i < f->size; i++) {
		if (f->list[i]->type == DIR) {
			if (sl == NULL) {
				sl = new QStringList();
			}
			sl->append(f->list[i]->name);
		}
	}
	return sl == NULL ? new QStringList() : sl;
}

QString VirtualDisk::fileTree::getNetPath() {
	QString s = "";
	VirtualDisk::fileTree* f = this;
	while (f != NULL) {
		s = f->name + (s == "" ? "" : "/") + s;
		f = f->parent;
	}
	return s;
}
VirtualDisk::fileTree::fileTree() {
	isSearch = false;
	downloadMessage = "";
	name = "";
	type = DIR;
	size = 0;
	date = "";
	isSame = false;
	isLocal = false;
	path = "";
	list = NULL;
	parent = NULL;
}

bool VirtualDisk::fileTree::operator==(VirtualDisk::fileTree* b) {
	if (this->name != b->name) {
		return false;
	}
	if (this->date != b->date) {
		return false;
	}
	if (this->type != b->type) {
		return false;
	}
	return true;
}

bool VirtualDisk::fileTree::operator==(QFileInfo& b) {
	if (this->name != b.fileName()) {
		return false;
	}
	if (this->date != b.birthTime().toString()) {
		return false;
	}
	if (this->type != (int)b.isDir()* this->type) {
		return false;
	}
	return true;
}

void VirtualDisk::fileTree::deleteSelf() {
	if (isSearch) { return; }
	if (type == DIR) {
		for (int i = 0; i < size; i++) {
			this->list[i]->deleteSelf();
		}
	}
	delete[] this->list;
	delete this;
}

void VirtualDisk::fileTree::deleteThis() {
	if (isSearch) { return; }
	delete[] this->list;
	delete this;
}

bool VirtualDisk::canUsed() {
	return dhc->canUsed();
}
void VirtualDisk::setLogin(QStringList s) {
	dhc->setLogin(s);
}

QStringList VirtualDisk::getMessageFromBaiDu() {
	QStringList f;
	f.push_back(((BaiDuClient*)dhc)->getAc());
	return f;
}

QStringList VirtualDisk::getMessageFromJianGuo() {
	QStringList f;
	f.push_back(((JianGuoClient*)dhc)->getUser());
	f.push_back(((JianGuoClient*)dhc)->getPass());
	return f;
}
