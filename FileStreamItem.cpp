#include "FileStreamItem.h"
#include "FileStreamView.h"
#include "FileWorker.h"


#pragma execution_character_set("utf-8")

FileStreamItem::FileStreamItem(QWidget *parent,int fWidth)
	: QWidget(parent)
{
	this->fWidth = fWidth;
	this->setStyleSheet("FileStreamItem{background:#ffffff;border-bottom:1px solid #b1cce3;}");
	workName = new QLabel(this);
	workName->setGeometry(20, 20, 100, 28);
	workName->show();
	mainWork = new QLabel(this);
	mainWork->setGeometry(20, 50, fWidth-140, 28);
	mainWork->show();
	workLv = new QLabel(this);
	workLv->setGeometry(20, 80, 400, 20);
	workLv->show();
	workSpeed = new QLabel(this);
	workSpeed->setGeometry(fWidth-120,80,100,20);
	workSpeed->setAlignment(Qt::AlignRight);
	workSpeed->show();
	f1 = new QFrame(this);
	f1->setGeometry(20,100,fWidth-40,40);
	f1->setStyleSheet("background:#ffffff;border:1px solid #b1cce3;");
	f1->show();
	f2 = new QFrame(this);
	f2->setGeometry(21, 101, 0, 38);
	f2->setStyleSheet("background:#e5f3ff;");
	f2->show();
	f3 = new QFrame(this);
	f3->setGeometry(21, 101, 0, 38);
	f3->setStyleSheet("background:#cde8ff;");
	f3->show();
	goonButton = new QPushButton(this);
	goonButton->setGeometry(fWidth - 120, 50, 18, 18);
	connect(goonButton, SIGNAL(clicked()), this, SLOT(goon()));
	goonButton->show();
	stopButton = new QPushButton(this);
	stopButton->setGeometry(fWidth - 120+22, 50, 18, 18);
	connect(stopButton, SIGNAL(clicked()), this, SLOT(stop()));
	stopButton->show();
	overButton = new QPushButton(this);
	overButton->setGeometry(fWidth - 120+44, 50, 18, 18);
	connect(overButton, SIGNAL(clicked()), this, SLOT(over()));
	overButton->show();
}

FileStreamItem::~FileStreamItem()
{
}

void FileStreamItem::stop() {
	fwr->doStop();
}

void FileStreamItem::over() {
	fwr->doOver();
}

void FileStreamItem::goon() {
	fwr->doGoon();
}

void FileStreamItem::setWorker(FileWorker* f) {
	fwr = f;
	if (f != NULL) {
		if (f->getMode() == FileStreamView::COPY) {
			mode = "复制";
		}
		else if (f->getMode() == FileStreamView::RENAME) {
			mode = "移动";
		}
		else if (f->getMode() == FileStreamView::DELET) {
			mode = "删除";
		}
	}
}

bool FileStreamItem::isUse() {
	if (fwr == NULL) {
		return false;
	}
	else {
		if (fwr->isRun()) {
			return true;
		}
		fwr = NULL;
		return false;
	}
}

void FileStreamItem::upDate() {
	if (!isUse()) { return; }
	workName->setText("正在执行"+ mode +"操作");
	if (!fwr->getDelete()) {
		mainWork->setText("从" + fwr->getWorkpath() + "到" + fwr->getMbPath());
		long long d = (fwr->getWorkFinishSize() - lastWorkSize) * 20;
		double lv = ((double)(fwr->getWorkFinishSize() * 10000 / fwr->getWorkSize())) / 100.0;
		workLv->setText(QString::number(fwr->getWorkFinishSize()) + "/" + QString::number(fwr->getWorkSize()) + "\t" + QString::number(lv, 'f', 2) + "%");
		workLv->adjustSize();
		workSpeed->setText(FileStringTools::getSize(d) + "/s");
		f2->setFixedWidth((fWidth - 42) * ((double)fwr->getFileFinishSize() / fwr->getFileSize()));
		f3->setFixedWidth((fWidth - 42) * lv/100);
		lastWorkSize = fwr->getWorkFinishSize();
	}
	else {
		int s = 0;
		
		if (lastFinishWorks == fwr->getFinishWorks()) {
			timeFinish += 50;
			s = lastDelNow;
		}
		else {
			s = fwr->getFinishWorks() - lastFinishWorks;
			timeFinish = 50;
		}
		mainWork->setText("从" + fwr->getWorkpath() + "中删除");
		workLv->setText(QString::number(fwr->getFinishWorks()) + "/" + QString::number(fwr->getAllWorks()) + "\t" + QString::number((double)fwr->getFinishWorks() / fwr->getAllWorks(), 'f', 2) + "%");
		workLv->adjustSize();
		workSpeed->setText(QString::number((double)s/(timeFinish/1000.0), 'f', 2)+"个/s");
		f2->setFixedWidth(0);
		f3->setFixedWidth((fWidth-42) * ((double)fwr->getFinishWorks() / fwr->getAllWorks()));
	}
	

}
