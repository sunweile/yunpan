#pragma once

#include <QFrame>
#include <QResizeEvent>

#include "YpButton.h"
#include "TopMainMenu.h"
#include <QDebug>
#include <QDir>
#pragma execution_character_set("utf-8")
class TopMenuView : public QFrame
{
	Q_OBJECT

public:
	enum Type {
		None,
		File,
		Main,
		Share,
		Show
	};
	TopMenuView(QWidget *parent,int w);
	~TopMenuView();
	void upDate(int w);
	void resizeEvent(QResizeEvent* size);
public slots:
	void filesButtonChick();
	void mianButtonChick();
	void shareButtonChick();
	void showButtonChick();

	void filesButtonFocusOut();
	void mianButtonFocusOut();
	void shareButtonFocusOut();
	void showButtonFocusOut();
private:
	
	Type type;

	YpButton* filesButton;
	YpButton* mainButton;
	YpButton* shareButton;
	YpButton* showButton;

	TopMainMenu* filesView;
	TopMainMenu* mainView;
	TopMainMenu* shareView;
	TopMainMenu* showView;



};
