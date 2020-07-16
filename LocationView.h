#pragma once

#include <QWidget>
#include <QLineEdit>
#include "YpButton.h"
#include <QList>
#pragma execution_character_set("utf-8")
class LocationView : public QWidget
{
	Q_OBJECT

public:
	LocationView(QWidget *parent);
	~LocationView();
	void newPath(QString);
	void newHistory();
	void setSize(int w, int h);
public slots:
	void reLoad();
	void upDate();
	void goParent();
	void goBack();
	void goForward();
	void search(QString);
private:
	int hIndex;
	QLineEdit* addressBarText;
	QLineEdit* searchText;

	YpButton* backButton;
	YpButton* forwardButton;
	YpButton* reloadButton;
	YpButton* upButton;
	YpButton* historyButton;
	QList<QString>* historyList;
};
