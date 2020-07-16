#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QByteArray>
#include <QCryptographicHash>
#include "FileWorker.h"
#include "FileStreamView.h"
#include "FileStringTools.h"
#include <QUuid>
#include <QCoreApplication>
#pragma execution_character_set("utf-8")
FileWorker::FileWorker(QWidget *parent)
	: QThread(parent)
{
	isWork = false;
	stop = false;
	isDelete = false;
	Workpath = "";
	mbPath = "";
	workLv = 0;
	allWorks = 0;
	finishWorks = 0;
	fileSize = 0;
	fileFinishSize = 0;
	workSize = 0;
	workFinishSize = 0;
	curl = curl_easy_init();
	fwm = new QList<FileWebManager*>();
	fwm->push_back(new FileWebManager(this));
	fwm->push_back(new FileWebManager(this));
	fwm->push_back(new FileWebManager(this));
	fwm->push_back(new FileWebManager(this));
}

FileWorker::~FileWorker()
{
}

void FileWorker::setVdl(QList<VirtualDisk*>* vdl) {
	this->vdl = vdl;
}

void FileWorker::setNewWork(FileStreamView::WorkType t, QList<QString> paths, QString mb, QStringList arg) {
	if (isWork) { return; }
	this->mode = t;
	this->paths = paths;
	this->mb = mb;
	this->stop = false;
	this->over = false;
	this->isDelete = false;
	this->Workpath = "";
	this->mbPath = "";
	this->workLv = 0;
	this->allWorks = 0;
	this->finishWorks = 0;
	this->fileSize = 0;
	this->fileFinishSize = 0;
	this->workSize = 0;
	this->workFinishSize = 0;
	this->arg = arg;
	this->start();
}

void FileWorker::setNewWork(FileStreamView::WorkType t, QList<QString> paths, QString mb) {
	if (isWork) { return; }
	this->mode = t;
	this->paths = paths;
	this->mb = mb;
	this->stop = false;
	this->over = false;
	this->isDelete = false;
	this->Workpath = "";
	this->mbPath = "";
	this->workLv = 0;
	this->allWorks = 0;
	this->finishWorks = 0;
	this->fileSize = 0;
	this->fileFinishSize = 0;
	this->workSize = 0;
	this->workFinishSize = 0;
	this->arg.clear();
	this->start();
}

bool FileWorker::isRun() {
	return isWork;
}

void FileWorker::doGoon() {
	stop = false;
}

void FileWorker::doStop() {
	stop = true;
}

void FileWorker::doOver() {
	over = true;
}

Mode FileWorker::StrToMode(QString s) {
	if (s.toUpper().trimmed() == "DISK") {
		return Disk;
	}
	else if (s.toUpper().trimmed() == "FTP") {
		return Ftp;
	}
	else if (s.toUpper().trimmed() == "BAIDU") {
		return BaiDu;
	}
	else if (s.toUpper().trimmed() == "JIANGUO") {
		return JianGuo;
	}
	else {
		return Disk;
	}
}


void FileWorker::run() {
	isWork = true;
	stop = false;
	over = false;
	if (arg.size() == 0) {
		path_type = Disk;
		mb_type = Disk;
	}
	else {
		path_type = StrToMode(arg[0]);
		mb_type = StrToMode(arg[1]);
	}
	if (mode == FileStreamView::COPY) {
		isDelete = false;
		workSize = getWorkSize(paths);
		unsigned long long fs = getHasSizeFree(mb);
		if (fs < workSize) { over = true; warnning = "目标目录没有足够的磁盘空间"; return; }
		QString dir = getDir();
		for (auto i : paths) {
			copy(dir, i, mb);
		}
	}
	else if (mode == FileStreamView::DELET) {
		isDelete = true;
		for (auto i : paths) {
			dele(i);
		}
	}
	else if (mode == FileStreamView::RENAME) {
		isDelete = false;
		workSize = getWorkSize(paths);
		unsigned long long fs = getHasSizeFree(mb);
		if (fs < workSize) { over = true; warnning = "目标目录没有足够的磁盘空间"; return; }
		QString dir = getDir();
		if (dir.split("/")[0] == mb.split("/")[0]) {
			for (auto i : paths) {
				rename(dir, i, mb);
			}
		}
		else {
			for (auto i : paths) {
				copy(dir, i, mb);
			}
			isDelete = true;
			for (auto i : paths) {
				dele(i);
			}
		}
	}
	isWork = false;
}

