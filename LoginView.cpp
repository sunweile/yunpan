#include "LoginView.h"
#pragma execution_character_set("utf-8")
LoginView::LoginView(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.login_button, SIGNAL(clicked()), this, SLOT(clickLogin()));
	connect(ui.yhm_input, SIGNAL(textEdited(const QString&)), this ,SLOT(yhmchanged(const QString&)));
}

void LoginView::yhmchanged(const QString& text) {
	yhm = text;
}

void LoginView::clickLogin() {
	QFileInfo file("C:/Go");
	ui.login_button->setText(file.lastModified().toString("yyyy_MM_dd_hh_mm_ss"));
}