#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QResizeEvent>
#include <QClipboard>
#include <QMimeData>
#include "FileStreamView.h"
#include "TopMenuView.h"
#include "LocationView.h"
#include "ui_MainWindows.h"
#include "fileSenceView.h"
#pragma execution_character_set("utf-8")
enum OSTpye {
	WINDOWS,
	LINUX,
	MAC
};
#if defined(_WIN64) || defined(_WIN32)
#define THIS_OS OSTpye::WINDOWS
#elif defined(_linux) || defined(_linux_)
#define THIS_OS OSTpye::LINUX
#endif


class MainWindows : public QWidget
{
	Q_OBJECT

public:
	MainWindows(QWidget *parent, FileStreamView* streamView, QList<VirtualDisk*>* vdl);
	~MainWindows();
	void upDate(int w);
	void resizeEvent(QResizeEvent* size);
	bool getShift();
	void setLineEdit(QLineEdit*);
	QLineEdit* getLineEdit();
	fileSenceView* getFsv();
	LocationView* getLv();
	void ctrlC();
	void ctrlV();
	void ctrlZ();
	void ctrlY();
	void ctrlX();
	void ctrlA();
	void ctrlD();

	void shiftDel();
	void ctrlShiftN();
	void altEnter();

private:
	FileStreamView* streamView;
	LocationView* lv;
	QLineEdit* lineEdit;
	QClipboard* clipboard;
	Ui::MainWindows ui;
	TopMenuView* topMenuView;
	fileSenceView* fsv;
	bool shift;
	bool ctrl;
	bool alt;

public slots:
	void doSome();
protected:
	virtual void keyPressEvent(QKeyEvent* ev);
	virtual void keyReleaseEvent(QKeyEvent* ev);
	
};
