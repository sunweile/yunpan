#include "YpLine.h"
#pragma execution_character_set("utf-8")
YpLine::YpLine(QWidget *parent)
	: QFrame(parent)
{

}

YpLine::~YpLine()
{
}

void YpLine::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		emit lineDown(event->globalPos().x());
	}
}

void YpLine::mouseReleaseEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		emit lineUp();
	}
}

void YpLine::mouseMoveEvent(QMouseEvent* event) {
	emit lineMove(event->globalPos().x());
}

void YpLine::enterEvent(QEvent* event) {
	this->setCursor(Qt::SizeHorCursor);
}

void YpLine::leaveEvent(QEvent* event) {
	this->setCursor(Qt::ArrowCursor);
}