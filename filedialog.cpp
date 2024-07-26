#include "filedialog.h"

FileDialog::FileDialog(QObject *parent)
    : QObject{parent}
{



}

FileDialog::~FileDialog()
{
    qDebug() << "File dialog destroyed!";
}

void FileDialog::openFolderDialog()
{
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Wybierz plik"), "/home",tr("Text files (*.txt)"));

    if (!path.isEmpty())
    {
        filePath=path;
        qDebug () << "Folder path: " << filePath;
        openFile();
    }
}



void FileDialog::openFile()
{


    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open file!";
        return;
    }

    QTextStream in(&file);

    m_totalLines = 0;

    while (!in.atEnd())
    {
        in.readLine();
        m_totalLines++;
    }

    qDebug() << "Total lines: " << m_totalLines;
    in.seek(0);


    m_lineCounter=0;

    if(!fileLine.isEmpty())
    {
        fileLine.clear();
    }


    quint8 percent;

    while (!in.atEnd())
    {
        QString line = in.readLine();
        fileLine[m_lineCounter++] = line;
        qDebug()<<line;

        quint8 newPercent = (m_lineCounter * 100) / m_totalLines;
        if (newPercent != percent)
        {
            percent = newPercent;
            emit loadingProgress(percent);
        }
    }
    file.close();
    qDebug() << "File closed!";

     m_lineCounter=0;


}

QString FileDialog::getFileLine(quint64 line)
{

    if(fileLine.contains(line))
    {
        return fileLine[line];
    }
    else
    {
        return nullptr;
    }


}

void FileDialog::dataParsed(QString data)
{
    static quint8 percent;

    if(getFileLine(m_lineCounter++)!=nullptr)
    {
        emit sendToServer(getFileLine(m_lineCounter));

        quint8 newPercent = (m_lineCounter * 100) / m_totalLines;
        if (newPercent != percent)
        {
            percent = newPercent;
            emit loadingProgress(percent);
        }
    }
    else
    {
        qDebug()<<"End of file!";
    }
}

quint64 FileDialog::getLineCounter() const
{
    return m_lineCounter;
}

void FileDialog::setLineCounter(quint64 newLineCounter)
{
    m_lineCounter = newLineCounter;
}

