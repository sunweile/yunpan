#include "TopMainMenu.h"
#pragma execution_character_set("utf-8")
TopMainMenu::TopMainMenu(UserHandle* userHandle, QWidget* parent)
	: QFrame(parent)
{
	ksfwButton = NULL;
	fzButton = NULL;
	ztButton = NULL;
	jqButton = NULL;
	fzljButton = NULL;
	ztkjfsButton = NULL;
	ztbLabel = NULL;
	line1 = NULL;

	moveToButton = NULL;
	copyToButton = NULL;
	line1_1 = NULL;
	removeButton = NULL;
	renameButton = NULL;
	zzLabel = NULL;
	line2 = NULL;

	xwjjButton = NULL;
	xxmButton = NULL;
	qsfwButton = NULL;
	xjLabel = NULL;
	line3 = NULL;

	sxButton = NULL;
	openButton = NULL;
	bjButton = NULL;
	lsjlButton = NULL;
	dkLabel = NULL;
	line4 = NULL;

	qxButton = NULL;
	qxxzButton = NULL;
	fxButton = NULL;
	xzLabel = NULL;
	line5 = NULL;

	ztbButton = NULL;
	zzButton = NULL;
	xjButton = NULL;
	dkButton = NULL;
	xzButton = NULL;

	this->userHandle = userHandle;
	upDate(true);
}

TopMainMenu::~TopMainMenu(){
	delete ksfwButton;
	delete fzButton;
	delete ztButton;
	delete jqButton;
	delete fzljButton;
	delete ztkjfsButton;
	delete ztbLabel;
	delete line1;
	delete moveToButton;
	delete copyToButton;
	delete line1_1;
	delete removeButton;
	delete renameButton;
	delete zzLabel;
	delete line2;
	delete xwjjButton;
	delete xxmButton;
	delete qsfwButton;
	delete xjLabel;
	delete line3;
	delete sxButton;
	delete openButton;
	delete bjButton;
	delete lsjlButton;
	delete dkLabel;
	delete line4;
	delete qxButton;
	delete qxxzButton;
	delete fxButton;
	delete xzLabel;
	delete line5;
}

void TopMainMenu::upDate(bool isNow = false) {
	int w = ((QWidget*)(this->parent()))->width();
	if (isNow) {
		this->setStyleSheet("background-color:#f5f6f7;border:1px solid #dadbdc;");
	}
	if (w < 288) {
		this->hide();
	}
	
	ksfwButtonUpDate(w);
	fzButtonUpDate(w);
	ztButtonUpDate(w);
	jqButtonUpDate(w);
	fzljButtonUpDate(w);
	ztkjfsButtonUpDate(w);
	ztbLabelUpDate(w);
	line1UpDate(w);

	moveToButtonUpDate(w);
	copyToButtonUpDate(w);
	line1_1UpDate(w);
	removeButtonUpDate(w);
	renameButtonUpDate(w);
	zzLabelUpDate(w);
	line2UpDate(w);

	xwjjButtonUpDate(w);
	xxmButtonUpDate(w);
	qsfwButtonUpDate(w);
	xjLabelUpDate(w);
	line3UpDate(w);

	sxButtonUpDate(w);
	openButtonUpDate(w);
	bjButtonUpDate(w);
	lsjlButtonUpDate(w);
	dkLabelUpDate(w);
	line4UpDate(w);

	qxButtonUpDate(w);
	qxxzButtonUpDate(w);
	fxButtonUpDate(w);
	xzLabelUpDate(w);
	line5UpDate(w);

	ztbButtonUpdate(w);
	zzButtonUpdate(w);
	xjButtonUpdate(w);
	dkButtonUpdate(w);
	xzButtonUpdate(w);
}
void TopMainMenu::resizeEvent(QResizeEvent* size) {
	upDate();
}

void TopMainMenu::ksfwButtonUpDate(int w) {
	if (ksfwButton == NULL) {
		ksfwButton = new YpButton(this,false);
		ksfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainKsfwButtonOff.png);");
		ksfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainKsfwButtonDown.png);");
		ksfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainKsfwButtonOn.png);");
		ksfwButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainKsfwButtonUnuse.png);");
		ksfwButton->setUsed();
		ksfwButton->useLeftChick(true);
		connect(ksfwButton,SIGNAL(leftChick()),this,SLOT(ksfwButtonChick()));
	}
	if (w >= 356) {
		ksfwButton->setGeometry(7, 4, 58, 78);
		ksfwButton->show();
	}else {
		ksfwButton->hide();
	}
}
void TopMainMenu::ksfwButtonChick() {

}

void TopMainMenu::fzButtonUpDate(int w) {
	if (fzButton == NULL) {
		fzButton = new YpButton(this, false);
		fzButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainFzButtonOff.png);");
		fzButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainFzButtonDown.png);");
		fzButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainFzButtonOn.png);");
		fzButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainFzButtonUnuse.png);");
		fzButton->setUnused();
		fzButton->useLeftChick(true);
		connect(fzButton, SIGNAL(leftChick()), this, SLOT(fzButtonChick()));
	}
	if (w >= 356) {
		fzButton->setGeometry(65, 4, 42, 78);
		fzButton->show();
	}else {
		fzButton->hide();
	}
}
void TopMainMenu::fzButtonChick() {

}

