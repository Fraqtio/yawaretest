#pragma once

#include <QPixmap>
#include <QObject>
#include <QScreen>
#include <QGuiApplication>
#include <QThreadPool>
#include <QtConcurrent/QtConcurrent>
#include <QImage>

class QScreenshot : public QObject
{
    Q_OBJECT

private:
    QPixmap mPixmap;
    qint64 mCache;
    qint64 mComparePercent;
    void compare(QPixmap, QPixmap);

public:
    QScreenshot();
    void setPreloadPixmap(QPixmap);

public slots:
    void takeScreenshot();

signals:
    void sendPixmap(QPixmap);
    void sendComparePercent(qint64);
    void sendToDb(QPixmap, qint64, qint64);
};
