#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextBrowser>
#include <QNetworkInterface>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<QHostAddress> allAddresses = QNetworkInterface::allAddresses();
    //QList<QHostAddress> ipv4Addresses;
    // Get all network interfaces address
    for (const auto &networkInterface : allAddresses) {

        if(networkInterface.protocol() == QAbstractSocket::IPv4Protocol)
        {
            ui->textBrowserNetwork->append(networkInterface.toString());
        }

    }

    // create object
    server = new Server(this);
    dialog = new FileDialog(this);
    parser = new Parser(this);

    //connect singal & slots
    QObject::connect(server, &Server::recivedMessage, parser, &Parser::newDataReceived, Qt::ConnectionType::AutoConnection);
    QObject::connect(parser, &Parser::dataParsed, dialog, &FileDialog::dataParsed, Qt::ConnectionType::AutoConnection);
    QObject::connect(dialog, &FileDialog::sendToServer, server, &Server::sentToClient, Qt::ConnectionType::AutoConnection);
    QObject::connect(dialog, &FileDialog::loadingProgress, this, &MainWindow::progressChanged, Qt::ConnectionType::AutoConnection);

}

MainWindow::~MainWindow()
{

    qDebug()<<"Main window destroyed!";
    delete ui;

}

void MainWindow::on_pushButtonStartServer_clicked()
{
    qDebug()<<"Trying to start server!";

    if(server->startServer(1234))
    {
        qDebug()<<"Server started!";
        ui->progressBar->setValue(0);
    }

}



void MainWindow::on_pushButtonStop_clicked()
{
    if(server->closeServer())
    {
        qDebug()<<"Server closed!";
    }
    else
    {
        qDebug()<<"Server could not close!";
    }

    ui->progressBar->setValue(0);
}


void MainWindow::on_pushButtonLoadFile_clicked()
{
    dialog->openFolderDialog();
}


void MainWindow::on_pushButtonRandom_clicked()
{


}

void MainWindow::progressChanged(int progress)
{
    ui->progressBar->setValue(progress);
    // qDebug()<<"Progress: "<<progress;
}


void MainWindow::on_pushButtonResetFilePointer_clicked()
{
    dialog->setLineCounter(0);
}

