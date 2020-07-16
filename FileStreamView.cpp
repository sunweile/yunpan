#include "FileStreamView.h"
#include "FileWorker.h"
#include "FileStreamItem.h"


#pragma execution_character_set("utf-8")

FileStreamView::FileStreamView(QWidget *parent)
	: QWidget(parent)
{
	itemList = new QList<FileStreamItem*>();
	worker = new QList<FileWorker*>();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(upDate()));
	timer->start(50);
	doCleanMax = 100;
	doClean = 0;
}

FileStreamView::~FileStreamView()
{
}
void FileStreamView::setVdl(QList<VirtualDisk*>* vdl) {
	this->vdl = vdl;
}

void FileStreamView::newWork(WorkType t, QList<QString> paths, QString mb) {
	FileWorker* w = NULL;
	for (auto i : *worker) {
		if (!i->isRun()) {
			w = i;
			break;
		}
	}
	if (w == NULL) {
		w = new FileWorker(this);
		w->setVdl(vdl);
		worker->push_back(w);
	}
	QStringList sl;
	sl.push_back(w->getVd(paths[0])->getTypeName());
	sl.push_back(w->getVd(mb)->getTypeName());
	w->setNewWork(t, paths, mb,sl);
	FileStreamItem* m = NULL;
	for (auto i : *itemList) {
		if (!i->isUse()) {
			m = i;
			break;
		}
	}
	if (m == NULL) {
		m = new FileStreamItem(this, width());
		m->fWidth = width();
		itemList->push_back(m);
	}
	m->setWorker(w);
}

void FileStreamView::upDate() {
	int y = 0;
	for (auto i : *itemList) {
		if (i->isUse()) {
			i->fWidth = width();
			i->upDate();
			i->setGeometry(0,y,width(),115);
			i->show();
			y += 150;
		}
		else {
			i->hide();
		}
	}
	if (y > 0) {
		this->setFixedHeight(y);
		this->setFixedWidth(width());
		this->show();
	}
	else {
		this->hide();
	}
	if (doCleanMax == ++doClean) {
		doClean = 0;
		while (worker->size() > 5 && !worker->last()->isRun()) {
			delete worker->last();
			worker->removeLast();
		}
		while (itemList->size() > 5 && !itemList->last()->isUse()) {
			delete itemList->last();
			itemList->removeLast();
		}
	}
}

void FileStreamView::closeEvent(QCloseEvent* e) {
	for (auto i : *itemList) {
		if (i->isUse()) {
			i->stop();
		}
	}
	int result = QMessageBox::warning(this, "注意", "关闭将中止所有任务", "是", "否");
	if (result == 0) {
		for (auto i : *itemList) {
			if (i->isUse()) {
				i->over();
			}
		}
		this->hide();
		e->ignore();
	}else if (result == 1){
		for (auto i : *itemList) {
			if (i->isUse()) {
				i->goon();
			}
		}
		e->ignore();
	}
	e->ignore();
}