void TopMainMenu::ztButtonUpDate(int w) {
	if (ztButton == NULL) {
		ztButton = new YpButton(this, false);
		ztButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainZtButtonOff.png);");
		ztButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainZtButtonDown.png);");
		ztButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainZtButtonOn.png);");
		ztButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainZtButtonUnuse.png);");
		ztButton->setUnused();
		ztButton->useLeftChick(true);
		connect(ztButton, SIGNAL(leftChick()), this, SLOT(ztButtonChick()));
	}
	if (w >= 356) {
		ztButton->setGeometry(107, 4, 42, 56);
		ztButton->show();
	}
	else {
		ztButton->hide();
	}
}
void TopMainMenu::ztButtonChick() {

}

void TopMainMenu::jqButtonUpDate(int w) {
	if (jqButton == NULL) {
		jqButton = new YpButton(this, false);
		jqButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainJqButtonOff.png);");
		jqButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainJqButtonDown.png);");
		jqButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainJqButtonOn.png);");
		jqButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainJqButtonUnuse.png);");
		jqButton->setUnused();
		jqButton->useLeftChick(true);
		connect(jqButton, SIGNAL(leftChick()), this, SLOT(jqButtonChick()));
	}
	if (w >= 668) {
		jqButton->setGeometry(107, 60, 50, 22);
		jqButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainJqButtonOff.png);");
		jqButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainJqButtonDown.png);");
		jqButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainJqButtonOn.png);");
		jqButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainJqButtonUnuse.png);");
		jqButton->show();
	}else if (w >= 356) {
		jqButton->setGeometry(107, 60, 22, 22);
		jqButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainJqButtonOff_noText.png);");
		jqButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainJqButtonDown_noText.png);");
		jqButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainJqButtonOn_noText.png);");
		jqButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainJqButtonUnuse_noText.png);");
		jqButton->show();
	}else {
		jqButton->hide();
	}
}
void TopMainMenu::jqButtonChick() {

}
void TopMainMenu::fzljButtonUpDate(int w) {
	if (fzljButton == NULL) {
		fzljButton = new YpButton(this, false);
		fzljButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainFzljButtonOff.png);");
		fzljButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainFzljButtonDown.png);");
		fzljButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainFzljButtonOn.png);");
		fzljButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainFzljButtonUnuse.png);");
		fzljButton->setUnused();
		fzljButton->useLeftChick(true);
		connect(fzljButton, SIGNAL(leftChick()), this, SLOT(fzljButtonChick()));
	}
	if (w >= 668) {
		fzljButton->setGeometry(157, 4, 74, 22);
		fzljButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainFzljButtonOff.png);");
		fzljButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainFzljButtonDown.png);");
		fzljButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainFzljButtonOn.png);");
		fzljButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainFzljButtonUnuse.png);");
		fzljButton->show();
	}
	else if (w >= 356) {
		fzljButton->setGeometry(149, 4, 22, 22);
		fzljButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainFzljButtonOff_noText.png);");
		fzljButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainFzljButtonDown_noText.png);");
		fzljButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainFzljButtonOn_noText.png);");
		fzljButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainFzljButtonUnuse_noText.png);");
		fzljButton->show();
	}
	else {
		fzljButton->hide();
	}
}
void TopMainMenu::fzljButtonChick() {

}
void TopMainMenu::ztkjfsButtonUpDate(int w) {
	if (ztkjfsButton == NULL) {
		ztkjfsButton = new YpButton(this, false);
		ztkjfsButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonOff.png);");
		ztkjfsButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonDown.png);");
		ztkjfsButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonOn.png);");
		ztkjfsButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonUnuse.png);");
		ztkjfsButton->setUnused();
		ztkjfsButton->useLeftChick(true);
		connect(ztkjfsButton, SIGNAL(leftChick()), this, SLOT(ztkjfsButtonChick()));
	}
	if (w >= 668) {
		ztkjfsButton->setGeometry(157, 26, 98, 22);
		ztkjfsButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonOff.png);");
		ztkjfsButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonDown.png);");
		ztkjfsButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonOn.png);");
		ztkjfsButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonUnuse.png);");
		ztkjfsButton->show();
	}
	else if (w >= 356) {
		ztkjfsButton->setGeometry(149, 26, 22, 22);
		ztkjfsButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonOff_noText.png);");
		ztkjfsButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonDown_noText.png);");
		ztkjfsButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonOn_noText.png);");
		ztkjfsButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainZtkjfsButtonUnuse_noText.png);");
		ztkjfsButton->show();
	}
	else {
		ztkjfsButton->hide();
	}
}
void TopMainMenu::ztkjfsButtonChick() {

}

void TopMainMenu::ztbLabelUpDate(int w) {
	if (ztbLabel == NULL) {
		ztbLabel = new QLabel(this);
		ztbLabel->setStyleSheet("border-image:url(./images/TopMainMenu/mainZtbLabel.png);");
	}
	if (w >= 668) {
		ztbLabel->setGeometry(108, 85, 44, 19);
		ztbLabel->show();
	}
	else if (w >= 356) {
		ztbLabel->setGeometry(66, 85, 44, 19);
		ztbLabel->show();
	}
	else {
		ztbLabel->hide();
	}
}

void TopMainMenu::line1UpDate(int w) {
	if (line1 == NULL) {
		line1 = new QFrame(this);
		line1->setStyleSheet("background-color:#dadbdc;");
	}
	if (w >= 668) {
		line1->setGeometry(262, 2, 1, 102);
		line1->show();
	}
	else if (w >= 356) {
		line1->setGeometry(177, 2, 1, 102);
		line1->show();
	}
	else {
		line1->hide();
	}
}

