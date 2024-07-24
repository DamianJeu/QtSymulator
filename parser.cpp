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

bool Parser::newDataReceived(QString data)
{

    qDebug() << this << "Data received";


    emit dataParsed(data);

    return true;
}
