#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Server server(this);
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
    else
    {
        qDebug()<<"Server could not start!";
    }

}



void MainWindow::on_pushButtonDisconnect_clicked()
{



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

