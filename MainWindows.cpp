#include "MainWindows.h"
#include <QDeBug>
#include <QLayout>
#include <QStorageInfo>

#pragma execution_character_set("utf-8")

MainWindows::MainWindows(QWidget *parent, FileStreamView* streamView, QList<VirtualDisk*>* vdl)
	: QWidget(parent)
{
	ui.setupUi(this);
	setObjectName("mainView");
	setStyleSheet("background-color:#ffffff;");
	this->streamView = streamView;

	topMenuView = new TopMenuView(this, width());
	topMenuView->setGeometry(0, 0, width(),26);
	topMenuView->show();

	lv = new LocationView(this);
	lv->setGeometry(0, 140, 800, 40);
	lv->show();

	fsv = new fileSenceView(this, vdl);
	fsv->setGeometry(0, 180, 800, 400);
	fsv->show();

	qDebug() << QDir::drives();

	QStorageInfo storage = QStorageInfo::root();
	shift = false;
	ctrl = false;
	alt = false;
	clipboard = QApplication::clipboard();
	lineEdit = NULL;
}

MainWindows::~MainWindows() {

}
fileSenceView* MainWindows::getFsv() {
	return fsv;
}

LocationView* MainWindows::getLv() {
	return lv;
}

bool MainWindows::getShift() {
	return shift;
}

void MainWindows::setLineEdit(QLineEdit* l) {
	lineEdit = l;
}
QLineEdit* MainWindows::getLineEdit() {
	return lineEdit;
}


void MainWindows::resizeEvent(QResizeEvent* size) {
	qDebug() << width();
	topMenuView->upDate(width());
	fsv->setSize(width(), height() - 180);
	lv->setSize(width(), 40);
}
void MainWindows::upDate(int w) {

}
void MainWindows::doSome() {
	qDebug() << "11";
}

void MainWindows::keyPressEvent(QKeyEvent* ev) {
	if (ev->key() == Qt::Key_Shift) {
		shift = true;
	}
	else if (ev->key() == Qt::Key_Control) {
		ctrl = true;
	}
	else if (ev->key() == Qt::Key_Alt) {
		alt = true;
	}
	else if (ev->key() == Qt::Key_Z) {
		if (ctrl) {
			this->ctrlZ();
		}
	}
	else if (ev->key() == Qt::Key_X) {
		if (ctrl) {
			this->ctrlX();
		}
	}
	else if (ev->key() == Qt::Key_C) {
		if (ctrl) {
			this->ctrlC();
		}
	}
	else if (ev->key() == Qt::Key_V) {
		if (ctrl) {
			this->ctrlV();
		}
	}
	else if (ev->key() == Qt::Key_Y) {
		if (ctrl) {
			this->ctrlY();
		}
	}
	else if (ev->key() == Qt::Key_A) {
		if (ctrl) {
			this->ctrlA();
		}
	}
	else if (ev->key() == Qt::Key_D) {
		if (ctrl) {
			this->ctrlD();
		}
	}
	else if (ev->key() == Qt::Key_Enter || ev->key() == Qt::Key_Return) {
		if (alt) {
			this->altEnter();
		}
	}
	else if (ev->key() == Qt::Key_N) {
		if (ctrl && shift) {
			this->ctrlShiftN();
		}
	}
	else if (ev->key() == Qt::Key_Delete) {
		if (shift) {
			this->shiftDel();
		}
	}
}
void MainWindows::keyReleaseEvent(QKeyEvent* ev) {
	if (ev->key() == Qt::Key_Shift) {
		shift = false;
	}
	else if (ev->key() == Qt::Key_Control) {
		ctrl = false;
	}
	else if (ev->key() == Qt::Key_Alt) {
		alt = false;
	}
}

void MainWindows::ctrlC() {
	qDebug() << "ctrl + c";
	if (lineEdit == NULL) {
		QMimeData* mimeData = new QMimeData();
		QList<QUrl> copyfile;
		fsv->getDfv()->setCopy(true);
		for (QString f : *(fsv->getDfv()->getList())) {
			if (fsv->getUh()->getVd()->getType() == DISK) {
				copyfile.push_back(QUrl::fromLocalFile(f));
			}
			else {
				copyfile.push_back(QUrl::fromLocalFile(f));
			}
			
		}
		mimeData->setUrls(copyfile);
		clipboard->setMimeData(mimeData);
	}
}
void MainWindows::ctrlV() {
	qDebug() << "ctrl + v";
	if (lineEdit == NULL) {
		QString workDir = "";
		if (fsv->getUh()->getVd()->getType() == DISK) {
			workDir = fsv->getUh()->getFiles()->getNetPath();
		}
		else {
			workDir = fsv->getUh()->getFiles()->getNetPath();
		}
		QList<QString> ps;
		for (QUrl i : clipboard->mimeData()->urls()) {
			ps.push_back(i.toLocalFile());
		}
		if (fsv->getDfv()->getCopy()) {
			streamView->newWork(FileStreamView::COPY, ps, workDir);
		}
		else {
			streamView->newWork(FileStreamView::RENAME, ps, workDir);
		}
	}
}
void MainWindows::ctrlZ() {
	qDebug() << "ctrl + z";
}
void MainWindows::ctrlY() {
	qDebug() << "ctrl + y";
}
void MainWindows::ctrlX() {
	qDebug() << "ctrl + x";
	if (lineEdit == NULL) {
		QMimeData* mimeData = new QMimeData();
		QList<QUrl> copyfile;
		fsv->getDfv()->setCopy(false);
		for (QString f : *(fsv->getDfv()->getList())) {
			copyfile.push_back(QUrl::fromLocalFile(f));
		}
		mimeData->setUrls(copyfile);
		clipboard->setMimeData(mimeData);
	}
}
void MainWindows::ctrlA() {
	qDebug() << "ctrl + a";
	fsv->getDfv()->chooseAll();
}
void MainWindows::ctrlD() {
	qDebug() << "ctrl + d";
	QList<QString> ps;
	for (QString f : *(fsv->getDfv()->getList())) {
		ps.push_back(f);
	}
	if (ps.size() > 0) {
		int result = QMessageBox::warning(this, "注意", "你确定将这" + QString::number(ps.size()) + "个项目放入回收站吗？", "是", "否");
		if (result == 0) {
			QString m = "";
			if (THIS_OS == WINDOWS) {
			}
			else if (THIS_OS == LINUX) {
				streamView->newWork(FileStreamView::RENAME, ps, m);

			}
		}
	}
}
void MainWindows::shiftDel() {
	qDebug() << "shift + del";
	QList<QString> ps;
	for (QString f : *(fsv->getDfv()->getList())) {
		ps.push_back(f);
	}
	if (ps.size() > 0) {
		int result = QMessageBox::warning(this, "注意", "你确定将这"+QString::number(ps.size())+"个项目销毁吗？这将不会放入回收站","是", "否");
		if (result == 0) {
			streamView->newWork(FileStreamView::DELET, ps, "");
		}
	}
}
void MainWindows::ctrlShiftN() {
	qDebug() << "ctrl + shift + n";
	QString workDir = fsv->getUh()->getFiles()->getNetPath();
	QDir dir(workDir);
	QString name = "新建文件夹";
	if (!dir.exists(name)) {
		dir.mkdir(name);
	}
	else {
		int i = 1;
		while (dir.exists(name + " (" + QString::number(i) + ")")) {
			i++;
		}
		dir.mkdir(name + " (" + QString::number(i) + ")");
	}
}
void MainWindows::altEnter() {
	qDebug() << "alt + Enter";
}