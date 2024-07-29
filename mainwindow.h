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

signals:

    void sendEndOfFileReached(const QString &data);

private slots:
    void on_pushButtonStartServer_clicked();
    void on_pushButtonStop_clicked();
    void on_pushButtonLoadFile_clicked();
    void progressChanged(int progress);
    void on_pushButtonResetFilePointer_clicked();
    void clientDisconnected();
    void clientConnected();
    void addServerErrorToLogs(const QString &error);
    void serverStarted();
    void serverClosed();
    void on_pushButton_clicked();
    void endOfFileReached();

    void on_checkBoxFileLoop_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QColumnView *columnView;
    Server * server;
    FileDialog * dialog;
    Parser * parser;

    bool loopFile;
};
#endif // MAINWINDOW_H
