#pragma once

#include <QObject>
#include <QPushButton>
#include <QTimer>

class QStartButton : public QPushButton
{
    Q_OBJECT

public:
    QStartButton(QWidget* parent = nullptr);

private:
    QTimer mTimer;
    qint64 mRemainingTime;

public slots:
    void toggleTimer();
    void timerTimeout();

signals:
    void makeScreenshot();
};
