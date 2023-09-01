#pragma once

#include <QObject>
#include <QLabel>

class QPixmapLabel : public QLabel
{
    Q_OBJECT

private:
    void resizeEvent(QResizeEvent*);
    QPixmap mPixmap;

public:
    QPixmapLabel(QWidget* parent = nullptr);

public slots:
    void recievePixmap(QPixmap);

signals:
    void sendPixmap(QPixmap);
};
