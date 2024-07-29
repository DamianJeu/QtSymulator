#include "server.h"
#include <QHostInfo>
#include <QNetworkInterface>

Server::Server(QObject *parent) : QTcpServer(parent), clientSocket(nullptr)
{
    m_connectionCount = 0;

    qDebug() << "Server created!";

   // QObject::connect(this, &QTcpServer::acceptError, this, &Server::error);
}

Server::~Server()
{
    if(clientSocket != nullptr)
    {
        clientSocket->close();
        clientSocket->deleteLater();

    }

    this->close();
    qDebug() << "Server destroyed!";
}

bool Server::startServer(quint16 port)
{
    QHostAddress address = QHostAddress::AnyIPv4;

    if(!this->listen(address, port))
    {
        qDebug() << "Server could not start!";
        return false;
    }
    else
    {
        QHostAddress address = this->serverAddress();

        qDebug() << "Server address: " << address.toString();

        emit serverStarted();

        return true;
    }
}

bool Server::closeServer()
{
    if(this->isListening())
    {
        if(clientSocket != nullptr)
        {
            clientSocket->close();
            qDebug()<< "Client disconnected by server close!";
        }
        this->close();
        emit serverClosed();

        return true;
    }

    return false;
}

void Server::onClientReadyRead()
{

    QString data = clientSocket->readAll();

    qDebug() << "Data received: " << data;

    emit recivedMessage(data);
}

void Server::onClientDisconnected()
{
    clientSocket->deleteLater();
    clientSocket = nullptr;
    emit clientDisconnected();
    qDebug() << "Client disconnected, deleteing client socket!";
}

void Server::error(QAbstractSocket::SocketError socketError)
{
    QString error = clientSocket->errorString();
    emit errorSignal(error);
}

void Server::sentToClient(const QString & data)
{
    qDebug() << "Data sent to client: " << data;

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
        connect(clientSocket, &QTcpSocket::errorOccurred,this, &Server::error);
        qDebug() << "Client connected!";
    }

    qDebug()<< "New client connected from:"<< clientSocket->peerAddress().toString();
    emit clientConnected();
}


