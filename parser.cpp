#include "parser.h"
#include <QDebug>

/**
 * @brief Constructor Parser class.
 */
Parser::Parser(QObject *parent)
    : QObject{parent}
{



}

/**
 * @brief Deconstructor Parser class.
 */
Parser::~Parser()
{
    qDebug() << "Parser destroyed!";
}


/**
 * @brief Parses data received from the client.
 *
 * @param const QString & data Data received from the client
 * @return bool
 *
 *
 *  This method is responsible for parsing the data received from the client.
 */
bool Parser::newDataReceived(const QString &data)
{
    qDebug() << this << "Data received";

    if(data == "RST")
    {
        emit dataPointerReset();
        return false;
    }

    emit dataParsed(data);

    return true;
}
