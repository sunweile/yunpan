#pragma once

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include "YpButton.h"
#include "VirtualDisk.h"
#include <QFrame>
#include <QList>
#include <QPalette>
#include <QPushButton>
#pragma execution_character_set("utf-8")
class FilesTreeView;
class fileSenceView;

class FilesTreeButton : public QFrame
{
	Q_OBJECT

public:
	enum type {
		DIR,
		DISK

	};
	FilesTreeButton(QWidget* parent, FilesTreeButton* dirParentButton, QString name);
	FilesTreeButton(QWidget *parent, FilesTreeButton* dirParentButton, QString name, QString pname);
	~FilesTreeButton();

	void cleanDirs();
	bool getIsRun();
	void setIsRun(bool b);
	int getLen();
	int getHeight();
	int upDate(int y,int w);
	void upDateWithData();
	QString getPath();
	FilesTreeView* getTreeView();
	void killDirs();
	void hideDirs();
	void focusOut();
	void focusIn();
	void setVirtualDisk(VirtualDisk* vd);

	void setNeedLogin();
	void notNeedLogin();
public slots:
	//void dirButtonChick();
	void moreDirsButtonChick();
	void needButtonChick();
	
private:
	bool needLogin;
	int height;
	type type;
	QString name;
	QString pname;
	int line;
	QLabel* dirButton;
	YpButton* moreDirsButton;
	bool isRun;
	FilesTreeButton* dirParentButton;
	QList<FilesTreeButton*>* dirButtons;
	bool isUse;
	VirtualDisk* vd;

protected:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	//void focusOutEvent(QFocusEvent* e);
};
