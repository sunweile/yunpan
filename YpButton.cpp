#include "YpButton.h"
#pragma execution_character_set("utf-8")
YpButton::YpButton(QWidget* parent, bool allUse = false)
    : QToolButton(parent) {
    useHoveringActivationTimer = NULL;
    timer = NULL;
    isLeftChick = allUse;
    isRightChick = allUse;
    isLeftDown = allUse;
    isRightUp = allUse;
    isLeftUp = allUse;
    isRightDown = allUse;
    isDoubleChick = allUse;
    isHoveringActivation = allUse;
    isActivation = allUse;
    isUseActivation = allUse;
    setUnused();
    hoveringActivationTime = 0;
    time = -1;
    chickTimes = 0;
}

YpButton::~YpButton() {
    timerDelete();
}
void YpButton::focusOutEvent(QFocusEvent* e) {
    if (isUseActivation) {
        unActivation();
    }
    emit focusOut();
}

void YpButton::enterEvent(QEvent* event) {
    if (isHoveringActivation) {
        if (useHoveringActivationTimer == NULL) {
            useHoveringActivationTimer = new QTimer(this);
        }
        useHoveringActivationTimer->setSingleShot(true);
        useHoveringActivationTimer->start(hoveringActivationTime == 0 ? 1 : hoveringActivationTime);
        connect(useHoveringActivationTimer, SIGNAL(timeout()), this, SLOT(doHoveringActivation()));
    }
    if (!isUsed()) { return; }
    if (!isUseActivation || !isActivation) {
        buttonType = Enter;
        this->setStyleSheet(mouseEnterStyle);
    }
}

void YpButton::leaveEvent(QEvent* event) {
    if (isHoveringActivation) {
        if (useHoveringActivationTimer != NULL) {
            useHoveringActivationTimer->stop();
            delete useHoveringActivationTimer;
            useHoveringActivationTimer = NULL;
        }
    }
    if (!isUsed()) { return; }
    if (!isUseActivation || !isActivation) {
        buttonType = Leave;
        this->setStyleSheet(mouseLeaveStyle);
    }
}

void YpButton::mousePressEvent(QMouseEvent* event)
{
    if (!isUsed()) { return; }
    // 鼠标左键按下
    if (event->button() == Qt::LeftButton) {
        if (isLeftDown) {
            buttonType = Chick;
            this->setStyleSheet(mouseChickStyle);
            emit leftDown();
        }
        if (isLeftChick) {
            buttonType = Chick;
            this->setStyleSheet(mouseChickStyle);
        }
        if (time == -1) {
            time = 0;
            chickTimes = 0;
            timerInit();
        }
    }
    // 鼠标右键按下
    else if (event->button() == Qt::RightButton) {
        if (isRightDown) {
            emit rightDown();
        }
    }
}

void YpButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (!isUsed()) { return; }
    // 鼠标左键松开
    if (event->button() == Qt::LeftButton) {   
        if (!isUseActivation) {
            this->setStyleSheet(mouseEnterStyle);
        }else {
            isActivation = true;
        }
        if (isLeftUp) {
            emit leftUp();
        }
        if (isLeftChick) {
            emit leftChick();
        }
        if (isDoubleChick) {
            if (time != -1 && time <= 3 && chickTimes == 0) {
                chickTimes = 1;
                time = 0;
            }else if (time != -1 && time <= 6 && chickTimes == 1) {
                chickTimes = 0;
                time = -1;
                timerStop();
                emit doubleChick();
            }
        }
    }
    // 鼠标右键松开
    else if (event->button() == Qt::RightButton) {
        if (isRightUp) {
            emit rightUp();
        }
    }
}

void YpButton::timerStop() {
    timer->stop();
}

void YpButton::timerDelete() {
    delete timer;
}

void YpButton::timerInit() {
    if (timer == NULL) {
        timer = new QTimer(this);
    }
    timer->setSingleShot(false);
    timer->start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpOn()));
}

void YpButton::timeUpOn() {
    if (time >= 0) {
        time++;
    }
    if (time == 7) {
        timerStop();
    }
}

void YpButton::setMouseEnterStyle(const QString& str) {
    mouseEnterStyle = str;
    if (buttonType == Enter) {
        this->setStyleSheet(str);
    }
}
void YpButton::setMouseLeaveStyle(const QString& str) {
    mouseLeaveStyle = str;
    if (buttonType == Leave) {
        this->setStyleSheet(str);
    }
}
void YpButton::setMouseChickStyle(const QString& str) {
    mouseChickStyle = str;
    if (buttonType == Chick) {
        this->setStyleSheet(str);
    }
}
void YpButton::setMouseUnuseStyle(const QString& str) {
    mouseUnuseStyle = str;
    if (buttonType == Unuse) {
        this->setStyleSheet(str);
    }
}
void YpButton::useHoveringActivation(bool b, int ms) {
    isHoveringActivation = b;
    hoveringActivationTime = ms;
}
void YpButton::doHoveringActivation() {
    if (isHoveringActivation) {
        if (useHoveringActivationTimer != NULL) {
            useHoveringActivationTimer->stop();
            delete useHoveringActivationTimer;
            useHoveringActivationTimer = NULL;
        }
        emit hoveringActivation();
    }
}
void YpButton::setUnused() {
    buttonType = Unuse;
    this->setStyleSheet(mouseUnuseStyle);
}
void YpButton::setUsed() {
    buttonType = Leave;
    this->setStyleSheet(mouseLeaveStyle);
}
void YpButton::useLeftChick(bool b) {
    isLeftChick = b;
}
void YpButton::useRightChick(bool b) {
    isRightChick = b;
}
void YpButton::useLeftDown(bool b) {
    isLeftDown = b;
}
void YpButton::useRightUp(bool b) {
    isRightUp = b;
}
void YpButton::useLeftUp(bool b) {
    isLeftUp = b;
}
void YpButton::useRightDown(bool b) {
    isRightDown = b;
}
void YpButton::useDoubleChick(bool b) {
    isDoubleChick = b;
}
void YpButton::useActivation(bool b) {
    isUseActivation = b;
    isLeftChick = b;
}
void YpButton::unActivation() {
    isActivation = false;
    this->setStyleSheet(mouseLeaveStyle);
}
bool YpButton::isActivationNow() {
    return isActivation;
}
bool YpButton::isLeave() {
    return Leave == buttonType;
}
bool YpButton::isEnter() {
    return Enter == buttonType;
}
bool YpButton::isChick() {
    return Chick == buttonType;
}
bool YpButton::isUsed() {
    return Unuse != buttonType;
}