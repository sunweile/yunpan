#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileInfo>
#include <QDateTime>
#include "ui_LoginView.h"
#pragma execution_character_set("utf-8")
class LoginView : public QMainWindow
{
	Q_OBJECT

public:
	LoginView(QWidget* parent = Q_NULLPTR);

	QString yhm = "";
	QString mim = "";

public slots:
	void clickLogin();
	void yhmchanged(const QString&);

private:
	Ui::LoginViewClass ui;
};
