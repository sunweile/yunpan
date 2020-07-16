#pragma once

#include <QToolButton>
#include <QMouseEvent>
#include <QTimer>
#pragma execution_character_set("utf-8")
class YpButton : public QToolButton
{
	Q_OBJECT

public:
	enum ButtonType {
		Enter,
		Leave,
		Chick,
		Unuse
	};
	YpButton(QWidget*parent,bool allUse);
	~YpButton();
	void setMouseEnterStyle(const QString& str);
	void setMouseLeaveStyle(const QString& str);
	void setMouseChickStyle(const QString& str);
	void setMouseUnuseStyle(const QString& str);

	void useLeftChick(bool b);
	void useRightChick(bool b);
	void useLeftDown(bool b);
	void useRightUp(bool b);
	void useLeftUp(bool b);
	void useRightDown(bool b);
	void useDoubleChick(bool b);
	void useHoveringActivation(bool b,int ms);
	void useActivation(bool b);
	void unActivation();
	bool isActivationNow();
	void setUnused();
	void setUsed();
	bool isLeave();
	bool isEnter();
	bool isChick();
	bool isUsed();
private:
	QString mouseEnterStyle;
	QString mouseLeaveStyle;
	QString mouseChickStyle;
	QString mouseUnuseStyle;

	ButtonType buttonType;

	bool isUseActivation;
	bool isActivation;
	bool isLeftChick;
	bool isRightChick;
	bool isLeftDown;
	bool isRightUp;
	bool isLeftUp;
	bool isRightDown;
	bool isDoubleChick;
	bool isHoveringActivation;

	QTimer* timer;
	QTimer* useHoveringActivationTimer;
	int hoveringActivationTime;
	int time;
	int chickTimes;
	void timerInit();
	void timerStop();
	void timerDelete();
signals:
	void leftChick();
	void focusOut();
	void rightChick();
	void leftUp();
	void leftDown();
	void rightUp();
	void rightDown();
	void doubleChick();
	void hoveringActivation();

private slots:
	void timeUpOn();
	void doHoveringActivation();
protected:
	void enterEvent(QEvent* event);
	void leaveEvent(QEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void focusOutEvent(QFocusEvent* e);
};
