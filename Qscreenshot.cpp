#include "Qscreenshot.h"

QScreenshot::QScreenshot()
{
}

void QScreenshot::setPreloadPixmap(QPixmap preloadedPixmap)
{
    if (!preloadedPixmap.isNull())
        mPixmap = preloadedPixmap;
}

void QScreenshot::compare(QPixmap fPM, QPixmap sPM) {
        QImage firstGrayImage = fPM.scaled(QSize(32, 32))
                                    .toImage()
                                    .convertToFormat(QImage::Format_Grayscale8);
        QImage secondGrayImage = sPM.scaled(QSize(32, 32))
                                     .toImage()
                                     .convertToFormat(QImage::Format_Grayscale8);

        qint64 distance = 0;
        for (qint64 h = 0; h < firstGrayImage.height(); h++) {
        for (qint64 w = 0; w < firstGrayImage.width(); w++) {
            distance += qAbs(qGray(firstGrayImage.pixel(h, w))
                             - qGray(secondGrayImage.pixel(h, w)));
        }
        }

        double koef = (100 * distance) / (256 * 32 * 32);
        qint64 result = 100 - koef;
        mComparePercent = result;
}

void QScreenshot::takeScreenshot() {
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap newPixmap;
    newPixmap = screen->grabWindow(0);

    if (mPixmap.isNull()) {
        mCache = newPixmap.cacheKey();
        mPixmap = newPixmap;
        emit sendPixmap(newPixmap);
        emit sendComparePercent(0);
        emit sendToDb(mPixmap, mCache, 0);
        return;
    }

    QFuture<void> future = QtConcurrent::run([=]() {
        compare(mPixmap, newPixmap);
    });
    future.waitForFinished();
    mCache = newPixmap.cacheKey();
    mPixmap = newPixmap;

    emit sendPixmap(newPixmap);
    emit sendComparePercent(mComparePercent);
    emit sendToDb(mPixmap, mCache, mComparePercent);

}




