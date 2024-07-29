#include "server.h"
#include <QHostInfo>
#include <QNetworkInterface>

/**
 * @brief Constructor Server class.
 */
Server::Server(QObject *parent) : QTcpServer(parent), clientSocket(nullptr)
{
    m_connectionCount = 0;

    qDebug() << "Server created!";

}

/**
 * @brief Deconstructor Server class.
 */
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

/**
 * @brief Starts the server.
 *
 * @param quint16 port Port number
 * @return bool true if server started successfully, false otherwise
 *
 * This method is responsible for starting the server.
 */
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

/**
 * @brief Closes the server.
 *
 * @return bool true if server closed successfully, false otherwise
 *
 * This method is responsible for closing the server.
 */
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

/**
 * @brief Slot called when data is received from the client.
 */
void Server::onClientReadyRead()
{

    QString data = clientSocket->readAll();

    qDebug() << "Data received: " << data;

    emit recivedMessage(data);
}

/**
 * @brief Slot called when client is disconnected.
 */
void Server::onClientDisconnected()
{
    clientSocket->deleteLater();
    clientSocket = nullptr;
    emit clientDisconnected();
    qDebug() << "Client disconnected, deleteing client socket!";
}

/**
 * @brief Slot called when error occurs.
 *
 * @param QAbstractSocket::SocketError socketError
 */
void Server::error(QAbstractSocket::SocketError socketError)
{
    QString error = clientSocket->errorString();
    emit errorSignal(error);
}

/**
 * @brief Sends data to the client.
 *
 * @param const QString & data Data to be sent to the client
 */
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


/**
 * @brief Slot called when new connection is established.
 *
 * @param qintptr handle
 */
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


