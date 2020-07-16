#pragma once

#include <QWidget>
#include <QList>
#include "FileButton.h"
#include "UserHandle.h"
#pragma execution_character_set("utf-8")
class DetailedFileView : public QWidget
{
	Q_OBJECT

public:
	DetailedFileView(QWidget *parent, UserHandle* uh);
	~DetailedFileView();
	void upDateSearch();
	void search(QList<VirtualDisk::fileTree*>*);
	void notSearch();
	void otherUnUse(FileButton*);
	void otherUse(FileButton*);
	void setUsed(FileButton*);
	void otherUnChoose(FileButton*);
	void listOut();
	void chooseAll();
	QList<QString>* getList();
	void upDate();
	UserHandle* getUh();
	bool getCopy();
	void setCopy(bool);
	void open(QString);
public slots:
	void upDateWithData();

private:
	int lastW;
	int lastH;
	int search_x;
	int search_y;
	int search_h;
	int timeIndex;
	int searchIndex;
	QList<VirtualDisk::fileTree*>* searchList;
	QTimer* timer;
	bool isCopy;
	UserHandle* uh;
	QList<FileButton*>* files;
	QList<QString>* chooseList;
	FileButton* lastUsed;
	int useLen;
	int showMode;
	void mouseReleaseEvent(QMouseEvent* event);

};
