#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>


/**
 * @class Server
 * @brief Handles the server side of the application
 *
 * Handles the server side of the application, creates and manages the server socket.
 */

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    ~Server();

    bool startServer(quint16 port);
    bool closeServer();

signals:
    void serverClosed();                            //emited when server is closed
    void serverStarted();                           //emited when server is started
    void recivedMessage(const QString &data);       //emited when message is received from
    void clientConnected();                         //emited when client is connected
    void clientDisconnected();                      //emited when client is disconnected
    void errorSignal(const QString &error);         //emited when error occurs
    // void

public slots:
    void sentToClient(const QString &data);

private slots:
    void onClientReadyRead();
    void onClientDisconnected();
    void error(QAbstractSocket::SocketError socketError);

protected:
    void incomingConnection(qintptr handle) override;

private:
    QTcpSocket * clientSocket;
    quint16 m_connectionCount;
};

#endif // SERVER_H
