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



    // QTcpServer interface

private slots:
    void onClientReadyRead();
    void onClientDisconnected();
    void clientSendData(QString & data);


protected:
    void incomingConnection(qintptr handle) override;


private:
    QTcpSocket * clientSocket;
    quint16 m_connectionCount;
};

#endif // SERVER_H
