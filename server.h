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

signals:

    // QTcpServer interface

private slots:
    void onClientReadyRead();
    void onClientDisconnected();
    void clientSendData(QString & data);


protected:
    void incomingConnection(qintptr handle) override;


private:
    QTcpSocket * client;
    quint16 connectionCount;
};

#endif // SERVER_H
