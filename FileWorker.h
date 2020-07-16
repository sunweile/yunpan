#pragma once

#include <QThread>
#include <QList>
#include <QDir>
#include <QFile>
#include <QStorageInfo>
#include <qDebug>
#include "FileStreamView.h"
#include "VirtualDisk.h"
#include "FileWebManager.h"
#pragma execution_character_set("utf-8")

enum Mode : int{
	Disk,
	Ftp,
	BaiDu,
	JianGuo
};

class FileWorker : public QThread
{
	Q_OBJECT

public:
	
	FileWorker(QWidget *parent);
	~FileWorker();
	void setVdl(QList<VirtualDisk*>* vdl);
	void setNewWork(FileStreamView::WorkType t, QList<QString> paths, QString mb);
	void setNewWork(FileStreamView::WorkType t, QList<QString> paths, QString mb, QStringList arg);
	unsigned long long getWorkSize(QList<QString> paths);
	unsigned long long getHasSizeFree(QString s);
	void copy(QString dir, QString p1,QString p2);
	void rename(QString dir, QString p1, QString p2);
	void dele(QString p1);


	void copy_Disk(QString dir, QString p1, QString p2);
	void rename_Disk(QString dir, QString p1, QString p2);
	void dele_Disk(QString p1);
	void up_BaiDu(QString dir, QString p1, QString p2);
	void down_BaiDu(QString dir, QString p1, QString p2);
	void copy_BaiDu(QString dir, QString p1, QString p2);
	void rename_BaiDu(QString dir, QString p1, QString p2);
	void dele_BaiDu(QString p1);
	void up_Ftp(QString dir, QString p1, QString p2);
	void down_Ftp(QString dir, QString p1, QString p2);
	void rename_Ftp(QString dir, QString p1, QString p2);
	void dele_Ftp(QString p1);
	void down_JianGuo(QString dir, QString p1, QString p2);
	void up_JianGuo(QString dir, QString p1, QString p2);
	void copy_JianGuo(QString dir, QString p1, QString p2);
	void move_JianGuo(QString dir, QString p1, QString p2);
	void dele_JianGuo(QString p1);



	void run();
	bool isRun();
	void doGoon();
	void doStop();
	void doOver();
	bool getDelete();

	QString getWorkpath();
	QString getMbPath();
	int getWorkLv();
	int getAllWorks();
	int getFinishWorks();
	unsigned long long getWorkSize();
	unsigned long long getWorkFinishSize();

	unsigned long long getFileSize();
	unsigned long long getFileFinishSize();
	QString getWarnning();

	QString getDir();
	QString getMb();
	FileStreamView::WorkType getMode();
	VirtualDisk::fileTree* getPathToFile(QString path);
	VirtualDisk* getVd(QString path);
	Mode StrToMode(QString);

private:
	bool isWork;
	bool stop;
	bool over;
	bool isDelete;

	CURL* curl;
	QList<VirtualDisk*>* vdl;
	QString Workpath;
	QString mbPath;
	int workLv;
	int allWorks;
	int finishWorks;
	unsigned long long workSize;
	unsigned long long workFinishSize;

	unsigned long long fileSize;
	unsigned long long fileFinishSize;
	QString warnning;
	
	QList<QString> paths;
	QString mb;
	Mode mb_type;
	Mode path_type;
	FileStreamView::WorkType mode;

	QStringList arg;
	QList<FileWebManager*>* fwm;

	void fileAddFile(QString a, QString b);
	QString getBaiDuFileDlink(QString p);
	QStringList fileCut(long long size,QString path);
	QString getFileMd5(QString filePath);
	QString doBaiDuFileUpBeforehand(QStringList ml, QString p, QString mb);
	QString uploadBaiDuFile(QString id, QString path, QString l, QString file, QString ac);
	QString getPathWithoutDiskName(QString p);
	void newBaiDuDir(QString p, QString ac);
	void newBaiDuFile(QString p,QStringList mdl,QString id, QString ac, QString t, QString s);
	bool baiDuMove(QString p, QString mb, QString ac);

	bool newWebDavDir(QString p, QString user, QString pass);
	bool upWebDavFile(QString p, QString file, QString user, QString pass);

	bool webDavMove(QString p, QString mb, QString user, QString pass);
	bool webDavCopy(QString p, QString mb, QString user, QString pass);
	bool isSameDisk(QString a, QString b);
};

