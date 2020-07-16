#include "FilesTreeView.h"
#pragma execution_character_set("utf-8")
FilesTreeView::FilesTreeView(QWidget *parent, QList<VirtualDisk*>* vdl)
	: QWidget(parent)
{
	treeButtons = new FilesTreeButton * [vdl->size()];
	len = vdl->size();
	int i = 0;
	for each (VirtualDisk* vd in *vdl) {
		treeButtons[i] = new FilesTreeButton(this, NULL, vd->getName(),vd->getDiskName());
		treeButtons[i]->setIsRun(false);
		i++;
	}
	this->virtualDisk = vdl;
	time = new QTimer(this);
	connect(time, SIGNAL(timeout()), this, SLOT(upDate()));
	time->start(500);

}

FilesTreeView::~FilesTreeView()
{
	time->stop();
	time->deleteLater();
}

void FilesTreeView::appendVirtualDisk(VirtualDisk* virtualDisk) {
	this->virtualDisk->append(virtualDisk);
}

void FilesTreeView::upDate() {
	int y = 15;
	int w = getWidth();
	for (int i = 0; i < len; i++) {
		FilesTreeButton* b = treeButtons[i];
		for each (VirtualDisk* v in *virtualDisk){
			if (b->getPath() == v->getName()) {
				if (v->canUsed()) {
					b->notNeedLogin();
				}
				else {
					b->setNeedLogin();
				}
				break;
			}
		}
		y += b->upDate(y,w);
	}
	setFixedHeight(y);
}

void FilesTreeView::upDateWithData() {
	for (int i = 0; i < len; i++) {
		FilesTreeButton* b = treeButtons[i];
		b->setVirtualDisk(virtualDisk->at(i));
		b->upDateWithData();
	}
	upDate();
}

void FilesTreeView::setNewUseButton(FilesTreeButton* b) {

}

int FilesTreeView::getWidth() {
	return w;
}

void FilesTreeView::setWidth(int w) {
	this->w = w;
	upDate();
}