void TopMainMenu::moveToButtonUpDate(int w) {
	if (moveToButton == NULL) {
		moveToButton = new YpButton(this, false);
		moveToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOff.png);");
		moveToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonDown.png);");
		moveToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOn.png);");
		moveToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonUnuse.png);");
		moveToButton->setUnused();
		moveToButton->useLeftChick(true);
		connect(moveToButton, SIGNAL(leftChick()), this, SLOT(moveToButtonChick()));
	}
	if (w >= 744) {
		moveToButton->setGeometry(266, 4, 42, 78);
		moveToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOff.png);");
		moveToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonDown.png);");
		moveToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOn.png);");
		moveToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonUnuse.png);");
		moveToButton->show();
	}else if (w >= 668) {
		moveToButton->setGeometry(266, 16, 72, 22);
		moveToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOff_small.png);");
		moveToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonDown_small.png);");
		moveToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOn_small.png);");
		moveToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonUnuse_small.png);");
		moveToButton->show();
	}else if (w >= 545) {
		moveToButton->setGeometry(182, 16, 72, 22);
		moveToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOff_small.png);");
		moveToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonDown_small.png);");
		moveToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOn_small.png);");
		moveToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonUnuse_small.png);");
		moveToButton->show();
	}else if (w >= 393) {
		moveToButton->setGeometry(182, 16, 30, 22);
		moveToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOff_noText.png);");
		moveToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonDown_noText.png);");
		moveToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonOn_noText.png);");
		moveToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainMoveToButtonUnuse_noText.png);");
		moveToButton->show();
	}
	else {
		moveToButton->hide();
	}
}
void TopMainMenu::moveToButtonChick() {

}
void TopMainMenu::copyToButtonUpDate(int w) {
	if (copyToButton == NULL) {
		copyToButton = new YpButton(this, false);
		copyToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOff.png);");
		copyToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonDown.png);");
		copyToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOn.png);");
		copyToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonUnuse.png);");
		copyToButton->setUnused();
		copyToButton->useLeftChick(true);
		connect(moveToButton, SIGNAL(leftChick()), this, SLOT(copyToButtonChick()));
	}
	if (w >= 744) {
		copyToButton->setGeometry(308, 4, 42, 78);
		copyToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOff.png);");
		copyToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonDown.png);");
		copyToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOn.png);");
		copyToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonUnuse.png);");
		copyToButton->show();
	}
	else if (w >= 668) {
		copyToButton->setGeometry(266, 48, 72, 22);
		copyToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOff_small.png);");
		copyToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonDown_small.png);");
		copyToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOn_small.png);");
		copyToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonUnuse_small.png);");
		copyToButton->show();
	}
	else if (w >= 545) {
		copyToButton->setGeometry(182, 48, 72, 22);
		copyToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOff_small.png);");
		copyToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonDown_small.png);");
		copyToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOn_small.png);");
		copyToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonUnuse_small.png);");
		copyToButton->show();
	}
	else if (w >= 393) {
		copyToButton->setGeometry(182, 48, 30, 22);
		copyToButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOff_noText.png);");
		copyToButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonDown_noText.png);");
		copyToButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonOn_noText.png);");
		copyToButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainCopyToButtonUnuse_noText.png);");
		copyToButton->show();
	}
	else {
		copyToButton->hide();
	}
}
void TopMainMenu::copyToButtonChick() {

}

void TopMainMenu::line1_1UpDate(int w) {
	if (line1_1 == NULL) {
		line1_1 = new QFrame(this);
		line1_1->setStyleSheet("background-color:#dadbdc;");
	}
	if (w >= 744) {
		line1_1->setGeometry(354, 15, 1, 55);
		line1_1->show();
	}else if (w >= 668) {
		line1_1->setGeometry(342, 15, 1, 55);
		line1_1->show();
	}else if (w >= 545) {
		line1_1->setGeometry(258, 15, 1, 55);
		line1_1->show();
	}else if (w >= 393) {
		line1_1->setGeometry(216, 15, 1, 55);
		line1_1->show();
	}else {
		line1_1->hide();
	}
}

void TopMainMenu::removeButtonUpDate(int w) {
	if (removeButton == NULL) {
		removeButton = new YpButton(this, false);
		removeButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOff.png);");
		removeButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonDown.png);");
		removeButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOn.png);");
		removeButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonUnuse.png);");
		removeButton->setUnused();
		removeButton->useLeftChick(true);
		connect(moveToButton, SIGNAL(leftChick()), this, SLOT(removeButtonChick()));
	}
	if (w >= 744) {
		removeButton->setGeometry(358, 4, 42, 78);
		removeButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOff.png);");
		removeButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonDown.png);");
		removeButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOn.png);");
		removeButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonUnuse.png);");
		removeButton->show();
	}
	else if (w >= 668) {
		removeButton->setGeometry(346, 16, 60, 22);
		removeButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOff_small.png);");
		removeButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonDown_small.png);");
		removeButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOn_small.png);");
		removeButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonUnuse_small.png);");
		removeButton->show();
	}
	else if (w >= 545) {
		removeButton->setGeometry(262, 16, 60, 22);
		removeButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOff_small.png);");
		removeButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonDown_small.png);");
		removeButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOn_small.png);");
		removeButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonUnuse_small.png);");
		removeButton->show();
	}
	else if (w >= 393) {
		removeButton->setGeometry(220, 16, 32, 22);
		removeButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOff_noText.png);");
		removeButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonDown_noText.png);");
		removeButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonOn_noText.png);");
		removeButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRemoveButtonUnuse_noText.png);");
		removeButton->show();
	}
	else {
		removeButton->hide();
	}
}
void TopMainMenu::removeButtonChick() {

}