void FileWorker::dele(QString p1) {
	if (path_type == Disk) {
		dele_Disk(p1);
	}
	else if (path_type == Ftp) {
		dele_Ftp(p1);
	}
	else if (path_type == BaiDu) {
		dele_BaiDu(p1);
	}
}


void FileWorker::copy(QString dir, QString p1, QString p2) {
	if (path_type == Disk && mb_type == Disk) {
		copy_Disk(dir, p1, p2);
	}
	else if (path_type == BaiDu && mb_type == Disk) {
		down_BaiDu(dir, p1, p2);
	}
	else if (path_type == Disk && mb_type == BaiDu) {
		up_BaiDu(dir, p1, p2);
	}
	else if (path_type == JianGuo && mb_type == Disk) {
		down_JianGuo(dir, p1, p2);
	}
	else if (path_type == Disk && mb_type == JianGuo) {
		up_JianGuo(dir, p1, p2);
	}
	else if (path_type == JianGuo && mb_type == JianGuo) {
		if (isSameDisk(p1, p2)) {
			copy_JianGuo(dir, p1, p2);
		}
		else {
			QUuid id = QUuid::createUuid();
			QString strId = id.toString();
			QString pd = QCoreApplication::applicationDirPath()+"/tmp/"+strId;
			down_JianGuo(dir, p1, pd);
			up_JianGuo(pd, pd+ p1.split(dir)[1].split("/")[0], p2);
			dele_Disk(pd);
		}
	}
	else if (path_type == BaiDu && mb_type == BaiDu) {
		if (isSameDisk(p1, p2)) {
			copy_BaiDu(dir, p1, p2);
		}
		else {
			QUuid id = QUuid::createUuid();
			QString strId = id.toString();
			QString pd = QCoreApplication::applicationDirPath() + "/tmp/" + strId;
			down_JianGuo(dir, p1, pd);
			up_JianGuo(pd, pd + p1.split(dir)[1].split("/")[0], p2);
			dele_Disk(pd);
		}
	}
}

void FileWorker::rename(QString dir, QString p1, QString p2) {
	if (path_type == Disk && mb_type == Disk) {
		rename_Disk(dir, p1, p2);
	}
}

void FileWorker::dele_Disk(QString p1) {
	if (p1.isEmpty() || !QDir().exists(p1)) {
		return;
	}
	QFileInfo fileInfo(p1);

	if (fileInfo.isFile()) {
		QFile::remove(p1);
	}
	else if (fileInfo.isDir()){
		QDir qDir(p1);
		qDir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
		QFileInfoList fileInfoLst = qDir.entryInfoList();
		for(QFileInfo qFileInfo : fileInfoLst){
			if (qFileInfo.isFile()) {
				qDir.remove(qFileInfo.absoluteFilePath());
			}
			else {
				dele(qFileInfo.absoluteFilePath());
				qDir.rmdir(qFileInfo.absoluteFilePath());
			}
		}
		qDir.rmdir(fileInfo.absoluteFilePath());
	}
	return;
}


