#pragma once

#include <QDialog>
#include "WebView.h"
#pragma execution_character_set("utf-8")
class LoginDialog : public QDialog
{
	Q_OBJECT

public:
	LoginDialog(QString);
	~LoginDialog();
	QStringList getStr();
	void setStr(QStringList);

private:
	WebView* wb;
	QStringList str;
};
