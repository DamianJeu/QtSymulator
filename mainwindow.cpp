#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextBrowser>
#include <QNetworkInterface>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Server server(this);
    FileDialog dialog(this);

    foreach (const auto &networkInterface, QNetworkInterface::allAddresses()) {
        ui->textBrowserNetwork->append(networkInterface.toString());
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonStartServer_clicked()
{
    qDebug()<<"Trying to start server!";

    if(server.startServer(1234))
    {
        qDebug()<<"Server started!";
    }



}



void MainWindow::on_pushButtonStop_clicked()
{
    if(server.closeServer())
    {
        qDebug()<<"Server closed!";
    }
    else
    {
        qDebug()<<"Server could not close!";
    }
}


void MainWindow::on_pushButton_clicked()
{
    dialog.openFolderDialog();
}

