#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "server.h"
#include <qcolumnview.h>
#include "filedialog.h"

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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QColumnView *columnView;
    Server server;
    FileDialog dialog;
};
#endif // MAINWINDOW_H