void TopMainMenu::renameButtonUpDate(int w) {
	if (renameButton == NULL) {
		renameButton = new YpButton(this, false);
		renameButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOff.png);");
		renameButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRenameButtonDown.png);");
		renameButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOn.png);");
		renameButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRenameButtonUnuse.png);");
		renameButton->setUnused();
		renameButton->useLeftChick(true);
		connect(renameButton, SIGNAL(leftChick()), this, SLOT(renameButtonChick()));
	}
	if (w >= 744) {
		renameButton->setGeometry(400, 4, 42, 78);
		renameButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOff.png);");
		renameButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRenameButtonDown.png);");
		renameButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOn.png);");
		renameButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRenameButtonUnuse.png);");
		renameButton->show();
	}
	else if (w >= 668) {
		renameButton->setGeometry(346, 48, 62, 22);
		renameButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOff_small.png);");
		renameButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRenameButtonDown_small.png);");
		renameButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOn_small.png);");
		renameButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRenameButtonUnuse_small.png);");
		renameButton->show();
	}
	else if (w >= 545) {
		renameButton->setGeometry(262, 48, 62, 22);
		renameButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOff_small.png);");
		renameButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRenameButtonDown_small.png);");
		renameButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOn_small.png);");
		renameButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRenameButtonUnuse_small.png);");
		renameButton->show();
	}
	else if (w >= 393) {
		renameButton->setGeometry(220, 48, 22, 22);
		renameButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOff_noText.png);");
		renameButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainRenameButtonDown_noText.png);");
		renameButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainRenameButtonOn_noText.png);");
		renameButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainRenameButtonUnuse_noText.png);");
		renameButton->show();
	}
	else {
		renameButton->hide();
	}
}
void TopMainMenu::renameButtonChick() {

}

void TopMainMenu::zzLabelUpDate(int w) {
	if (zzLabel == NULL) {
		zzLabel = new QLabel(this);
		zzLabel->setStyleSheet("border-image:url(./images/TopMainMenu/mainZzLabel.png);");
	}
	if (w >= 744) {
		zzLabel->setGeometry(338, 85, 33, 19);
		zzLabel->show();
	}
	else if (w >= 668) {
		zzLabel->setGeometry(321, 85, 33, 19);
		zzLabel->show();
	}
	else if (w >= 545) {
		zzLabel->setGeometry(237, 85, 33, 19);
		zzLabel->show();
	}
	else if (w >= 393) {
		zzLabel->setGeometry(201, 85, 33, 19);
		zzLabel->show();
	}
	else {
		zzLabel->hide();
	}
}

void TopMainMenu::line2UpDate(int w) {
	if (line2 == NULL) {
		line2 = new QFrame(this);
		line2->setStyleSheet("background-color:#dadbdc;");
	}
	if (w >= 744) {
		line2->setGeometry(448, 2, 1, 102);
		line2->show();
	}else if (w >= 668) {
		line2->setGeometry(414, 2, 1, 102);
		line2->show();
	}else if (w >= 545) {
		line2->setGeometry(330, 2, 1, 102);
		line2->show();
	}else if (w >= 393) {
		line2->setGeometry(258, 2, 1, 102);
		line2->show();
	}
	else {
		line2->hide();
	}
}

void TopMainMenu::xwjjButtonUpDate(int w) {
	if (xwjjButton == NULL) {
		xwjjButton = new YpButton(this, false);
		xwjjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXwjjButtonOff.png);");
		xwjjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXwjjButtonDown.png);");
		xwjjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXwjjButtonOn.png);");
		xwjjButton->setUsed();
		xwjjButton->useLeftChick(true);
		connect(xwjjButton, SIGNAL(leftChick()), this, SLOT(xwjjButtonChick()));
	}
	if (w >= 744) {
		xwjjButton->setGeometry(453, 4, 42, 78);
		xwjjButton->show();
	}
	else if (w >= 668) {
		xwjjButton->setGeometry(419, 4, 42, 78);
		xwjjButton->show();
	}
	else if (w >= 545) {
		xwjjButton->setGeometry(335, 4, 42, 78);
		xwjjButton->show();
	}
	else if (w >= 473) {
		xwjjButton->setGeometry(263, 4, 42, 78);
		xwjjButton->show();
	}
	else {
		xwjjButton->hide();
	}
}
void TopMainMenu::xwjjButtonChick() {

}

void TopMainMenu::xxmButtonUpDate(int w) {
	if (xxmButton == NULL) {
		xxmButton = new YpButton(this, false);
		xxmButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOff.png);");
		xxmButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXxmButtonDown.png);");
		xxmButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOn.png);");
		xxmButton->setUsed();
		xxmButton->useLeftChick(true);
		connect(xxmButton, SIGNAL(leftChick()), this, SLOT(xxmButtonChick()));
	}
	if (w >= 798) {
		xxmButton->setGeometry(495, 4, 84, 22);
		xxmButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOff.png);");
		xxmButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXxmButtonDown.png);");
		xxmButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOn.png);");
		xxmButton->show();
	}
	else if (w >= 744) {
		xxmButton->setGeometry(495, 4, 30, 22);
		xxmButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOff_noText.png);");
		xxmButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXxmButtonDown_noText.png);");
		xxmButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOn_noText.png);");
		xxmButton->show();
	}
	else if (w >= 668) {
		xxmButton->setGeometry(461, 4, 30, 22);
		xxmButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOff_noText.png);");
		xxmButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXxmButtonDown_noText.png);");
		xxmButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOn_noText.png);");
		xxmButton->show();
	}
	else if (w >= 545) {
		xxmButton->setGeometry(377, 4, 30, 22);
		xxmButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOff_noText.png);");
		xxmButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXxmButtonDown_noText.png);");
		xxmButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOn_noText.png);");
		xxmButton->show();
	}
	else if (w >= 473) {
		xxmButton->setGeometry(305, 4, 30, 22);
		xxmButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOff_noText.png);");
		xxmButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXxmButtonDown_noText.png);");
		xxmButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXxmButtonOn_noText.png);");
		xxmButton->show();
	}
	else {
		xxmButton->hide();
	}
}
void TopMainMenu::xxmButtonChick() {

}

