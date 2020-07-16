#include "TopMenuView.h"
#pragma execution_character_set("utf-8")
TopMenuView::TopMenuView(QWidget *parent,int w)
	: QFrame(parent)
{
	mainButton = new YpButton(this, false);
	mainButton->show();
	mainButton->setGeometry(0, 0, 52, 26);
	mainButton->setMouseLeaveStyle("border-image:url(./images/TopMain/topMenuMainButtonOff.png);");
	mainButton->setMouseChickStyle("border-image:url(./images/TopMain/topMenuMainButtonDown.png);");
	mainButton->setMouseEnterStyle("border-image:url(./images/TopMain/topMenuMainButtonOn.png);");
	mainButton->useActivation(true);
	mainButton->setUsed();
	connect(mainButton, SIGNAL(leftChick()), this, SLOT(mianButtonChick()));
	//connect(mainButton, SIGNAL(focusOut()), this, SLOT(mianButtonFocusOut()));
	shareButton = new YpButton(this, false);
	shareButton->show();
	shareButton->setGeometry(53, 0, 52, 26);
	shareButton->setMouseLeaveStyle("border-image:url(./images/TopMain/topMenuShareButtonOff.png);");
	shareButton->setMouseChickStyle("border-image:url(./images/TopMain/topMenuShareButtonDown.png);");
	shareButton->setMouseEnterStyle("border-image:url(./images/TopMain/topMenuShareButtonOn.png);");
	shareButton->useActivation(true);
	shareButton->setUsed();
	connect(shareButton, SIGNAL(leftChick()), this, SLOT(shareButtonChick()));
	//connect(shareButton, SIGNAL(focusOut()), this, SLOT(shareButtonFocusOut()));
	showButton = new YpButton(this, false);
	showButton->show();
	showButton->setGeometry(106, 0, 52, 26);
	showButton->setMouseLeaveStyle("border-image:url(./images/TopMain/topMenuShowButtonOff.png);");
	showButton->setMouseChickStyle("border-image:url(./images/TopMain/topMenuShowButtonDown.png);");
	showButton->setMouseEnterStyle("border-image:url(./images/TopMain/topMenuShowButtonOn.png);");
	showButton->useActivation(true);
	showButton->setUsed();
	connect(showButton, SIGNAL(leftChick()), this, SLOT(showButtonChick()));
	//connect(showButton, SIGNAL(focusOut()), this, SLOT(showButtonFocusOut()));
	mainView = NULL;
	filesView = NULL;
	shareView = NULL;
	showView = NULL;
}

TopMenuView::~TopMenuView()
{
}
void TopMenuView::upDate(int w) {
	this->setGeometry(0, 0, ((QWidget*)parent())->width(), 26);
	this->show();

	if (w >= 798) {//剪贴板 全，组织 全，新建 全，打开 全，选择 全
		this->show();
	}else if (w >= 744) {//剪贴板 全，组织 全，新建 小图标无字，打开 全，选择 全
		this->show();
	}else if (w >= 710) {//剪贴板 全，组织 小图标，新建 小图标无字，打开 全，选择 全
		this->show();
	}else if (w >= 668) {//剪贴板 全，组织 小图标，新建 小图标无字，打开 小图标无字，选择 全
		this->show();
	}else if (w >= 584) {//剪贴板 小图标无字，组织 小图标，新建 小图标无字，打开 小图标无字，选择 全
		this->show();
	}else if (w >= 545) {//剪贴板 小图标无字，组织 小图标，新建 小图标无字，打开 小图标无字，选择 下拉图标
		this->show();
	}else if (w >= 473) {//剪贴板 小图标无字，组织 小图标无字，新建 小图标无字，打开 小图标无字，选择 下拉图标
		this->show();
	}else if (w >= 434) {//剪贴板 小图标无字，组织 小图标无字，新建 下拉图标，打开 小图标无字，选择 下拉图标
		this->show();
	}else if (w >= 393) {//剪贴板 小图标无字，组织 小图标无字，新建 下拉图标，打开 下拉图标，选择 下拉图标
		this->show();
	}else if (w >= 356) {//剪贴板 小图标无字，组织 下拉图标，新建 下拉图标，打开 下拉图标，选择 下拉图标
		this->show();
	}else if (w >= 288) {//剪贴板 下拉图标，组织 下拉图标，新建 下拉图标，打开 下拉图标，选择 下拉图标
		this->show();
	}else {//不显示
		this->hide();
	}
	
}
void TopMenuView::resizeEvent(QResizeEvent* size) {
	if (mainView != NULL) {
		mainView->setGeometry(0, 26, width(), 109);
		mainView->setStyleSheet("background-color:#f5f6f7;border:1px solid #dadbdc;");
	}
}
void TopMenuView::filesButtonFocusOut() {
	if (filesView != NULL) {
		filesView->hide();
	}
}
void TopMenuView::mianButtonFocusOut() {
	if (mainView != NULL) {
		mainView->hide();
	}
}
void TopMenuView::shareButtonFocusOut() {
	if (shareView != NULL) {
		shareView->hide();
	}
}
void TopMenuView::showButtonFocusOut() {
	if (showView != NULL) {
		showView->hide();
	}
}


void TopMenuView::filesButtonChick() {
	if (type == File) { return; }
}

void TopMenuView::mianButtonChick() {
	if (type == Main) { return; }
	if (filesView != NULL && filesView->isVisible()) { filesView->hide(); }
	if (shareView != NULL && shareView->isVisible()) { shareView->hide(); }
	if (showView != NULL && showView->isVisible()) { showView->hide(); }
	if (mainView == NULL) {
		mainView = new TopMainMenu(NULL, (QWidget*)parent());
		mainView->setGeometry(0, 27, width(), 109);
		mainView->setStyleSheet("background-color:#f5f6f7;border:1px solid #dadbdc;");
		mainView->show();
		return;
	}
	mainView->setGeometry(0, 27, width(), 109);
	mainView->setStyleSheet("background-color:#f5f6f7;border:1px solid #dadbdc;");
	mainView->show();
}

void TopMenuView::shareButtonChick() {
	if (type == Share) { return; }
	if (filesView != NULL && filesView->isVisible()) { filesView->hide(); }
	if (mainView != NULL && mainView->isVisible()) { mainView->hide(); }
	if (showView != NULL && showView->isVisible()) { showView->hide(); }
}

void TopMenuView::showButtonChick() {
	if (type == Show) { return; }
	if (filesView != NULL && filesView->isVisible()) { filesView->hide(); }
	if (mainView != NULL && mainView->isVisible()) { mainView->hide(); }
	if (shareView != NULL && shareView->isVisible()) { shareView->hide(); }
}