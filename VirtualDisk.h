#pragma once
#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>
#include <QDebug>
#include <QThread>
#pragma execution_character_set("utf-8")
class DiskHandleClient;

#include <QStorageInfo>


enum yunType : int{
	DISK = 0,
	FTP = 1,
	SMB = 2,
	SEA_FILE = 3,
	BAI_DU = 4,
	_360 = 5,
	TENG_XUN = 6,
	_115 = 7,
	JIAN_GUO = 8
};

enum fileType {
	DIR,
	TXT,
	_7Z
};

//虚拟磁盘
class VirtualDisk : public QThread {

	Q_OBJECT
public:
	class fileTree {
	public:
		fileTree();
		void deleteSelf();            //删除所有，包括孩子
		void deleteThis();            //只是删除自己
		QString name;                 //文件/文件夹名称
		fileType type;                 //类型 0 文件夹，
		long long size;               //文件夹->文件列表长度，文件->文件大小B
		QString date;                 //文件更新日期，标识文件是否更改
		bool isSame;                  //标识与网络文件是否一致
		bool isLocal;                 //标识是否本地文件 true 本地需备份， false 存在网络 以date确定文件新旧
		bool isSearch;
		QString downloadMessage;       //下载信息，用于网盘文件下载所需的信息
		QString path;                 //为空：本地无缓存，“defeat”：使用默认路径，“sss/sss/sss”自定义路径（./ 相对于上级目录）
		fileTree** list;       //
		fileTree* parent;
		QString getNetPath();
		bool operator==(fileTree*);
		bool operator==(QFileInfo&);
	};
protected:
	void run();
private:
	//名称
	QString name;
	//类型  0自定义私有云，1百度，2阿里，。。
	yunType type;
	//备注
	QString bz;
	//文件树

	fileTree* files;
	DiskHandleClient* dhc;
	QString workPath;

	QString cookie;

	QString diskName;

	QString maxSize;

	QString useSize;

	double usedSizeRate;

	void upDateDisk();
	void upDateBaiDu();
	bool upDateDiskWithPath( QString& path, fileTree* files,int dd);
	void clean(fileTree* file);
	
public:
	//构造函数
	VirtualDisk();
	VirtualDisk(yunType, QString);
	VirtualDisk(yunType, QString, QString);
	VirtualDisk(yunType, QString, QString, QString);
	VirtualDisk(yunType, QString, QString, QString, QString);
	VirtualDisk(yunType, QString, QString, QString, QString, QString);

	~VirtualDisk();
	void upDate();
	bool upDatePath(QString path);
	bool upDatePath_(QString path);
	//获取工作目录
	QString getWorkPath();

	//获取虚拟名称
	QString getName();
	QString getDiskName();

	//获取磁盘类型id
	int getType();

	//获取磁盘类型
	QString getTypeName();

	//获取磁盘备注
	QString getBz();

	//获取根目录文件树
	fileTree* getFiles();

	//通过路径获取文件树
	VirtualDisk::fileTree* getFiles(QString& path);
	VirtualDisk::fileTree* getFiles(QString& dir,QString& path);
	VirtualDisk::fileTree* getFiles(VirtualDisk::fileTree* file, QString& path);

	//判断该文件是否备份
	bool isSame(VirtualDisk::fileTree* file);
	bool isSame( QString& path);
	bool isSame( QString& dir,  QString& path);

	//获取文件最后修改日期
	QString getLastTime(VirtualDisk::fileTree* file);
	QString getLastTime( QString& path);
	QString getLastTime( QString& dir,  QString& path);

	//获取本地文件最后修改日期
	QString getLastTimeWithLocalPath( QString& path);

	//获取文件在本地的备份路径
	QString getLoaclPath(VirtualDisk::fileTree* file);
	QString getLoaclPath( QString& path);
	QString getLoaclPath( QString& dir,  QString& path);

	//获取文件大小或文件数量
	long long getFileSize(VirtualDisk::fileTree* file);
	long long getFileSize( QString& path);
	long long getFileSize( QString& dir,  QString& path);

	//获取目标文件树在云盘路径
	QString getNetPath(VirtualDisk::fileTree* file);

	//获取上级目录
	VirtualDisk::fileTree* getParentDir(VirtualDisk::fileTree* file);

	QStringList* getDir(QString dir);

	bool canUsed();
	void setLogin(QStringList);
	QStringList getMessageFromBaiDu();
	QStringList getMessageFromJianGuo();

};

extern QList<VirtualDisk::fileTree*> deleteFileList;
extern QList<VirtualDisk::fileTree*> deleteFileList_;

