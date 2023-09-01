#pragma once

#include <QMainWindow>
#include "qdb.h"
#include "Qscreenshot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

private:
    Ui::MainWindow *ui;
    Qdb mDb;
    QScreenshot mScr;
};