void TopMainMenu::qsfwButtonUpDate(int w) {
	if (qsfwButton == NULL) {
		qsfwButton = new YpButton(this, false);
		qsfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOff.png);");
		qsfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonDown.png);");
		qsfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOn.png);");
		qsfwButton->setUsed();
		qsfwButton->useLeftChick(true);
		connect(qsfwButton, SIGNAL(leftChick()), this, SLOT(qsfwButtonChick()));
	}
	if (w >= 798) {
		qsfwButton->setGeometry(495, 26, 84, 22);
		qsfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOff.png);");
		qsfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonDown.png);");
		qsfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOn.png);");
		qsfwButton->show();
	}
	else if (w >= 744) {
		qsfwButton->setGeometry(495, 26, 30, 22);
		qsfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOff_noText.png);");
		qsfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonDown_noText.png);");
		qsfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOn_noText.png);");
		qsfwButton->show();
	}
	else if (w >= 668) {
		qsfwButton->setGeometry(461, 26, 30, 22);
		qsfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOff_noText.png);");
		qsfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonDown_noText.png);");
		qsfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOn_noText.png);");
		qsfwButton->show();
	}
	else if (w >= 545) {
		qsfwButton->setGeometry(377, 26, 30, 22);
		qsfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOff_noText.png);");
		qsfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonDown_noText.png);");
		qsfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOn_noText.png);");
		qsfwButton->show();
	}
	else if (w >= 473) {
		qsfwButton->setGeometry(305, 26, 30, 22);
		qsfwButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOff_noText.png);");
		qsfwButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonDown_noText.png);");
		qsfwButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQsfwButtonOn_noText.png);");
		qsfwButton->show();
	}
	else {
		qsfwButton->hide();
	}
}
void TopMainMenu::qsfwButtonChick() {

}

void TopMainMenu::xjLabelUpDate(int w) {
	if (xjLabel == NULL) {
		xjLabel = new QLabel(this);
		xjLabel->setStyleSheet("border-image:url(./images/TopMainMenu/mainXjLabel.png);");
	}
	if (w >= 798) {
		xjLabel->setGeometry(499, 85, 34, 20);
		xjLabel->show();
	}
	else if (w >= 744) {
		xjLabel->setGeometry(472, 85, 34, 20);
		xjLabel->show();
	}
	else if (w >= 668) {
		xjLabel->setGeometry(438, 85, 34, 20);
		xjLabel->show();
	}
	else if (w >= 545) {
		xjLabel->setGeometry(354, 85, 34, 20);
		xjLabel->show();
	}
	else if (w >= 473) {
		xjLabel->setGeometry(282, 85, 34, 20);
		xjLabel->show();
	}
	else {
		xjLabel->hide();
	}
}

void TopMainMenu::line3UpDate(int w) {
	if (line3 == NULL) {
		line3 = new QFrame(this);
		line3->setStyleSheet("background-color:#dadbdc;");
	}
	if (w >= 798) {
		line3->setGeometry(585, 2, 1, 102);
		line3->show();
	}
	else if (w >= 744) {
		line3->setGeometry(531, 2, 1, 102);
		line3->show();
	}
	else if (w >= 668) {
		line3->setGeometry(497, 2, 1, 102);
		line3->show();
	}
	else if (w >= 545) {
		line3->setGeometry(413, 2, 1, 102);
		line3->show();
	}
	else if (w >= 473) {
		line3->setGeometry(341, 2, 1, 102);
		line3->show();
	}
	else {
		line3->hide();
	}
}

void TopMainMenu::sxButtonUpDate(int w) {
	if (sxButton == NULL) {
		sxButton = new YpButton(this, false);
		sxButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainSxButtonOff.png);");
		sxButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainSxButtonDown.png);");
		sxButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainSxButtonOn.png);");
		sxButton->setUsed();
		sxButton->useLeftChick(true);
		connect(sxButton, SIGNAL(leftChick()), this, SLOT(sxButtonChick()));
	}
	if (w >= 798) {
		sxButton->setGeometry(590, 4, 42, 78);
		sxButton->show();
	}
	else if (w >= 744) {
		sxButton->setGeometry(536, 4, 42, 78);
		sxButton->show();
	}
	else if (w >= 668) {
		sxButton->setGeometry(502, 4, 42, 78);
		sxButton->show();
	}
	else if (w >= 545) {
		sxButton->setGeometry(418, 4, 42, 78);
		sxButton->show();
	}
	else if (w >= 473) {
		sxButton->setGeometry(346, 4, 42, 78);
		sxButton->show();
	}
	else if (w >= 434) {
		sxButton->setGeometry(307, 4, 42, 78);
		sxButton->show();
	}
	else {
		sxButton->hide();
	}
}
void TopMainMenu::sxButtonChick(){

}
void TopMainMenu::openButtonUpDate(int w) {
	if (openButton == NULL) {
		openButton = new YpButton(this, false);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse.png);");
		openButton->setUsed();
		openButton->useLeftChick(true);
		connect(openButton, SIGNAL(leftChick()), this, SLOT(openButtonChick()));
	}
	if (w >= 798) {
		openButton->setGeometry(632, 7, 60, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse.png);");
		openButton->show();
	}
	else if (w >= 744) {
		openButton->setGeometry(578, 7, 60, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse.png);");
		openButton->show();
	}
	else if (w >= 710) {
		openButton->setGeometry(544, 7, 60, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse.png);");
		openButton->show();
	}
	else if (w >= 668) {
		openButton->setGeometry(544, 7, 22, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff_noText.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown_noText.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn_noText.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse_noText.png);");
		openButton->show();
	}
	else if (w >= 545) {
		openButton->setGeometry(460, 7, 32, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff_noText.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown_noText.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn_noText.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse_noText.png);");
		openButton->show();
	}
	else if (w >= 473) {
		openButton->setGeometry(388, 7, 32, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff_noText.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown_noText.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn_noText.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse_noText.png);");
		openButton->show();
	}
	else if (w >= 434) {
		openButton->setGeometry(349, 7, 32, 22);
		openButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOff_noText.png);");
		openButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainOpenButtonDown_noText.png);");
		openButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainOpenButtonOn_noText.png);");
		openButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainOpenButtonUnuse_noText.png);");
		openButton->show();
	}
	else {
		openButton->hide();
	}
}