void FileWorker::copy_Disk(QString dir, QString p1, QString p2) {
	QFileInfo d(p1);
	if (!over) {
		if (d.isDir()) {
			QDir().mkpath(p2 + p1.split(dir)[1]);
			for (auto i : QDir(p1).entryInfoList()) {
				if (i.fileName() == "." || i.fileName() == "..") { continue; }
				if (over) { break; }
				copy(dir, i.filePath(), p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)d.size();
			fileFinishSize = 0;
			char* rbytes = new char[4096]{ 0 };
			uint len = 4096;
			QFile file(p1);
			QFile fileout(mbPath);
			file.open(QIODevice::ReadOnly);
			fileout.open(QIODevice::WriteOnly);
			if (file.isOpen() && fileout.isOpen()) {
				QDataStream in(&file);
				QDataStream out(&fileout);
				while (!in.atEnd()) {
					while (stop) { 
						msleep(200);
						if (over) {
							break;
						}
					}
					if (over) { break; }
					int readSize = 0;
					readSize = in.readRawData(rbytes, len);
					out.writeRawData(rbytes, readSize);
					fileFinishSize += readSize;
					workFinishSize += readSize;
				}
			}
			delete[] rbytes;
			file.close();
			fileout.close();
		}
	}
	if (over) {
		QFile::remove(p2 + p1.split(dir)[1]);
	
	}
	// over do...
	
}

void FileWorker::rename_Disk(QString dir, QString p1, QString p2) {
	QFileInfo d(p1);
	if (!over) {
		if (d.isDir()) {
			QDir().mkpath(p2 + p1.split(dir)[1]);
			for (auto i : QDir(p1).entryInfoList()) {
				if (i.fileName() == "." || i.fileName() == "..") { continue; }
				if (over) { break; }
				rename(dir, i.filePath(), p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)d.size();
			fileFinishSize = 0;
			while (stop) {
				msleep(200);
				if (over) {
					break;
				}
			}
			QFile::rename(p1, mbPath);
		}
	}
	if (over) {
		QFile::remove(p2 + p1.split(dir)[1]);

	}
	// over do...

}


unsigned long long FileWorker::getHasSizeFree(QString s) {
	s = s.split("/")[0] + "/";
	QStorageInfo si = QStorageInfo::root();
	QList<QStorageInfo> list = QStorageInfo::mountedVolumes();
	for (auto i : list) {
		if (i.name() == s) {
			si = i;
		}
	}
	return si.bytesFree();
}

unsigned long long FileWorker::getWorkSize(QList<QString> paths) {
	unsigned long long s = 0;
	for (auto i : paths) {
		QFileInfo f(i);
		if (f.isDir()) {
			QDir d(i);
			QList<QString> p;
			for (auto j : d.entryInfoList()) {
				if (j.fileName() != "." && j.fileName() != "..") {
					p.push_back(j.filePath());
				}
			}
			s += getWorkSize(p);
		}
		else {
			s += f.size();
		}
	}
	return s;
}

void FileWorker::up_BaiDu(QString dir, QString p1, QString p2) {
	VirtualDisk* vd = getVd(p1);
	
	VirtualDisk::fileTree* f = vd->getFiles(p1);
	QString ac = getVd(p2)->getMessageFromBaiDu()[0];
	if (!over) {
		if (f->type == DIR) {
			newBaiDuDir(p2 + p1.split(dir)[1], ac);
			if (f->size == 0) {
				getVd(p1)->upDatePath(p1);
			}
			for (int i = 0; i < f->size; i++) {
				if (over) { break; }
				up_BaiDu(dir, p1 + "/" + f->list[i]->name, p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			//对文件进行分片
			QStringList l = fileCut(4096 * 1024, p1);
			QStringList ml;
			for each (QString p in l) {
				ml.push_back(getFileMd5(p));
			}
			QString r = doBaiDuFileUpBeforehand(ml, p1, mbPath);
			if (r == "") { return; }
			QStringList sl_ = r.split("||");
			QString uploadid = sl_[0];
			QStringList nl = sl_[1].split(",");
			QString mb = getPathWithoutDiskName(mbPath);
			QStringList mdl;
			for each (QString v in nl) {
				QString md5 = "";
				while (md5 == "") {
					md5 = uploadBaiDuFile(uploadid, mb, v, p1 + ".ypup.p", ac);
					mdl.push_back(md5);
					msleep(500);
				}
			}
			QFile f(p1);
			QFileInfo fi(f);
			newBaiDuFile(mb, mdl, uploadid, ac, QString::number(fi.metadataChangeTime().toTime_t()), QString::number(f.size()));
		}
	}
}
void FileWorker::down_BaiDu(QString dir, QString p1, QString p2) {
	
	VirtualDisk::fileTree* f = getPathToFile(p1);
	if (!over) {
		if (f->type == DIR) {
			QDir().mkpath(p2 + p1.split(dir)[1]);
			if (f->size == 0) {
				getVd(p1)->upDatePath(p1);
			}
			for (int i = 0; i < f->size; i++) {
				if (over) { break; }
				down_BaiDu(dir, p1+"/"+f->list[i]->name, p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)f->size;
			fileFinishSize = 0;
			long long w = fileSize / 4;
			long long h = fileSize % 4;
			QString dlink = getBaiDuFileDlink(p1);
			fwm->at(0)->setDownloadWork(mbPath + ".ypDown.p1", w - 1, 0, dlink);
			fwm->at(1)->setDownloadWork(mbPath + ".ypDown.p2", w - 1, w, dlink);
			fwm->at(2)->setDownloadWork(mbPath + ".ypDown.p3", w - 1, w * 2, dlink);
			fwm->at(3)->setDownloadWork(mbPath + ".ypDown.p4", w + h - 1, w * 3, dlink);
			fwm->at(0)->start();
			fwm->at(1)->start();
			fwm->at(2)->start();
			fwm->at(3)->start();
			while (true) {
				msleep(100);
				long long t = 0;
				t += fwm->at(0)->getSize();
				t += fwm->at(1)->getSize();
				t += fwm->at(2)->getSize();
				t += fwm->at(3)->getSize();
				long long t_ = t - fileFinishSize;
				fileFinishSize += t_;
				workFinishSize += t_;
				if (stop) {
					fwm->at(0)->doStop();
					fwm->at(1)->doStop();
					fwm->at(2)->doStop();
					fwm->at(3)->doStop();
				}
				else {
					fwm->at(0)->doRun();
					fwm->at(1)->doRun();
					fwm->at(2)->doRun();
					fwm->at(3)->doRun();
				}
				while (stop) {
					msleep(500);
					if (over) {
						break;
					}
				}
				if (over) {
					fwm->at(0)->doOver();
					fwm->at(1)->doOver();
					fwm->at(2)->doOver();
					fwm->at(3)->doOver();
					break;
				}
				if (fwm->at(0)->isFinished() && fwm->at(1)->isFinished() 
					&& fwm->at(2)->isFinished() && fwm->at(3)->isFinished()) {
					if (fwm->at(0)->isSuccess() && fwm->at(1)->isSuccess()
						&& fwm->at(2)->isSuccess() && fwm->at(3)->isSuccess()) {
						fileAddFile(mbPath, mbPath + ".ypDown.p1");
						fileAddFile(mbPath, mbPath + ".ypDown.p2");
						fileAddFile(mbPath, mbPath + ".ypDown.p3");
						fileAddFile(mbPath, mbPath + ".ypDown.p4");
						QFile::remove(mbPath + ".ypDown.p1");
						QFile::remove(mbPath + ".ypDown.p2");
						QFile::remove(mbPath + ".ypDown.p3");
						QFile::remove(mbPath + ".ypDown.p4");
					}
					break;
				}
			}
		}
	}


}

void FileWorker::copy_BaiDu(QString dir, QString p1, QString p2) {
	VirtualDisk* vd = getVd(p1);
	VirtualDisk::fileTree* f = vd->getFiles(p1);
	QString ac = getVd(p2)->getMessageFromBaiDu()[0];


	if (!over) {
		if (f->type == DIR) {
			newBaiDuDir(p2 + p1.split(dir)[1], ac);
			if (f->size == 0) {
				getVd(p1)->upDatePath(p1);
			}
			for (int i = 0; i < f->size; i++) {
				if (over) { break; }
				copy_BaiDu(dir, p1 + "/" + f->list[i]->name, p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)f->size;
			fileFinishSize = 0;
			//webDavCopy(mbPath, Workpath, ac);
		}
	}
}


VirtualDisk::fileTree* FileWorker::getPathToFile(QString path) {
	VirtualDisk* vd = NULL;
	for each (VirtualDisk* v in *vdl) {
		if (path.contains(v->getDiskName())&&path[0] == v->getDiskName()[0]) {
			vd = v;
			break;
		}
	}
	if (vd == NULL) { return NULL; }
	return vd->getFiles(path);
}

VirtualDisk* FileWorker::getVd(QString path) {
	VirtualDisk* vd = NULL;
	for each (VirtualDisk * v in *vdl) {
		if ((path.contains(v->getDiskName())|| path.contains(v->getName())) && path[0] == v->getDiskName()[0]) {
			vd = v;
			break;
		}
	}
	return vd;
}

void FileWorker::rename_BaiDu(QString dir, QString p1, QString p2){

}
void FileWorker::dele_BaiDu(QString p1) {

}
void FileWorker::up_Ftp(QString dir, QString p1, QString p2) {

}
void FileWorker::down_Ftp(QString dir, QString p1, QString p2) {

}
void FileWorker::rename_Ftp(QString dir, QString p1, QString p2) {

}
void FileWorker::dele_Ftp(QString p1) {

}

void FileWorker::down_JianGuo(QString dir, QString p1, QString p2) {
	VirtualDisk* vd = getVd(p1);
	VirtualDisk::fileTree* f = vd->getFiles(p1);
	QStringList sl = vd->getMessageFromJianGuo();
	QString user = sl[0];
	QString pass = sl[1];
	
	if (!over) {
		if (f->type == DIR) {
			QDir().mkpath(p2 + p1.split(dir)[1]);
			if (f->size == 0) {
				getVd(p1)->upDatePath(p1);
			}
			for (int i = 0; i < f->size; i++) {
				if (over) { break; }
				down_JianGuo(dir, p1 + "/" + f->list[i]->name, p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)f->size;
			fileFinishSize = 0;
			long long w = fileSize / 4;
			long long h = fileSize % 4;
			QString dlink = "https://dav.jianguoyun.com/dav" + getPathWithoutDiskName(p1);
			fwm->at(0)->setDownloadWork(mbPath + ".ypDown.p1", w - 1, 0, dlink, user, pass);
			fwm->at(1)->setDownloadWork(mbPath + ".ypDown.p2", w - 1, w, dlink, user, pass);
			fwm->at(2)->setDownloadWork(mbPath + ".ypDown.p3", w - 1, w * 2, dlink, user, pass);
			fwm->at(3)->setDownloadWork(mbPath + ".ypDown.p4", w + h - 1, w * 3, dlink, user, pass);
			fwm->at(0)->start();
			fwm->at(1)->start();
			fwm->at(2)->start();
			fwm->at(3)->start();
			while (true) {
				msleep(100);
				long long t = 0;
				t += fwm->at(0)->getSize();
				t += fwm->at(1)->getSize();
				t += fwm->at(2)->getSize();
				t += fwm->at(3)->getSize();
				long long t_ = t - fileFinishSize;
				fileFinishSize += t_;
				workFinishSize += t_;
				if (stop) {
					fwm->at(0)->doStop();
					fwm->at(1)->doStop();
					fwm->at(2)->doStop();
					fwm->at(3)->doStop();
				}
				else {
					fwm->at(0)->doRun();
					fwm->at(1)->doRun();
					fwm->at(2)->doRun();
					fwm->at(3)->doRun();
				}
				while (stop) {
					msleep(500);
					if (over) {
						break;
					}
				}
				if (over) {
					fwm->at(0)->doOver();
					fwm->at(1)->doOver();
					fwm->at(2)->doOver();
					fwm->at(3)->doOver();
					break;
				}
				if (fwm->at(0)->isFinished() && fwm->at(1)->isFinished()
					&& fwm->at(2)->isFinished() && fwm->at(3)->isFinished()) {
					if (fwm->at(0)->isSuccess() && fwm->at(1)->isSuccess()
						&& fwm->at(2)->isSuccess() && fwm->at(3)->isSuccess()) {
						fileAddFile(mbPath, mbPath + ".ypDown.p1");
						fileAddFile(mbPath, mbPath + ".ypDown.p2");
						fileAddFile(mbPath, mbPath + ".ypDown.p3");
						fileAddFile(mbPath, mbPath + ".ypDown.p4");
						QFile::remove(mbPath + ".ypDown.p1");
						QFile::remove(mbPath + ".ypDown.p2");
						QFile::remove(mbPath + ".ypDown.p3");
						QFile::remove(mbPath + ".ypDown.p4");
					}
					break;
				}
			}
		}
	}
}
void FileWorker::up_JianGuo(QString dir, QString p1, QString p2) {

	VirtualDisk* vd = getVd(p1);
	VirtualDisk::fileTree* f = vd->getFiles(p1);
	QStringList sl = getVd(p2)->getMessageFromJianGuo();
	QString user = sl[0];
	QString pass = sl[1];

	if (!over) {
		if (f->type == DIR) {
			newWebDavDir(p2 + p1.split(dir)[1],user,pass);
			if (f->size == 0) {
				getVd(p1)->upDatePath(p1);
			}
			for (int i = 0; i < f->size; i++) {
				if (over) { break; }
				up_JianGuo(dir, p1 + "/" + f->list[i]->name, p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)f->size;
			fileFinishSize = 0;
			upWebDavFile(mbPath,Workpath,user,pass);
		}
	}

}
void FileWorker::copy_JianGuo(QString dir, QString p1, QString p2) {
	VirtualDisk* vd = getVd(p1);
	VirtualDisk::fileTree* f = vd->getFiles(p1);
	QStringList sl = getVd(p2)->getMessageFromJianGuo();
	QString user = sl[0];
	QString pass = sl[1];

	if (!over) {
		if (f->type == DIR) {
			newWebDavDir(p2 + p1.split(dir)[1], user, pass);
			if (f->size == 0) {
				getVd(p1)->upDatePath(p1);
			}
			for (int i = 0; i < f->size; i++) {
				if (over) { break; }
				copy_JianGuo(dir, p1 + "/" + f->list[i]->name, p2);
			}
		}
		else {
			Workpath = p1;
			mbPath = p2 + p1.split(dir)[1];
			fileSize = (unsigned long long)f->size;
			fileFinishSize = 0;
			webDavCopy(mbPath, Workpath, user, pass);
		}
	}







}
void FileWorker::move_JianGuo(QString dir, QString p1, QString p2) {

}
void FileWorker::dele_JianGuo(QString p1) {
	VirtualDisk* vd = getVd(p1);
	QStringList sl = vd->getMessageFromJianGuo();
	QString user = sl[0];
	QString pass = sl[1];
	QString url = "https://dav.jianguoyun.com/dav" + getPathWithoutDiskName(p1);
	char urlc[1024];
	FileStringTools::getChar(url, urlc);
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	if (ok == 0) {
		return;
	}
	return;

}

QString FileWorker::getWorkpath() {
	return Workpath;
}
int FileWorker::getWorkLv() {
	return workLv;
}
int FileWorker::getAllWorks() {
	return allWorks;
}
int FileWorker::getFinishWorks() {
	return finishWorks;
}
unsigned long long FileWorker::getWorkSize() {
	return workSize + 1;
}
unsigned long long FileWorker::getWorkFinishSize() {
	return workFinishSize + 1;
}

unsigned long long FileWorker::getFileSize() {
	return fileSize + 1;
}
unsigned long long FileWorker::getFileFinishSize() {
	return fileFinishSize + 1;
}
QString FileWorker::getWarnning() {
	return warnning;
}

QString FileWorker::getDir() {
	QString s = "";
	QString s1 = "";
	int j = 0;
	while (true) {
		for (QString i : paths) {
			if (j == i.split("/").size()-1) {
				return s;
			}
			if (s1 == "") {
				s1 = i.split("/")[j];
			}
			else {
				if (s1 != i.split("/")[j]) {
					return s;
				}
			}
		}
		s += (s == "" ? "" : "/") + s1;
		s1 = "";
		j++;
	}
}
QString FileWorker::getMb() {
	return mb;
}
FileStreamView::WorkType FileWorker::getMode() {
	return mode;
}

QString FileWorker::getMbPath() {
	return mbPath;
}

bool FileWorker::getDelete() {
	return isDelete;
}

void FileWorker::fileAddFile(QString a, QString b) {
	char* rbytes = new char[4096]{ 0 };
	uint len = 4096;
	QFile fileout(a);
	QFile file(b);
	file.open(QIODevice::ReadOnly);
	fileout.open(QIODevice::WriteOnly | QIODevice::Append);
	if (file.isOpen() && fileout.isOpen()) {
		QDataStream in(&file);
		QDataStream out(&fileout);
		while (!in.atEnd()) {
			int readSize = 0;
			readSize = in.readRawData(rbytes, len);
			out.writeRawData(rbytes, readSize);
		}
	}
	delete[] rbytes;
	file.close();
	fileout.close();
}

QString FileWorker::getBaiDuFileDlink(QString p) {
	VirtualDisk* vd = getVd(p);
	QStringList sl = vd->getMessageFromBaiDu();
	QString fsid = vd->getFiles(p)->downloadMessage;
	QString ac = sl[0];
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, ("https://pan.baidu.com/rest/2.0/xpan/multimedia?method=filemetas&access_token="+ac+"&dlink=1&fsids=["+ fsid +"]").toStdString().c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "pan.baidu.com");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson(re.toUtf8());
		if (json["errno"].toInt() == 0) {
			return json["list"].toArray()[0].toObject()["dlink"].toString()+"&access_token="+ac;
		}
	}


}


QStringList FileWorker::fileCut(long long size, QString path) {
	QFile f(path);
	QStringList l;
	if (!f.exists()) { return l; }
	int p = 0;
	int s = f.size();
	char* rbytes = new char[4096]{ 0 };
	uint len = 4096;
	f.open(QIODevice::ReadOnly);
	if (!f.isOpen()) { return l; }
	QDataStream in(&f);
	while (s > 0) {
		QString path_ = path + ".ypup.p" + QString::number(p);
		QFile f_(path_);
		f_.open(QIODevice::WriteOnly);
		int s_ = (s > size ? size : s);
		if (f_.isOpen()) {
			QDataStream out(&f_);
			while (s_ != 0) {
				int readSize = 0;
				if (s_ >= len) {
					readSize = in.readRawData(rbytes, len);
					out.writeRawData(rbytes, readSize);
					s_ -= readSize;
				}
				else {
					readSize = in.readRawData(rbytes, s_);
					out.writeRawData(rbytes, readSize);
					s_ -= readSize;
				}
			}
		}
		f_.close();
		p++;
		s -= (s > size ? size : s);
		l.push_back(path_);
	}
	f.close();
	return l;
}

QString FileWorker::getFileMd5(QString filePath) {
	QFile localFile(filePath);
	if (!localFile.open(QFile::ReadOnly)) {
		qDebug() << "file open error.";
		return 0;
	}

	QCryptographicHash ch(QCryptographicHash::Md5);

	quint64 totalBytes = 0;
	quint64 bytesWritten = 0;
	quint64 bytesToWrite = 0;
	quint64 loadSize = 1024 * 4;
	QByteArray buf;

	totalBytes = localFile.size();
	bytesToWrite = totalBytes;

	while (1) {
		if (bytesToWrite > 0) {
			buf = localFile.read(qMin(bytesToWrite, loadSize));
			ch.addData(buf);
			bytesWritten += buf.length();
			bytesToWrite -= buf.length();
			buf.resize(0);
		}
		else {
			break;
		}

		if (bytesWritten == totalBytes) {
			break;
		}
	}
	localFile.close();
	QByteArray md5 = ch.result();
	qDebug() << md5.toHex();
	QString s(md5.toHex());
	qDebug() << s;
	return s;
}

QString FileWorker::doBaiDuFileUpBeforehand(QStringList ml, QString p,QString mb) {
	VirtualDisk* vd = getVd(p);
	VirtualDisk::fileTree* f = vd->getFiles(p);
	QStringList sl = getVd(mb)->getMessageFromBaiDu();
	QString ac = sl[0];
	QString url = "http://pan.baidu.com/rest/2.0/xpan/file?method=precreate&access_token=" + ac;
	QString post = "path=" + getPathWithoutDiskName(mb) + "&size=" + QString::number(f->size) + "&isdir=0&autoinit=1&block_list=[";
	for each (QString s in ml) {
		post += "\""+s + "\",";
	}
	post += "]";
	post.replace(",]", "]");
	char urlc[1024];
	char postc[1024];
	FileStringTools::getChar(url, urlc);
	FileStringTools::getChar(post, postc);
	qDebug() << url;
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
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson(re.toUtf8());
		if (json["errno"].toInt() == 0) {
			if (json["return_type"].toInt() == 1) {
				QString r = "";
				r+=json["uploadid"].toString()+"||";
				for each (QVariant v in json["block_list"].toArray().toVariantList()) {
					r += QString::number(v.toInt()) + ",";
				}
				r += "]";
				r.replace(",]", "");
				return r + "||" + ac;
			}
			else {
				return "";
			}
		}
	}
}

QString FileWorker::uploadBaiDuFile(QString id, QString path, QString l, QString file,QString ac) {
	int readSize = 0;
	char pathc[1024] = { 0 };
	char urlc[1024] = { 0 };
	FileStringTools::getLocalChar(file + l, pathc);
	
	QString url = "https://d.pcs.baidu.com/rest/2.0/pcs/superfile2?method=upload&type=tmpfile&access_token=" + ac +
		"&path=" + path + "&uploadid=" + id + "&partseq=" + l;
	FileStringTools::getChar(url, urlc);
	struct curl_httppost* formpost = NULL;
	struct curl_httppost* lastptr = NULL;
	QString re = "";
	qDebug()<<curl_formadd(&formpost, &lastptr, CURLFORM_COPYNAME, "file", CURLFORM_FILE, pathc, CURLFORM_END);

	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "pan.baidu.com");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	curl_formfree(formpost);
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson(re.toUtf8());
		if (!json["md5"].isUndefined()) {
			return json["md5"].toString();
		}
		return "";
	}
}

QString FileWorker::getPathWithoutDiskName(QString p) {
	QStringList sl = p.replace("://","+:kk:+").split("/");
	QString r = "";
	for (int i = 1; i < sl.size(); i++) {
		r += "/" + sl[i].replace("+:kk:+","://");
	}
	return r;
}

void FileWorker::newBaiDuFile(QString p, QStringList mdl, QString id, QString ac, QString t, QString s) {
	QString url = "https://pan.baidu.com/rest/2.0/xpan/file?method=create&access_token=" + ac;
	QString post = "path=" + p + "&isdir=0" + "&size=" + s + "&uploadid=" + id + "&local_mtime=" + t + "&local_ctime=" + t + "&block_list=[";
	for each (QString v in mdl) {
		url += v + ",";
	}
	url += "]";
	url.replace(",]", "]");
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
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson(re.toUtf8());
		if (json["errno"].toInt() == 0) {
		
		}
	}
}

void FileWorker::newBaiDuDir(QString p, QString ac) {
	QString url = "https://pan.baidu.com/rest/2.0/xpan/file?method=create&access_token=" + ac + "&path=" + p + "&isdir=1&size=0";
	char urlc[1024];
	FileStringTools::getChar(url, urlc);
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "pan.baidu.com");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson(re.toUtf8());
		if (json["errno"].toInt() == 0) {

		}
	}
}

