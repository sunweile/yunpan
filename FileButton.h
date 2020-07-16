#pragma once

#include <QFrame>
#include <QLabel>
#include <QFileIconProvider>
#include <QPushButton>
#include <QPixmap>
#include <QTimer>
#include <QLineEdit>
#include <QMap>
#include "VirtualDisk.h"
#include "FileStringTools.h"
#pragma execution_character_set("utf-8")
class FileButton : public QFrame
{
	Q_OBJECT

public:
	FileButton(QWidget*parent);
	~FileButton();
	int setFile(VirtualDisk::fileTree* file,int mode);
	QString getFile();
	void focusOut();
	void focusOutChoose();
	void choose();
	void use();
	void unChoose();
	void unUse();
	static QMap<QString, QIcon>* IconsMap;

private:
	bool isChoose;
	bool isUse;
	int mode;
	int time;
	QTimer* timer;
	QString file;
	QLineEdit* nameEdit;
	QLabel* fileImage;
	QLabel* fileName;
	QLabel* fileDate;
	QLabel* fileDateLabel;
	QLabel* fileType;
	QLabel* fileTypeLabel;
	QLabel* fileSize;
	QLabel* fileSizeLabel;
public slots:
	void click();
	void nameEditReturn();
protected:
	bool eventFilter(QObject* obj, QEvent* event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
};
