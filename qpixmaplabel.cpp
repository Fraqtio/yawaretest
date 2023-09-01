#include "qpixmaplabel.h"

QPixmapLabel::QPixmapLabel(QWidget* parent) :
    QLabel(parent)
{
}

void QPixmapLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    setPixmap(mPixmap.scaled(size(), Qt::KeepAspectRatio));
}

void QPixmapLabel::recievePixmap(QPixmap pm) {
    if (!mPixmap.isNull())
        emit QPixmapLabel::sendPixmap(mPixmap);
    mPixmap = pm;
    setPixmap(mPixmap.scaled(size(), Qt::KeepAspectRatio));
}

