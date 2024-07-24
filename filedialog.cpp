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

    QString line = in.readLine();
    quint64 lineCounter = 0;

    if(!fileLine.isEmpty())
    {
        fileLine.clear();
    }

    while(!line.isNull())
    {
        qDebug() << line;
        line = in.readLine();
        fileLine[lineCounter++] = line;


    }
    file.close();
    qDebug() << "File closed!";


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


    static quint64 line = 0;

    if(getFileLine(line++)!=nullptr)
    {
        emit sendToServer(getFileLine(line));
    }
    else
    {
        line=0;
        qDebug()<<"End of file!";
    }


}