bool FileWorker::newWebDavDir(QString p, QString user, QString pass) {
	QString url = "https://dav.jianguoyun.com/dav"+getPathWithoutDiskName(p);
	char urlc[1024];
	FileStringTools::getChar(url, urlc);
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "MKCOL");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	if (ok == 0) {
		return true;
	}
	return false;
}

bool FileWorker::upWebDavFile(QString p, QString file, QString user, QString pass) {
	QString url = "https://dav.jianguoyun.com/dav" + getPathWithoutDiskName(p);
	char urlc[1024];
	FileStringTools::getChar(url, urlc);
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	char pathc[1024];
	FileStringTools::getLocalChar(file,pathc);
	QString re = "";
	FILE* f = fopen(pathc,"r");
	struct stat info;
	stat(pathc, &info);
	size_t size = info.st_size;
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(curl, CURLOPT_PUT, 1L);
	curl_easy_setopt(curl, CURLOPT_READDATA, f);
	curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, size);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	fclose(f);
	if (ok == 0) {
		if (re.contains("502")) {
			return false;
		}
		return true;
	}
	return false;
}

bool FileWorker::webDavMove(QString p, QString mb, QString user, QString pass) {
	QString url = "https://dav.jianguoyun.com/dav" + getPathWithoutDiskName(p);
	char urlc[1024];
	FileStringTools::getChar(url, urlc);
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "MOVE");
	char mbc[1024];
	FileStringTools::getChar(getPathWithoutDiskName(mb), mbc);
	char mbcc[1024] = { 0 };
	sprintf(mbcc, "Destination:%s", mbc);
	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, mbcc);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	if (ok == 0) {
		if (re.contains("502")) {
			return false;
		}
		return true;
	}
	return false;
}
bool FileWorker::webDavCopy(QString p, QString mb, QString user, QString pass) {
	QString url = "https://dav.jianguoyun.com/dav" + getPathWithoutDiskName(p);
	char urlc[1024];
	FileStringTools::getChar(url, urlc);
	char userc[256];
	char passc[128];
	FileStringTools::getChar(user, userc);
	FileStringTools::getChar(pass, passc);
	char upc[384] = { 0 };
	sprintf(upc, "%s:%s", userc, passc);
	QString re = "";
	curl_easy_setopt(curl, CURLOPT_URL, urlc);
	curl_easy_setopt(curl, CURLOPT_USERPWD, upc);
	curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "COPY");
	char mbc[1024];
	FileStringTools::getChar(getPathWithoutDiskName(mb), mbc);
	char mbcc[1024] = { 0 };
	sprintf(mbcc, "Destination:%s", mbc);
	struct curl_slist* headers = NULL;
	headers = curl_slist_append(headers, mbcc);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&re);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &FileStringTools::getRep);
	int ok = curl_easy_perform(curl);
	curl_easy_reset(curl);
	if (ok == 0) {
		if (re.contains("502")) {
			return false;
		}
		return true;
	}
	return false;
}

bool FileWorker::isSameDisk(QString a, QString b) {
	return (a.replace("://", "+:kk:+").split("/")[0] == b.replace("://", "+:kk:+").split("/")[0]);
}

bool FileWorker::baiDuMove(QString p, QString mb, QString ac) {
	QString url = "https://pan.baidu.com/rest/2.0/xpan/file?method=filemanager&opera=copy&access_token=" + ac;
	QString post = "async=1&filelist=[";
	//for each (QString v in mdl) {
	///	url += v + ",";
	//}
	url += "]";
	url.replace(",]", "]");
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
	if (ok == 0) {
		QJsonDocument json = QJsonDocument::fromJson(re.toUtf8());
		if (json["errno"].toInt() == 0) {

		}
	}
	return false;
}