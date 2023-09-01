#include "qpercentcomparelabel.h"

QPercentCompareLabel::QPercentCompareLabel(QWidget* parent) :
    QLabel(parent)
{
}

void QPercentCompareLabel::recievePercent(qint64 percent) {
    setText(QString::number(percent));
}
