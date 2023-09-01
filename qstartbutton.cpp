#include "qstartbutton.h"

QStartButton::QStartButton(QWidget* parent) :
    QPushButton(parent), mRemainingTime(10000)
{
    connect(this, &QPushButton::clicked, this, &QStartButton::toggleTimer);
    connect(&mTimer, &QTimer::timeout, this, &QStartButton::timerTimeout);
}

void QStartButton::toggleTimer() {
    if (mTimer.isActive()) {
        mRemainingTime = mTimer.remainingTime();
        mTimer.stop();
        setText("Start");
    } else {
        mTimer.start(mRemainingTime);
        setText("Stop");
    }
}

void QStartButton::timerTimeout() {
    emit makeScreenshot();
    mTimer.start(10000);
}
