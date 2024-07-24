#ifndef PARSER_H
#define PARSER_H

#include <QObject>

class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);

    ~Parser();

public slots:

    bool newDataReceived(QString data);

signals:

    void dataParsed(QString data);

};

#endif // PARSER_H
