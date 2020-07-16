#pragma once

#include <QFrame>
#include <QMouseEvent>
#include <QDebug>
#include <QPoint>
#pragma execution_character_set("utf-8")
class YpLine : public QFrame
{
	Q_OBJECT

public:
	YpLine(QWidget *parent);
	~YpLine();
signals:
	void lineDown(int x);
	void lineUp();
	void lineMove(int x);
protected:
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);

};
