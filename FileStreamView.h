#pragma once

#include <QWidget>
#include <QList>
#include <QTimer>
#include <QMessageBox>
#include <QCloseEvent>
#include "VirtualDisk.h"
#pragma execution_character_set("utf-8")
class FileStreamItem;

class FileWorker;


class FileStreamView : public QWidget
{
	Q_OBJECT

public:
	enum WorkType{
		COPY,
		RENAME,
		DELET
	};

	FileStreamView(QWidget *parent);
	~FileStreamView();
	void newWork(WorkType t, QList<QString> paths, QString mb);
	void closeEvent(QCloseEvent*);
	void setVdl(QList<VirtualDisk*>* vdl);
public slots:
	void upDate();

private:
	QList<VirtualDisk*>* vdl;
	QList<FileStreamItem*>* itemList;
	int doClean;
	int doCleanMax;
	QList<FileWorker*>* worker;
	QTimer* timer;
};
