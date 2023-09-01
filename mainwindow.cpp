#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include "qstartbutton.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(&mDb, &Qdb::preloadingPixmap,
            ui->lastScrLabel, &QPixmapLabel::recievePixmap);

    connect(&mDb, &Qdb::preloadingComparePercent,
            ui->percLabel, &QPercentCompareLabel::recievePercent);

    connect(ui->lastScrLabel, &QPixmapLabel::sendPixmap,
            ui->prevScrLabel, &QPixmapLabel::recievePixmap);

    mDb.firstLaunch();
    mScr.setPreloadPixmap(ui->lastScrLabel->pixmap(Qt::ReturnByValue));

    QStartButton* button = ui->startButton;

    connect(button, &QStartButton::makeScreenshot,
            &mScr, &QScreenshot::takeScreenshot);

    connect(&mScr, &QScreenshot::sendPixmap,
            ui->lastScrLabel, &QPixmapLabel::recievePixmap);

    connect(&mScr, &QScreenshot::sendComparePercent,
            ui->percLabel, &QPercentCompareLabel::recievePercent);

    connect(&mScr, &QScreenshot::sendToDb,
            &mDb, &Qdb::recieveNewSceenshot);

}

MainWindow::~MainWindow()
{
    delete ui;
}
