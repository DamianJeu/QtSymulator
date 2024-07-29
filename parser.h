#ifndef PARSER_H
#define PARSER_H

#include <QObject>


/**
 * @class Parser
 * @brief Parses data received from the client
 *
 * Parses data received from the client and emits the parsed data.
 *  part of the i2c driver could be implemented here
 */
class Parser : public QObject
{
    Q_OBJECT
public:
    explicit Parser(QObject *parent = nullptr);

    ~Parser();

public slots:

    bool newDataReceived(const QString &data);

signals:

    void dataParsed(const QString &data);
    void dataPointerReset();

};

#endif // PARSER_H