void TopMainMenu::openButtonChick() {

}

void TopMainMenu::bjButtonUpDate(int w) {
	if (bjButton == NULL) {
		bjButton = new YpButton(this, false);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse.png);");
		bjButton->setUsed();
		bjButton->useLeftChick(true);
		connect(bjButton, SIGNAL(leftChick()), this, SLOT(bjButtonChick()));
	}
	if (w >= 798) {
		bjButton->setGeometry(632, 32, 50, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse.png);");
		bjButton->show();
	}
	else if (w >= 744) {
		bjButton->setGeometry(578, 32, 50, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse.png);");
		bjButton->show();
	}
	else if (w >= 710) {
		bjButton->setGeometry(544, 32, 50, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse.png);");
		bjButton->show();
	}
	else if (w >= 668) {
		bjButton->setGeometry(544, 32, 22, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff_noText.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown_noText.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn_noText.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse_noText.png);");
		bjButton->show();
	}
	else if (w >= 545) {
		bjButton->setGeometry(460, 32, 22, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff_noText.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown_noText.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn_noText.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse_noText.png);");
		bjButton->show();
	}
	else if (w >= 473) {
		bjButton->setGeometry(388, 32, 22, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff_noText.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown_noText.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn_noText.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse_noText.png);");
		bjButton->show();
	}
	else if (w >= 434) {
		bjButton->setGeometry(349, 32, 22, 22);
		bjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainBjButtonOff_noText.png);");
		bjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainBjButtonDown_noText.png);");
		bjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainBjButtonOn_noText.png);");
		bjButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainBjButtonUnuse_noText.png);");
		bjButton->show();
	}
	else {
		bjButton->hide();
	}
}

void TopMainMenu::bjButtonChick() {

}

void TopMainMenu::lsjlButtonUpDate(int w) {
	if (lsjlButton == NULL) {
		lsjlButton = new YpButton(this, false);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse.png);");
		lsjlButton->setUsed();
		lsjlButton->useLeftChick(true);
		connect(lsjlButton, SIGNAL(leftChick()), this, SLOT(lsjlButtonChick()));
	}
	if (w >= 798) {
		lsjlButton->setGeometry(632, 57, 74, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse.png);");
		lsjlButton->show();
	}
	else if (w >= 744) {
		lsjlButton->setGeometry(578, 57, 74, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse.png);");
		lsjlButton->show();
	}
	else if (w >= 710) {
		lsjlButton->setGeometry(544, 57, 74, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse.png);");
		lsjlButton->show();
	}
	else if (w >= 668) {
		lsjlButton->setGeometry(544, 57, 22, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff_noText.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown_noText.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn_noText.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse_noText.png);");
		lsjlButton->show();
	}
	else if (w >= 545) {
		lsjlButton->setGeometry(460, 57, 22, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff_noText.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown_noText.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn_noText.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse_noText.png);");
		lsjlButton->show();
	}
	else if (w >= 473) {
		lsjlButton->setGeometry(388, 57, 22, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff_noText.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown_noText.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn_noText.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse_noText.png);");
		lsjlButton->show();
	}
	else if (w >= 434) {
		lsjlButton->setGeometry(349, 57, 22, 22);
		lsjlButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOff_noText.png);");
		lsjlButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonDown_noText.png);");
		lsjlButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonOn_noText.png);");
		lsjlButton->setMouseUnuseStyle("border-image:url(./images/TopMainMenu/mainLsjlButtonUnuse_noText.png);");
		lsjlButton->show();
	}
	else {
		lsjlButton->hide();
	}
}

void TopMainMenu::lsjlButtonChick() {

}

void TopMainMenu::dkLabelUpDate(int w) {
	if (dkLabel == NULL) {
		dkLabel = new QLabel(this);
		dkLabel->setStyleSheet("border-image:url(./images/TopMainMenu/mainDkLabel.png);");
	}
	if (w >= 798) {
		dkLabel->setGeometry(632, 85, 33, 19);
		dkLabel->show();
	}
	else if (w >= 744) {
		dkLabel->setGeometry(578, 85, 33, 19);
		dkLabel->show();
	}
	else if (w >= 668) {
		dkLabel->setGeometry(544, 85, 33, 19);
		dkLabel->show();
	}
	else if (w >= 545) {
		dkLabel->setGeometry(439, 85, 33, 19);
		dkLabel->show();
	}
	else if (w >= 473) {
		dkLabel->setGeometry(367, 85, 33, 19);
		dkLabel->show();
	}
	else if (w >= 434) {
		dkLabel->setGeometry(328, 85, 33, 19);
		dkLabel->show();
	}
	else {
		dkLabel->hide();
	}
}

