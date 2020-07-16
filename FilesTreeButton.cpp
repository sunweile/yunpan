#include "FilesTreeButton.h"

#include "FilesTreeView.h"
#include "fileSenceView.h"
#include "LoginDialog.h"

#pragma execution_character_set("utf-8")

FilesTreeButton::FilesTreeButton(QWidget* parent, FilesTreeButton* dirParentButton, QString name)
	: QFrame(parent)
{
	this->dirParentButton = dirParentButton;
	this->name = name;
	this->isRun = false;
	this->isUse = false;
	this->pname = "";
	height = 30;
	type = DIR;
	pname = "";
	line = dirParentButton == NULL ? 0 : (dirParentButton->line + 1);
	dirButton = new QLabel(this);
	dirButton->setText(name);
	dirButton->setGeometry(40+line*8, 0, 400, 20);
	dirButton->setAttribute(Qt::WA_TranslucentBackground);
	dirButton->show();
	moreDirsButton = new YpButton(this,false);
	moreDirsButton->setGeometry(line*8+18, 8, 9, 9);
	moreDirsButton->setUsed();
	moreDirsButton->useLeftDown(true);
	moreDirsButton->show();
	connect(moreDirsButton, SIGNAL(leftDown()), this, SLOT(moreDirsButtonChick()));
	dirButtons = new QList<FilesTreeButton*>();
	vd = NULL;
	needLogin = false;
}

FilesTreeButton::FilesTreeButton(QWidget* parent, FilesTreeButton* dirParentButton, QString name, QString pname)
	: QFrame(parent)
{
	this->dirParentButton = dirParentButton;
	this->name = name;
	this->isRun = false;
	this->isUse = false;
	height = 30;
	type = DIR;
	this->pname = pname;
	line = dirParentButton == NULL ? 0 : (dirParentButton->line + 1);
	dirButton = new QLabel(this);
	dirButton->setText(pname);
	dirButton->setGeometry(40 + line * 8, 0, 400, 20);
	dirButton->setAttribute(Qt::WA_TranslucentBackground);
	dirButton->show();
	moreDirsButton = new YpButton(this, false);
	moreDirsButton->setGeometry(line * 8 + 18, 8, 9, 9);
	moreDirsButton->setUsed();
	moreDirsButton->useLeftDown(true);
	moreDirsButton->show();
	connect(moreDirsButton, SIGNAL(leftDown()), this, SLOT(moreDirsButtonChick()));
	dirButtons = new QList<FilesTreeButton*>();
	vd = NULL;
	needLogin = false;

}

FilesTreeButton::~FilesTreeButton()
{
}
void FilesTreeButton::setIsRun(bool b) {
	isRun = b;
}
FilesTreeView* FilesTreeButton::getTreeView() {
	return (FilesTreeView*)(this->parent());
}
QString FilesTreeButton::getPath() {
	FilesTreeButton* f = this;
	QString str = "";
	while (f != NULL) {
		if (str != "") {
			str = f->name + "/" + str;
		}
		else {
			str = f->name;
		}
		f = f->dirParentButton;
	}
	return str;
}
void FilesTreeButton::cleanDirs() {
	int s = dirButtons->size();
	if (s > 0) {
		for (int i = 0; i < s; i++) {
			dirButtons->at(i)->hide();
			dirButtons->at(i)->cleanDirs();
			delete dirButtons->at(i)->dirButtons;
			delete dirButtons->at(i);
		}
	}
}
void FilesTreeButton::hideDirs() {
	int s = dirButtons->size();
	if (s > 0) {
		for (int i = 0; i < s; i++) {
			dirButtons->at(i)->hide();
			dirButtons->at(i)->hideDirs();
		}
	}
}
void FilesTreeButton::killDirs() {
	cleanDirs();
	delete dirButtons;
	dirButtons = NULL;
	this->hide();
	delete this;
}

int FilesTreeButton::upDate(int y, int w) {
	int y_ = y;
	this->setGeometry(0, y_, w, height);
	this->show();
	y_ += height;
	if (this->isRun) {
		for (int i = 0; i < dirButtons->size(); i++) {
			y_ += dirButtons->at(i)->upDate(y_, w);
		}
		if (vd->getDir(this->getPath())->size()) {
			moreDirsButton->show();
			moreDirsButton->setBackgroundRole(this->backgroundRole());
			
			moreDirsButton->setMouseChickStyle("border-image:url(./images/MoreDirButtonDownOn.png);");
			moreDirsButton->setMouseEnterStyle("border-image:url(./images/MoreDirButtonDownOn.png);");
			moreDirsButton->setMouseLeaveStyle("border-image:url(./images/MoreDirButtonDownOff.png);");
			
		}
		else {
			moreDirsButton->hide();
		}
	}
	else {
		if (vd->getDir(this->getPath())->size()) {
			moreDirsButton->show();
			moreDirsButton->setBackgroundRole(this->backgroundRole());
			moreDirsButton->setMouseChickStyle("border-image:url(./images/MoreDirButtonOn.png);");
			moreDirsButton->setMouseEnterStyle("border-image:url(./images/MoreDirButtonOn.png);");
			moreDirsButton->setMouseLeaveStyle("border-image:url(./images/MoreDirButtonOff.png);");
		}
		else {
			moreDirsButton->hide();
		}
		hideDirs();
		
	}
	
	return y_-y;
}

