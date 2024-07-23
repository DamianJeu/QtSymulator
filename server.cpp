#include "server.h"
#include <QHostInfo>

Server::Server(QObject *parent) : QTcpServer(parent)
{



}

bool Server::startServer(quint16 port)
{
    if(!this->listen(QHostAddress::Any, port))
    {
        qDebug() << "Server could not start!";
        return false;
    }
    else
    {
        qDebug() << "Server started!";
        emit serverStared();
        return true;
    }

    QHostAddress address = this->serverAddress();

    qDebug() << "Server address: " << address.toString();
}

bool Server::closeServer()
{
    if(this->isListening())
    {
        this->close();
        emit serverClosed();
        qDebug() << "Server closed!";
        return true;
    }

    return false;
}

void Server::onClientReadyRead()
{

    QString data = clientSocket->readAll();
    qDebug() << "Data received: " << data;

}

void Server::onClientDisconnected()
{
    clientSocket->deleteLater();
    clientSocket = nullptr;
    qDebug() << "Client disconnected!";
}

void Server::clientSendData(QString &data)
{
    if(clientSocket != nullptr && clientSocket->state()==QAbstractSocket::ConnectedState)
    {
        clientSocket->write(data.toUtf8());
        clientSocket->flush();
    }
    else
    {
        qDebug() << "No client connected!";
    }
}


void Server::incomingConnection(qintptr handle)
{

    // if there is already a client connected, reject the new connection
    if(clientSocket != nullptr)
    {
        QTcpSocket tempSocket; // temp socket
        tempSocket.setSocketDescriptor(handle);
        tempSocket.disconnectFromHost();
        return;
    }

    clientSocket = new QTcpSocket(this);

    if(clientSocket->setSocketDescriptor(handle))
    {
        connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onClientReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
        qDebug() << "Client connected!";
    }

    qDebug()<< "New client connected from:"<< clientSocket->peerAddress().toString();

}


