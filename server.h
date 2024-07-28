#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    ~Server();

    bool startServer(quint16 port);
    bool closeServer();

signals:
    void serverClosed();
    void recivedMessage(QString data);
    void clientConnected();
    void clientDisconnected();

public slots:
    void sentToClient(QString data);

    // QTcpServer interface
private slots:
    void onClientReadyRead();
    void onClientDisconnected();


protected:
    void incomingConnection(qintptr handle) override;


private:
    QTcpSocket * clientSocket;
    quint16 m_connectionCount;
};

#endif // SERVER_H
