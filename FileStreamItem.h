#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "FileStringTools.h"
#pragma execution_character_set("utf-8")
class FileWorker;

class FileStreamItem : public QWidget
{
	Q_OBJECT

public:
	FileStreamItem(QWidget *parent,int fWidth);
	~FileStreamItem();
	void setWorker(FileWorker*);
	bool isUse();
	int fWidth;
	void upDate();
public slots:
	void stop();
	void over();
	void goon();

private:
	QPushButton* goonButton;
	QPushButton* stopButton;
	QPushButton* overButton;
	QLabel* workName;
	QLabel* mainWork;
	QLabel* workLv;
	QLabel* workSpeed;
	QFrame* f1;
	QFrame* f2;
	QFrame* f3;
	int lastFinishWorks;
	int timeFinish;
	double lastDelNow;
	unsigned long long lastWorkSize;


	QString mode;
	FileWorker* fwr;
};
