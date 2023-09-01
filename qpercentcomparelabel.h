#pragma once

#include <QLabel>
#include <QObject>

class QPercentCompareLabel : public QLabel
{
    Q_OBJECT

public:
    QPercentCompareLabel(QWidget* parent = nullptr);

public slots:
    void recievePercent(qint64);
};
