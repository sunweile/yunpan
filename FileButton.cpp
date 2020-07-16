#include "FileButton.h"
#include "DetailedFileView.h"

#include "MainWindows.h"

#pragma execution_character_set("utf-8")

FileButton::FileButton(QWidget*parent)
	: QFrame(parent)
{
	nameEdit = new QLineEdit(this);
	nameEdit->setFont(QFont("微软雅黑", 10, 50));
	//nameEdit->installEventFilter(this);
	connect(nameEdit, SIGNAL(returnPressed()), this, SLOT(nameEditReturn()));
	nameEdit->adjustSize();
	nameEdit->hide();
	

	fileName = new QLabel(this);
	fileName->setFont(QFont("微软雅黑", 10, 50));
	fileName->installEventFilter(this);
	fileName->setAttribute(Qt::WA_TranslucentBackground);

	fileImage = new QLabel(this);
	fileImage->setAttribute(Qt::WA_TranslucentBackground);

	fileDate = new QLabel(this);
	fileDate->setGeometry(740, 7, 300, 18);
	fileDate->setAttribute(Qt::WA_TranslucentBackground);

	fileDateLabel = new QLabel(this);
	fileDateLabel->setText("修改日期：");
	fileDateLabel->setGeometry(660, 7, 80, 18);
	fileDateLabel->setAttribute(Qt::WA_TranslucentBackground);

	fileType = new QLabel(this);
	fileType->setGeometry(380, 7, 300, 18);
	fileType->setAttribute(Qt::WA_TranslucentBackground);

	fileTypeLabel = new QLabel(this);
	fileTypeLabel->setText("类型：");
	fileTypeLabel->setGeometry(330, 7, 50, 18);
	fileTypeLabel->setAttribute(Qt::WA_TranslucentBackground);

	fileSize = new QLabel(this);
	fileSize->setGeometry(710, 28, 300, 18);
	fileSize->setAttribute(Qt::WA_TranslucentBackground);

	fileSizeLabel = new QLabel(this);
	fileSizeLabel->setText("大小：");
	fileSizeLabel->setGeometry(660, 28, 50, 18);
	fileSizeLabel->setAttribute(Qt::WA_TranslucentBackground);
	mode = 0;

	fileName->hide();
	fileImage->hide();
	fileDate->hide();
	fileDateLabel->hide();
	fileType->hide();
	fileTypeLabel->hide();
	fileSize->hide();
	fileSizeLabel->hide();
	isUse = false;
	isChoose = false;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(click()));
	time = 0;
	file = "";
}

FileButton::~FileButton()
{
}