void TopMainMenu::line4UpDate(int w) {
	if (line4 == NULL) {
		line4 = new QFrame(this);
		line4->setStyleSheet("background-color:#dadbdc;");
	}
	if (w >= 798) {
		line4->setGeometry(713, 2, 1, 102);
		line4->show();
	}
	else if (w >= 744) {
		line4->setGeometry(658, 2, 1, 102);
		line4->show();
	}
	else if (w >= 710) {
		line4->setGeometry(624, 2, 1, 102);
		line4->show();
	}
	else if (w >= 668) {
		line4->setGeometry(582, 2, 1, 102);
		line4->show();
	}
	else if (w >= 545) {
		line4->setGeometry(498, 2, 1, 102);
		line4->show();
	}
	else if (w >= 473) {
		line4->setGeometry(426, 2, 1, 102);
		line4->show();
	}
	else if (w >= 434) {
		line4->setGeometry(387, 2, 1, 102);
		line4->show();
	}
	else {
		line4->hide();
	}
}

void TopMainMenu::qxButtonUpDate(int w) {
	if (qxButton == NULL) {
		qxButton = new YpButton(this, false);
		qxButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQxButtonOff.png);");
		qxButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQxButtonDown.png);");
		qxButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQxButtonOn.png);");
		qxButton->setUsed();
		qxButton->useLeftChick(true);
		connect(qxButton, SIGNAL(leftChick()), this, SLOT(qxButtonChick()));
	}
	if (w >= 798) {
		qxButton->setGeometry(715, 5, 74, 22);
		qxButton->show();
	}else if(w >= 744) {
		qxButton->setGeometry(663, 5, 74, 22);
		qxButton->show();
	}
	else if (w >= 710) {
		qxButton->setGeometry(629, 5, 74, 22);
		qxButton->show();
	}
	else if (w >= 668) {
		qxButton->setGeometry(587, 5, 74, 22);
		qxButton->show();
	}
	else if (w >= 584) {
		qxButton->setGeometry(503, 5, 74, 22);
		qxButton->show();
	}
	else {
		qxButton->hide();
	}
}

void TopMainMenu::qxButtonChick() {

}

void TopMainMenu::qxxzButtonUpDate(int w) {
	if (qxxzButton == NULL) {
		qxxzButton = new YpButton(this, false);
		qxxzButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainQxxzButtonOff.png);");
		qxxzButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainQxxzButtonDown.png);");
		qxxzButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainQxxzButtonOn.png);");
		qxxzButton->setUsed();
		qxxzButton->useLeftChick(true);
		connect(qxxzButton, SIGNAL(leftChick()), this, SLOT(qxxzButtonChick()));
	}
	if (w >= 798) {
		qxxzButton->setGeometry(715, 26, 74, 22);
		qxxzButton->show();
	}
	else if (w >= 744) {
		qxxzButton->setGeometry(663, 26, 74, 22);
		qxxzButton->show();
	}
	else if (w >= 710) {
		qxxzButton->setGeometry(629, 26, 74, 22);
		qxxzButton->show();
	}
	else if (w >= 668) {
		qxxzButton->setGeometry(587, 26, 74, 22);
		qxxzButton->show();
	}
	else if (w >= 584) {
		qxxzButton->setGeometry(503, 26, 74, 22);
		qxxzButton->show();
	}
	else {
		qxxzButton->hide();
	}
}

void TopMainMenu::qxxzButtonChick() {

}

void TopMainMenu::fxButtonUpDate(int w) {
	if (fxButton == NULL) {
		fxButton = new YpButton(this, false);
		fxButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainFxButtonOff.png);");
		fxButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainFxButtonDown.png);");
		fxButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainFxButtonOn.png);");
		fxButton->setUsed();
		fxButton->useLeftChick(true);
		connect(fxButton, SIGNAL(leftChick()), this, SLOT(fxButtonChick()));
	}
	if (w >= 798) {
		fxButton->setGeometry(715, 48, 74, 22);
		fxButton->show();
	}
	else if (w >= 744) {
		fxButton->setGeometry(663, 48, 74, 22);
		fxButton->show();
	}
	else if (w >= 710) {
		fxButton->setGeometry(629, 48, 74, 22);
		fxButton->show();
	}
	else if (w >= 668) {
		fxButton->setGeometry(587, 48, 74, 22);
		fxButton->show();
	}
	else if (w >= 584) {
		fxButton->setGeometry(503, 48, 74, 22);
		fxButton->show();
	}
	else {
		fxButton->hide();
	}
}

void TopMainMenu::fxButtonChick() {

}

void TopMainMenu::xzLabelUpDate(int w) {
	if (xzLabel == NULL) {
		xzLabel = new QLabel(this);
		xzLabel->setStyleSheet("border-image:url(./images/TopMainMenu/mainXzLabel.png);");
	}
	if (w >= 798) {
		xzLabel->setGeometry(737, 85, 34, 19);
		xzLabel->show();
	}
	else if (w >= 744) {
		xzLabel->setGeometry(683, 85, 34, 19);
		xzLabel->show();
	}
	else if (w >= 710) {
		xzLabel->setGeometry(649, 85, 34, 19);
		xzLabel->show();
	}
	else if (w >= 668) {
		xzLabel->setGeometry(607, 85, 34, 19);
		xzLabel->show();
	}
	else if (w >= 584) {
		xzLabel->setGeometry(523, 85, 34, 19);
		xzLabel->show();
	}
	else {
		xzLabel->hide();
	}
}

