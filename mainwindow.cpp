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
    QObject::connect(parser, &Parser::dataPointerReset, this, &MainWindow::on_pushButtonResetFilePointer_clicked, Qt::ConnectionType::AutoConnection);
    QObject::connect(server, &Server::clientConnected, this, &MainWindow::clientConnected, Qt::ConnectionType::AutoConnection);
    QObject::connect(server, &Server::clientDisconnected, this, &MainWindow::clientDisconnected, Qt::ConnectionType::AutoConnection);
    QObject::connect(server, &Server::errorSignal, this, &MainWindow::addServerErrorToLogs, Qt::ConnectionType::AutoConnection);
    QObject::connect(server, &Server::serverStarted, this, &MainWindow::serverStarted, Qt::ConnectionType::AutoConnection);
    QObject::connect(server, &Server::serverClosed, this, &MainWindow::serverClosed, Qt::ConnectionType::AutoConnection);
    QObject::connect(dialog, &FileDialog::endOfFileReached, this,&MainWindow::endOfFileReached, Qt::ConnectionType::AutoConnection);
    QObject::connect(this, &MainWindow::sendEndOfFileReached, server, &Server::sentToClient, Qt::ConnectionType::AutoConnection);
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
        dialog->setLineCounter(0);
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
    //ui->progressBar->setValue(0);
}


void MainWindow::on_pushButtonLoadFile_clicked()
{
    dialog->openFolderDialog();
}

void MainWindow::progressChanged(int progress)
{
    ui->progressBar->setValue(progress);
    // qDebug()<<"Progress: "<<progress;
}

void MainWindow::on_pushButtonResetFilePointer_clicked()
{
    dialog->setLineCounter(0);
    ui->progressBar->setValue(0);
}

void MainWindow::clientDisconnected()
{
    ui->labelConnectionStatus->setText("Disconnected");
    ui->labelConnectionStatus->setStyleSheet("QLabel { background-color : default; }");
    qDebug()<<"Client disconnected!";
}

void MainWindow::clientConnected()
{
    ui->labelConnectionStatus->setText("Connected");
    ui->labelConnectionStatus->setStyleSheet("QLabel { background-color : green; }");
    qDebug()<<"Client connected!";
}

void MainWindow::addServerErrorToLogs(const QString &error)
{
    ui->textBrowserNetwork->setTextColor(QColorConstants::Red);
    ui->textBrowserNetwork->append(error);
    ui->textBrowserNetwork->setTextColor(QColorConstants::White);
}

void MainWindow::serverStarted()
{
    ui->textBrowserNetwork->append("Server started!");
}

void MainWindow::serverClosed()
{
    ui->textBrowserNetwork->append("Server closed!");
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowserNetwork->clear();
}

void MainWindow::endOfFileReached()
{
    ui->textBrowserNetwork->append("End of file !");

    if(loopFile)
    {
        dialog->setLineCounter(0);
        ui->progressBar->setValue(0);
    }
    else
    {
        ui->progressBar->setValue(0);
        emit sendEndOfFileReached("EOF");
    }
}

void MainWindow::on_checkBoxFileLoop_stateChanged(int arg1)
{
    if(arg1)loopFile = true;
    else loopFile = false;

    qDebug()<<"Loop file: "<<loopFile;
}

