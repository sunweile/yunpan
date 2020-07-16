#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QScrollBar>
#include <QKeyEvent>
#include "DetailedFileView.h"
#include "YpLine.h"
#include "FilesTreeView.h"
#pragma execution_character_set("utf-8")
class UserHandle;

class fileSenceView : public QWidget
{
	Q_OBJECT

public:
	fileSenceView(QWidget *parent, QList<VirtualDisk*>* vdl);
	~fileSenceView();
	void setSize(int w,int h);
	DetailedFileView* getDfv();
	UserHandle* getUh();
	void openDir(QString);
	void setXm(int);
	void setXmxx(QList<QString>*);
	void setLogin(QStringList);
public slots:
	void lineDown(int x);
	void lineUp();
	void lineMove(int x);
private:
	QLabel* xm;
	QFrame* l1;
	QLabel* xmxx;
	QFrame* top;
	QList<VirtualDisk*>* vdl;
	FilesTreeView* fv;
    QScrollArea* scrollArea;
	QScrollArea* filesArea;
	DetailedFileView* dfv;
	YpLine* line;
	int lineX;
	int posX;
	UserHandle* uh;
};
