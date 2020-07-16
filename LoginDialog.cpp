#include "LoginDialog.h"
#pragma execution_character_set("utf-8")
LoginDialog::LoginDialog(QString s)
	: QDialog()
{
	wb = new WebView(this);
	wb->setGeometry(0,0,800,450);
	wb->show();
}

LoginDialog::~LoginDialog()
{
}

QStringList LoginDialog::getStr() {
	return str;
}

void LoginDialog::setStr(QStringList s) {
	str = s;
}
