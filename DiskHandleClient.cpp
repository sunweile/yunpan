#include "DiskHandleClient.h"
#pragma execution_character_set("utf-8")
DiskHandleClient::DiskHandleClient(QObject *parent)
	: QThread(parent)
{
	isUpDate = true;
	lock = false;
	files = NULL;
	filesBf = NULL;
	isCanUsed = false;
	this->rootPath = "";
	Client_Once = NULL;
}

DiskHandleClient::~DiskHandleClient()
{
}

VirtualDisk::fileTree*  DiskHandleClient::getFile() {
	while (lock) { sleep(100); }
	return files;
}


void DiskHandleClient::openUpDate() {
	if (!isUpDate) {
		isUpDate = true;
		this->run();
	}
}

bool DiskHandleClient::canUsed(){
	return isCanUsed;
}

void DiskHandleClient::closeUpDate() {
	if (isUpDate) {
		isUpDate = false;
	}
}

void DiskHandleClient::run() {
	if (!bb) {
		
		VirtualDisk::fileTree* tmp = NULL;
		while (isUpDate) {
			break;
			if (!isCanUsed) {
				msleep(5000);
				continue;
			}
			if (!UpDateOpen()) {
				lock = true;
				tmp = files;
				files = filesBf;
				filesBf = new VirtualDisk::fileTree();
				filesBf->name = files->name;
				filesBf->size = 0;
				filesBf->list = NULL;
				lock = false;
				if (tmp != NULL) {
					tmp->deleteSelf();
					tmp = NULL;
				}
				msleep(500);
				break;

			}
		}
		if (!isUpDate) {
			UpDateClose();
		}
		
	}
	else {
		while (true) {
			if (!work) {
				msleep(100);
			}
			else {
				upDateOnce(work_f, work_p);
				work = false;
			}
		}
	}
}

void DiskHandleClient::upDateOnceWork(VirtualDisk::fileTree* file, QString path) {
	if (Client_Once != NULL) {
		Client_Once->work = true;
		Client_Once->work_f = file;
		Client_Once->work_p = path;
		if (file->parent == NULL) {
			this->files = file;
		}
	}
	else {
		upDateOnce(file, path);
	}
}

bool DiskHandleClient::UpDateOpen() {
	if (filesBf == NULL) {
		filesBf = new VirtualDisk::fileTree();
		filesBf->size = 0;
		filesBf->list = NULL;

	}
	return upDateWithPath(filesBf, getRoot(),-1);
}

QString DiskHandleClient::getRoot() {
	return rootPath;
}

void DiskHandleClient::UpDateClose() {
	
}

void DiskHandleClient::upDateOnce(VirtualDisk::fileTree* file, QString path) {
	if (file->parent == NULL) {
		this->files = file;
	}
	upDateWithPath(file,path,2);
}

bool DiskHandleClient::upDateWithPath(VirtualDisk::fileTree*  file, QString path, int l) {
	if (l == 0) { return true; }
	bool kd = true;
	QList<VirtualDisk::fileTree*> ls = l < 0 ? getFileList_Thread(path) : getFileList(path);
	if (file != NULL) {
		for (int i = 0; i < ls.size(); i++) {
			VirtualDisk::fileTree* lf = ls.at(i);
			lf->parent = file;
			if (lf->type == DIR) {
				bool b = false;
				for (int j = 0; j < file->size; j++) {
					if (*file->list[j] == lf) {
						lf->list = file->list[j]->list;
						lf->size = file->list[j]->size;
						b = true;
						break;
					}

				}
				if (!b) {
					kd = false;
				}
				if (lf->list == NULL && lf->type == DIR) {
					lf->size = 0;
				}
				upDateWithPath(lf, path + "/" + lf->name, l-1);
			}
		}
		for (int j = 0; j < file->size; j++) {
			bool dd = false;
			for (int i = 0; i < ls.size(); i++) {
				VirtualDisk::fileTree* lf = ls.at(i);
				if (*file->list[j] == lf) {
					dd = true;
					break;
				}
			}
			if (!dd) {
				kd = false;
				if (file->list[j]->type == DIR) {
					deleteFileList.push_back(file->list[j]);
				}
			}
		}
		if (ls.size() != file->size) {
			kd = false;
		}
	}
	auto tmp = file->list;
	file->list = new VirtualDisk::fileTree * [ls.size()];
	for (int i = 0; i < ls.size(); i++) {
		file->list[i] = ls.at(i);
	}
	file->size = ls.size();
	//file->deleteThis();
	delete[] tmp;

	return kd;

}

void DiskHandleClient::setLogin(QStringList s) {
	return;
}