void TopMainMenu::line5UpDate(int w) {
	if (line5 == NULL) {
		line5 = new QFrame(this);
		line5->setStyleSheet("background-color:#dadbdc;");
	}
	if (w >= 798) {
		line5->setGeometry(797, 2, 1, 102);
		line5->show();
	}
	else if (w >= 744) {
		line5->setGeometry(743, 2, 1, 102);
		line5->show();
	}
	else if (w >= 710) {
		line5->setGeometry(709, 2, 1, 102);
		line5->show();
	}
	else if (w >= 668) {
		line5->setGeometry(667, 2, 1, 102);
		line5->show();
	}
	else if (w >= 584) {
		line5->setGeometry(583, 2, 1, 102);
		line5->show();
	}
	else {
		line4->hide();
	}
}

void TopMainMenu::ztbButtonUpdate(int w) {
	if (ztbButton == NULL) {
		ztbButton = new YpButton(this, false);
		ztbButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainZtbButtonOff.png);");
		ztbButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainZtbButtonDown.png);");
		ztbButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainZtbButtonOn.png);");
		ztbButton->setUsed();
		ztbButton->useLeftChick(true);
		connect(ztbButton, SIGNAL(leftChick()), this, SLOT(ztbButtonChick()));
	}
	if (w < 356) {
		ztbButton->setGeometry(5, 2, 42, 103);
		ztbButton->show();
	}else {
		ztbButton->hide();
	}
}
void TopMainMenu::ztbButtonChick() {

}

void TopMainMenu::zzButtonUpdate(int w) {
	if (zzButton == NULL) {
		zzButton = new YpButton(this, false);
		zzButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainZzButtonOff.png);");
		zzButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainZzButtonDown.png);");
		zzButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainZzButtonOn.png);");
		zzButton->setUsed();
		zzButton->useLeftChick(true);
		connect(zzButton, SIGNAL(leftChick()), this, SLOT(zzButtonChick()));
	}
	if (w < 356) {
		zzButton->setGeometry(50, 2, 42, 103);
		zzButton->show();
	}else if (w < 393) {
		zzButton->setGeometry(179, 2, 42, 103);
		zzButton->show();
	}else {
		zzButton->hide();
	}
}
void TopMainMenu::zzButtonChick() {

}

void TopMainMenu::xjButtonUpdate(int w) {
	if (xjButton == NULL) {
		xjButton = new YpButton(this, false);
		xjButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXjButtonOff.png);");
		xjButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXjButtonDown.png);");
		xjButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXjButtonOn.png);");
		xjButton->setUsed();
		xjButton->useLeftChick(true);
		connect(xjButton, SIGNAL(leftChick()), this, SLOT(xjButtonChick()));
	}
	if (w < 356) {
		xjButton->setGeometry(95, 2, 42, 103);
		xjButton->show();
	}else if (w < 393) {
		xjButton->setGeometry(224, 2, 42, 103);
		xjButton->show();
	}else if (w < 473) {
		xjButton->setGeometry(260, 2, 42, 103);
		xjButton->show();
	}else {
		xjButton->hide();
	}
}
void TopMainMenu::xjButtonChick() {

}

void TopMainMenu::dkButtonUpdate(int w) {
	if (dkButton == NULL) {
		dkButton = new YpButton(this, false);
		dkButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainDkButtonOff.png);");
		dkButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainDkButtonDown.png);");
		dkButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainDkButtonOn.png);");
		dkButton->setUsed();
		dkButton->useLeftChick(true);
		connect(dkButton, SIGNAL(leftChick()), this, SLOT(dkButtonChick()));
	}
	if (w < 356) {
		dkButton->setGeometry(140, 2, 42, 103);
		dkButton->show();
	}
	else if (w < 393) {
		dkButton->setGeometry(269, 2, 42, 103);
		dkButton->show();
	}
	else if (w < 434) {
		dkButton->setGeometry(305, 2, 42, 103);
		dkButton->show();
	}else {
		dkButton->hide();
	}
}
void TopMainMenu::dkButtonChick() {

}

void TopMainMenu::xzButtonUpdate(int w) {
	if (xzButton == NULL) {
		xzButton = new YpButton(this, false);
		xzButton->setMouseLeaveStyle("border-image:url(./images/TopMainMenu/mainXzButtonOff.png);");
		xzButton->setMouseChickStyle("border-image:url(./images/TopMainMenu/mainXzButtonDown.png);");
		xzButton->setMouseEnterStyle("border-image:url(./images/TopMainMenu/mainXzButtonOn.png);");
		xzButton->setUsed();
		xzButton->useLeftChick(true);
		connect(xzButton, SIGNAL(leftChick()), this, SLOT(xzButtonChick()));
	}
	if (w < 356) {
		xzButton->setGeometry(185, 2, 42, 103);
		xzButton->show();
	}
	else if (w < 393) {
		xzButton->setGeometry(314, 2, 42, 103);
		xzButton->show();
	}
	else if (w < 434) {
		xzButton->setGeometry(350, 2, 42, 103);
		xzButton->show();
	}
	else if (w < 473) {
		xzButton->setGeometry(389, 2, 42, 103);
		xzButton->show();
	}
	else if (w < 545) {
		xzButton->setGeometry(428, 2, 42, 103);
		xzButton->show();
	}
	else if (w < 584) {
		xzButton->setGeometry(500, 2, 42, 103);
		xzButton->show();
	}
	else {
		xzButton->hide();
	}
}
void TopMainMenu::xzButtonChick() {

}