void FilesTreeButton::upDateWithData() {
	this->vd = vd;
	QStringList* sl = vd->getDir(this->getPath());
	int len = dirButtons->size();
	if (sl != NULL) {
		QStringList sls;
		for each (QString s in *sl){
			bool b = false;
			for (int i = 0; i < len; i++) {
				if (dirButtons->at(i)->name == s) {
					b = true;
					break;
				}
			}
			if (!b) {
				if (!sls.contains(s)) {
					sls.append(s);
				}
			}
		}
		for (int i = 0; i < len; i++) {
			if (!sl->contains(dirButtons->at(i)->name)) {
				dirButtons->at(i)->killDirs();
			}
		}
		QList<FilesTreeButton*>* tbs = new QList<FilesTreeButton*>();
		for (int i = 0; i < sls.size(); i++) {
			tbs->push_back(new FilesTreeButton((QWidget*)parent(), this, sls.at(i)));
			tbs->last()->setVirtualDisk(vd);
		}
		int j = 0;
		for each (QString s in *sl) {
			for (int i = 0; i < len; i++) {
				if (dirButtons->at(i) != NULL && dirButtons->at(i)->name == s) {
					tbs->push_back(dirButtons->at(i));
					break;
				}
			}
		}
		dirButtons->clear();
		delete dirButtons;
		delete sl;
		dirButtons = tbs;
	}
	
}

void FilesTreeButton::enterEvent(QEvent* event) {
	if (isUse) {
		setStyleSheet("background-color:#cce8ff;");
	}else {
		setStyleSheet("background-color:#e5f3ff;");
	}
}
void FilesTreeButton::leaveEvent(QEvent* event) {
	if (isUse) {
		setStyleSheet("background-color:#cce8ff;");
	}else {
		setStyleSheet("background-color:#ffffff;");
	}
}
void FilesTreeButton::focusOut() {
	if (isUse) {
		setStyleSheet("background-color:#d9d9d9;");
	}
}

void FilesTreeButton::focusIn() {
	if (isUse) {
		setStyleSheet("background-color:#cce8ff;");
	}
}
void FilesTreeButton::setVirtualDisk(VirtualDisk* vd) {
	this->vd = vd;
}

void FilesTreeButton::mouseReleaseEvent(QMouseEvent* event) {
	// 鼠标左键松开
	if (event->button() == Qt::LeftButton) {
		if (this->type == DIR) {
			if (needLogin) {
				needButtonChick();
			}
			else {
				((fileSenceView*)(this->parent()->parent()->parent()->parent()))->openDir(this->getPath());
			}
		}
		else {
			
		}
	}
}

void FilesTreeButton::moreDirsButtonChick() {
	isUse = !isUse;
	isRun = !isRun;
	this->upDateWithData();
	((FilesTreeView*)parent())->upDate();
	((FilesTreeView*)parent())->setNewUseButton(this);
	setStyleSheet("background-color:#cce8ff;");
}

void FilesTreeButton::setNeedLogin() {
	if (!needLogin) {
		needLogin = true;
		dirButton->setText((pname == "" ? name: pname) + " (需要登录)");
	}
}

void FilesTreeButton::notNeedLogin() {
	if (needLogin) {
		needLogin = false;
		dirButton->setText((pname == "" ? name : pname));
	}
}

void FilesTreeButton::needButtonChick() {
	LoginDialog l("");
	if (l.exec() == 0) {
		QStringList sl = l.getStr();
		QStringList data;
		if (sl[1].toUpper() == "SUCCESS") {
			
			data.push_back((pname == "" ? name : pname));
			QString t = sl[0].toUpper();
			if (t == "BAIDU") {
				data.push_back("4");
			}
			data.push_back("");
			for (int i = 2; i < sl.size(); i++) {
				data.push_back(sl[i]);
			}
			((fileSenceView*)(this->parent()->parent()->parent()->parent()))->setLogin(data);
		}
	}
}