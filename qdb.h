#pragma once

#include <QObject>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QBuffer>

class Qdb : public QObject
{
    Q_OBJECT

private:
    QSqlDatabase mSdb;
    QSqlQuery mQuery;

public:
    Qdb();
    void firstLaunch();

public slots:
    void recieveNewSceenshot(QPixmap, qint64, qint64);

signals:
    void preloadingPixmap(QPixmap);
    void preloadingComparePercent(qint64);
};

