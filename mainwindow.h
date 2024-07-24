#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "server.h"
#include <qcolumnview.h>
#include "filedialog.h"
#include "parser.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStartServer_clicked();
    void on_pushButtonStop_clicked();

    void on_pushButtonLoadFile_clicked();

    void on_pushButtonRandom_clicked();

private:
    Ui::MainWindow *ui;
    QColumnView *columnView;
    Server * server;
    FileDialog * dialog;
    Parser * parser;
};
#endif // MAINWINDOW_H
