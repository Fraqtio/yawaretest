#include "qdb.h"

Qdb::Qdb()
{
    mSdb = QSqlDatabase::addDatabase("QSQLITE");
    mSdb.setDatabaseName("scr.db");
    mSdb.open();

    mQuery = QSqlQuery(mSdb);
    mQuery.exec("CREATE TABLE IF NOT EXISTS \
                Screenshots(screenshot BLOB NOT NULL, \
                            cache INT64 NOT NULL, \
                            percent INT64 NOT NULL)");
}

void Qdb::firstLaunch() {
    mQuery.exec("SELECT * FROM Screenshots ORDER BY screenshot DESC LIMIT 2");
    while (mQuery.next()) {
        emit preloadingComparePercent(mQuery.value("percent").toInt());

        QPixmap tempPixmap;
        tempPixmap.loadFromData(mQuery.value("screenshot").toByteArray());
        emit preloadingPixmap(tempPixmap);
    }
}

void Qdb::recieveNewSceenshot(QPixmap pixmap, qint64 cache, qint64 percent) {
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "JPG");
    buffer.close();

    mQuery.prepare("INSERT INTO Screenshots (screenshot, cache, percent) \
                   VALUES (?, ?, ?)");
    mQuery.addBindValue(byteArray);
    mQuery.addBindValue(cache);
    mQuery.addBindValue(percent);
    mQuery.exec();
}
