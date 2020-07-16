#pragma once

#include <QWidget>

#include "FilesTreeButton.h"
#include "VirtualDisk.h"
#pragma execution_character_set("utf-8")

class FilesTreeView : public QWidget
{
	Q_OBJECT

public:
	FilesTreeView(QWidget *parent, QList<VirtualDisk*>* vdl);
	~FilesTreeView();

	VirtualDisk* getVirtualDisk(QString name);
	void upDateWithData();
	void setNewUseButton(FilesTreeButton* b);
	void appendVirtualDisk(VirtualDisk* virtualDisk);
	void setWidth(int w);
	int getWidth();
public slots:
	void upDate();

private:
	QTimer* time;
	FilesTreeButton** treeButtons;
	QList<VirtualDisk*>* virtualDisk;
	int w;
	int len;
	int maxLine;
};
