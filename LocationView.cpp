#include "LocationView.h"
#include "MainWindows.h"
#include "fileSenceView.h"
#include <QAction>

#pragma execution_character_set("utf-8")

LocationView::LocationView(QWidget *parent)
	: QWidget(parent)
{

	addressBarText = new QLineEdit(this);
	addressBarText->setGeometry(107, 5, 500, 23);
	addressBarText->setStyleSheet("QLineEdit{border:1px solid #d9d9d9;}"
		"QLineEdit::hover{border-color : #26a0da;}");
		
	connect(addressBarText, SIGNAL(returnPressed()),this,SLOT(upDate()));
	addressBarText->show();
	backButton = new YpButton(this,false);
	backButton->setMouseUnuseStyle("border-image:url(./images/LocationView/backButtonUnuse.png);");
	backButton->setMouseEnterStyle("border-image:url(./images/LocationView/backButtonOn.png);");
	backButton->setMouseLeaveStyle("border-image:url(./images/LocationView/backButtonOff.png);");
	backButton->setMouseChickStyle("border-image:url(./images/LocationView/backButtonDown.png);");
	backButton->setGeometry(14,11,12,12);
	connect(backButton, SIGNAL(leftChick()), this, SLOT(goBack()));
	backButton->show();
	backButton->useLeftChick(true);

	forwardButton = new YpButton(this, false);
	forwardButton->setMouseUnuseStyle("border-image:url(./images/LocationView/forwardButtonUnuse.png);");
	forwardButton->setMouseEnterStyle("border-image:url(./images/LocationView/forwardButtonOn.png);");
	forwardButton->setMouseLeaveStyle("border-image:url(./images/LocationView/forwardButtonOff.png);");
	forwardButton->setMouseChickStyle("border-image:url(./images/LocationView/forwardButtonDown.png);");
	forwardButton->setGeometry(44, 11, 12, 12);
	connect(forwardButton, SIGNAL(leftChick()), this, SLOT(goForward()));
	forwardButton->show();
	forwardButton->useLeftChick(true);

	upButton = new YpButton(this, false);
	upButton->setMouseUnuseStyle("border-image:url(./images/LocationView/upButtonUnuse.png);");
	upButton->setMouseEnterStyle("border-image:url(./images/LocationView/upButtonOn.png);");
	upButton->setMouseLeaveStyle("border-image:url(./images/LocationView/upButtonOff.png);");
	upButton->setMouseChickStyle("border-image:url(./images/LocationView/upButtonDown.png);");
	upButton->setGeometry(82, 5, 24, 23);
	connect(upButton, SIGNAL(leftChick()), this, SLOT(goParent()));
	upButton->show();
	upButton->setUsed();
	upButton->useLeftChick(true);

	historyButton = new YpButton(this, false);
	historyButton->setMouseEnterStyle("border-image:url(./images/LocationView/historyButtonOn.png);");
	historyButton->setMouseLeaveStyle("border-image:url(./images/LocationView/historyButtonOff.png);");
	historyButton->setMouseChickStyle("border-image:url(./images/LocationView/historyButtonDown.png);");
	historyButton->setGeometry(70, 14, 7, 5);
	historyButton->show();
	historyButton->setUsed();

	reloadButton = new YpButton(this, false);
	reloadButton->setMouseEnterStyle("border-image:url(./images/LocationView/reloadButtonOn.png);");
	reloadButton->setMouseLeaveStyle("border-image:url(./images/LocationView/reloadButtonOff.png);");
	reloadButton->setMouseChickStyle("border-image:url(./images/LocationView/reloadButtonDown.png);");
	reloadButton->setGeometry(600, 5, 18, 23);
	connect(reloadButton, SIGNAL(leftChick()), this, SLOT(reLoad()));
	reloadButton->show();
	reloadButton->setUsed();
	reloadButton->useLeftChick(true);


	searchText = new QLineEdit(this);
	searchText->setGeometry(615, 5, 180, 23);
	searchText->setStyleSheet("QLineEdit{border:1px solid #d9d9d9;}"
		"QLineEdit::hover{border-color : #26a0da;}");
	connect(searchText, SIGNAL(textEdited(QString)), this, SLOT(search(QString)));
	QAction* searchAction = new QAction(searchText);
	searchAction->setIcon(QIcon("./images/LocationView/search.png"));
	searchText->addAction(searchAction, QLineEdit::TrailingPosition);
	searchText->setPlaceholderText("搜索");
	searchText->show();

	historyList = new QList<QString>();
	hIndex = -1;
}

