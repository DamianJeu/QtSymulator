#include "parser.h"
#include <QDebug>

Parser::Parser(QObject *parent)
    : QObject{parent}
{



}

Parser::~Parser()
{
    qDebug() << "Parser destroyed!";
}

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