int FileButton::setFile(VirtualDisk::fileTree* file, int mode) {
	VirtualDisk::fileTree file_ = *file;
	isUse = false;
	isChoose = false;
	this->file = file_.getNetPath();
	this->mode = mode;
	fileDate->hide();
	fileDateLabel->hide();
	fileType->hide();
	fileTypeLabel->hide();
	fileSize->hide();
	fileSizeLabel->hide();
	fileName->setText(file_.name);
	nameEdit->setText(file_.name);

	long long size = file_.size;
	fileSize->setText(FileStringTools::getSize(size));
	QFileIconProvider fp;
	QIcon file_icon;
	QIcon qi;
	QIcon fi;
	switch (file_.type)
	{
	case DIR:
		fileType->setText("文件夹");
		fi = FileButton::IconsMap->value("<DIR>", qi);
		if (fi.isNull()) {
			file_icon = fp.icon(QFileInfo(this->file));
			FileButton::IconsMap->insert("<DIR>", file_icon);
		}
		else {
			file_icon = fi;
		}
		break;
	default:
		QStringList fns = file_.name.split(".");
		if (fns.size() > 1) {
			fi = FileButton::IconsMap->value(file_.name.split(".").last(),qi);
			if (fi.isNull()) {
				if (QFile(this->file).exists()) {
					file_icon = fp.icon(QFileInfo(this->file));
					FileButton::IconsMap->insert(file_.name.split(".").last(), file_icon);
				}
				else {
				
				}
			}
			else {
				file_icon = fi;
			}
			QString fn = FileStringTools::getFileType(fns.last());
			fileType->setText(fn);
		}
		else {
			fi = FileButton::IconsMap->value("<FILE>",qi);
			if (fi.isNull()) {
				if (QFile(this->file).exists()) {
					file_icon = fp.icon(QFileInfo(this->file));
					FileButton::IconsMap->insert("<FILE>", file_icon);
				}
				else {
				
				}
			}
			else {
				file_icon = fi;
			}
			QString fn = FileStringTools::getFileType(fns.last());
			fileType->setText("文件");
		}
		break;
	}
	qDebug() << this->file;
	
	qDebug() << file_icon;
	int m = 16 << (4-mode);
	if (mode == 0) {
		m = 256;
	}
	else if (mode == 1) {
		m = 32;
	}
	else if (mode == 2 || mode == 3) {
		m = 16;
	}
	QPixmap f = file_icon.pixmap(m, m);
	qDebug() << this->file;

	int w = f.width();
	int h = f.height();
	qDebug() << m;
	fileImage->setPixmap(f);
	fileImage->show();
	switch (mode){
	case 0: {//超大
		fileName->setLineWidth(m);
		fileName->adjustSize();
		fileImage->setGeometry((m-w)/2, (m - h) / 2, w, h);
		fileName->setGeometry((m - fileName->width()) / 2, m, fileName->width(), fileName->height());
		fileName->show();
		return m + fileName->height() + 24;
	}
	case 1: {//内容
		setStyleSheet("FileButton{background:#ffffff;border-bottom:1px solid #dcdcdc;}");
		fileName->setLineWidth(m);
		fileImage->setGeometry(3, 7, w, h);
		fileName->setGeometry(42, 1, 270, 20);
		fileName->adjustSize();
		nameEdit->setGeometry(42, 1, fileName->width(), fileName->height());
		nameEdit->adjustSize();
		fileName->show();
		fileDateLabel->show();
		fileDate->show();
		fileDate->setText(file->date);
		if (file->type != DIR) {
			fileSizeLabel->show();
			fileSize->show();
			fileType->show();
			fileTypeLabel->show();
		}
		return 50;
	}
	case 2: {//小
		fileName->setLineWidth(m);
		fileName->setWordWrap(false);
		fileImage->setGeometry(3, 3, w, h);
		fileName->setGeometry(22, 1, 270, 20);
		fileName->show();
		return 22;
	}
	default:
		break;
	}
	//fileDate->setText(file->date);
	return 300;
}

