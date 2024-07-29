#include "filedialog.h"

/**
 * @brief Constructor FileDialog class.
 */
FileDialog::FileDialog(QObject *parent)
    : QObject{parent}
{



}

/**
 * @brief Deconstructor FileDialog class.
 */
FileDialog::~FileDialog()
{
    qDebug() << "File dialog destroyed!";
}

/**
 * @brief Opens a dialog window to choose a file.
 *
 * Opens a dialog window to choose a file.
 */
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

/**
 * @brief Opens a file.
 *
 * Opens a file and reads it line by line.
 */
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

/**
 * @brief Returns text line with the given index.
 * @param quint64 line lineIndex.
 * @return QString fileLine
 */
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

/**
 * @brief Parses the data from the file.
 * @param const QString &data
 */
void FileDialog::dataParsed(const QString &data)
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
        emit endOfFileReached();
        qDebug()<<"End of file!";
    }
}

/**
 * @brief Returns the total number of lines in the file.
 * @return quint64 m_totalLines
 */
quint64 FileDialog::getLineCounter() const
{
    return m_lineCounter;
}

/**
 * @brief Sets the total number of lines in the file.
 * @param newTotalLines
 */
void FileDialog::setLineCounter(quint64 newLineCounter)
{
    m_lineCounter = newLineCounter;
}

