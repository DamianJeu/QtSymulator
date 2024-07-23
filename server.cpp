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