void FileButton::enterEvent(QEvent* event) {
	if (mode == 0) {
		setStyleSheet("FileButton{background:#e5f3ff;}");
	}
	else if (mode == 1) {
		if (!isUse) {
			if (isChoose) {
				setStyleSheet("FileButton{background:#cde8ff;border-bottom:1px solid #b1cce3;border-left:1px solid #b1cce3;border-right:1px solid #b1cce3;}");
			}
			else {
				setStyleSheet("FileButton{background:#e5f3ff;border-bottom:1px solid #dcdcdc;}");
			}
		}
		else {
			if (isChoose) {
				setStyleSheet("FileButton{background:#cde8ff;border-bottom:1px solid #b1cce3;border-left:1px solid #b1cce3;border-right:1px solid #b1cce3;}");
			}
			else {
				setStyleSheet("FileButton{background:#e5f3ff;border-bottom:1px solid #dcdcdc;}");
			}
		}
	}
	else if (mode == 2) {
		setStyleSheet("FileButton{background:#e5f3ff;}");
	}
}
void FileButton::leaveEvent(QEvent* event) {
	if (mode == 0) {
		setStyleSheet("FileButton{background:#ffffff;}");
	}
	else if (mode == 1) {
		if (!isUse) {
			if (isChoose) {
				setStyleSheet("FileButton{background:#cde8ff;border-bottom:1px solid #dcdcdc;}");
			}
			else {			
				setStyleSheet("FileButton{background:#ffffff;border-bottom:1px solid #dcdcdc;}");
			}
		}
		else {
			if (isChoose) {
				setStyleSheet("FileButton{background:#cde8ff;border-bottom:1px solid #b1cce3;border-left:1px solid #b1cce3;border-right:1px solid #b1cce3;}");
			}
			else {
				setStyleSheet("FileButton{background:#ffffff;border-bottom:1px solid #b1cce3;border-left:1px solid #b1cce3;border-right:1px solid #b1cce3;}");
			}
		}
	}
	else if (mode == 2) {
		setStyleSheet("FileButton{background:#ffffff;}");
	}
}
void FileButton::mouseReleaseEvent(QMouseEvent* event) {
	QObject* f = parent();
	while (f->parent() != NULL) {
		f = f->parent();
	}
	if (((MainWindows*)f)->getShift()) {
		isChoose = true;
		((DetailedFileView*)parent())->otherUse(this);
	}
	else {
		((DetailedFileView*)parent())->otherUnUse(this);
		((DetailedFileView*)parent())->setUsed(this);
		isUse = true;
		isChoose = true;
	}
	if (mode == 0) {
		setStyleSheet("FileButton{background:#cde8ff;border:1px solid #b1cce3;}");
	}
	else if (mode == 1) {
		setStyleSheet("FileButton{background:#cde8ff;border-bottom:1px solid #b1cce3;border-left:1px solid #b1cce3;border-right:1px solid #b1cce3;}");
	}
	else if (mode == 2) {
		setStyleSheet("FileButton{background:#cde8ff;border:1px solid #b1cce3;}");
	}
}
void FileButton::mousePressEvent(QMouseEvent* event) {
	if (!timer->isActive()) {
		time = 0;
		timer->start(100);
	}
	else {
		timer->stop();
		time = 0;
		if (time <= 4) {
			((DetailedFileView*)(this->parent()))->open(file);
		}
	}
	
	if (mode == 0) {
		setStyleSheet("FileButton{background:#d8eaf9;}");
	}
	else if (mode == 1) {
		if (!isUse) {
			setStyleSheet("FileButton{background:#d8eaf9;border-bottom:1px solid #dcdcdc;}");
		}
	}
	else if (mode == 2) {
		setStyleSheet("FileButton{background:#d8eaf9;}");
	}
}
void FileButton::focusOut() {
	setStyleSheet("FileButton{background:#ffffff;border-bottom:1px solid #dcdcdc;}");
	isUse = false;
	isChoose = false;
}

void FileButton::focusOutChoose() {
	if (isUse) {
		setStyleSheet("FileButton{background:#ffffff;border-bottom:1px solid #b1cce3;border-left:1px solid #b1cce3;border-right:1px solid #b1cce3;}");
	}
	else {
		setStyleSheet("FileButton{background:#ffffff;border-bottom:1px solid #dcdcdc;}");
	}
	isChoose = false;
}

void FileButton::click() {
	time++;
	if (time == 5) {
		timer->stop();
		time = 0;
	}
}

void FileButton::choose() {
	setStyleSheet("FileButton{background:#cde8ff;border-bottom:1px solid #dcdcdc;}");
	isChoose = true;
}

void FileButton::use() {

	isUse = true;
}

void FileButton::unUse() {
	isUse = false;
}

void FileButton::unChoose() {
	isChoose = false;
}

QString FileButton::getFile() {
	return file;
}

bool FileButton::eventFilter(QObject* obj, QEvent* event) {
	if (obj == fileName) {
		if (isChoose && event->type() == QEvent::MouseButtonPress) {
			QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
			if (mouseEvent->button() == Qt::LeftButton){
				QObject* f = parent();
				while (f->parent() != NULL) {
					f = f->parent();
				}
				((MainWindows*)f)->setLineEdit(nameEdit);
				fileName->hide();
				nameEdit->show();
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else if (obj == nameEdit) {
		if (event->type() == QEvent::FocusOut) {
			QObject* f = parent();
			while (f->parent() != NULL) {
				f = f->parent();
			}
			if (((MainWindows*)f)->getLineEdit() == nameEdit) {
				nameEditReturn();
			}
		}
	}
	return QFrame::eventFilter(obj, event);
}

void FileButton::nameEditReturn() {
	QObject* f = parent();
	while (f->parent() != NULL) {
		f = f->parent();
	}
	((MainWindows*)f)->setLineEdit(NULL);
	fileName->setText(nameEdit->text());
	nameEdit->hide();
	fileName->show();
	((DetailedFileView*)parent())->getUh()->rename(file, nameEdit->text());
}