LocationView::~LocationView()
{
}

void LocationView::setSize(int w, int h) {
	this->setFixedWidth(w);
	if (w < 288) {
		this->hide();
	}
	else if (w < 434){
		this->show();
		addressBarText->setGeometry(107, 5, 200, 23);
		reloadButton->setGeometry(307, 5, 18, 23);
		searchText->setGeometry(335, 5, 100, 23);
	}
	else {
		this->show();
		addressBarText->setGeometry(107, 5, w-238, 23);
		reloadButton->setGeometry(w-131, 5, 18, 23);
		searchText->setGeometry(w - 105, 5, 100, 23);
	}
}

void LocationView::upDate() {
	QString str = addressBarText->text();
	((MainWindows*)(this->parent()))->getFsv()->openDir(str);
	if (addressBarText->hasFocus()) {
		addressBarText->clearFocus();
	}
}

void LocationView::reLoad() {
	QString str = addressBarText->text();
	((MainWindows*)(this->parent()))->getFsv()->openDir(str);
	if (addressBarText->hasFocus()) {
		addressBarText->clearFocus();
	}
	hIndex--;
	historyList->removeLast();
	if (hIndex == 0) {
		backButton->setUnused();
	}
	else {
		backButton->setUsed();
	}
	if (hIndex == historyList->size() - 1) {
		forwardButton->setUnused();
	}
	else {
		forwardButton->setUsed();
	}
}

void LocationView::newPath(QString s) {
	historyList->append(s+"|~:~|"+searchText->text().trimmed());
	hIndex++;
	if (hIndex == 0) {
		backButton->setUnused();
	}
	else {
		backButton->setUsed();
	}
	if (hIndex == historyList->size() - 1) {
		forwardButton->setUnused();
	}
	else {
		forwardButton->setUsed();
	}
	if (s != addressBarText->text()) {
		addressBarText->setText(s+"/");
	}
	searchText->setText("");
}

void LocationView::goParent() {
	QString str = addressBarText->text();
	QStringList sl = str.replace("://", "+:kk:+").split("/");
	if (sl.last().trimmed() == "") {
		sl.removeLast();
	}
	sl.removeLast();
	QString s = "";
	for each (QString v in sl) {
		s += (s != "" ? "/" : "") + v.replace("+:kk:+", "://");
	}
	((MainWindows*)(this->parent()))->getFsv()->openDir(s);
}

void LocationView::goBack() {
	hIndex--;
	QString s = historyList->at(hIndex);
	QStringList sl = s.split("|~:~|");

	((MainWindows*)(this->parent()))->getFsv()->openDir(sl[0]);
	hIndex--;
	historyList->removeLast();
	if (hIndex == 0) {
		backButton->setUnused();
	}
	else {
		backButton->setUsed();
	}
	if (hIndex == historyList->size() - 1) {
		forwardButton->setUnused();
	}
	else {
		forwardButton->setUsed();
	}
	search(sl[1]);
}

void LocationView::goForward() {
	hIndex++;
	QString s = historyList->at(hIndex);
	QStringList sl = s.split("|~:~|");
	((MainWindows*)(this->parent()))->getFsv()->openDir(sl[0]);
	hIndex--;
	historyList->removeLast();
	if (hIndex == 0) {
		backButton->setUnused();
	}
	else {
		backButton->setUsed();
	}
	if (hIndex == historyList->size() - 1) {
		forwardButton->setUnused();
	}
	else {
		forwardButton->setUsed();
	}
	search(sl[1]);

}

void LocationView::newHistory() {
	QList<QString>* historyList_ = new QList<QString>();
	for (int i = 0; i <= hIndex; i++) {
		historyList_->append(historyList->at(i));
	}
	delete historyList;
	historyList = historyList_;
}

void LocationView::search(QString s) {
	s = s.trimmed();
	if (s == "") { ((MainWindows*)(this->parent()))->getFsv()->getDfv()->notSearch(); return; }
	((MainWindows*)(this->parent()))->getFsv()->getDfv()->search(
	((MainWindows*)(this->parent()))->getFsv()->getUh()->search(s));

}
