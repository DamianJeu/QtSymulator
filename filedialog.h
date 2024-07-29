#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QLabel>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>
#include <QFile>


/**
 * @class FileDialog
 * @brief Handling system files.
 *
 * Allows to open a txt file and handle it for the simulator's needs
 */
class FileDialog : public QObject
{
    Q_OBJECT
public:
    explicit FileDialog(QObject *parent = nullptr);

    ~FileDialog();

    quint64 totalLines() const;
    void setTotalLines(quint64 newTotalLines);
    quint64 getLineCounter() const;
    void setLineCounter(quint64 newLineCounter);

public slots:
    void openFolderDialog();
    void openFile();
    QString getFileLine(quint64 line);
    void dataParsed(const QString &data);

signals:

    void sendToServer(const QString &data);
    void loadingProgress(int progress);
    void endOfFileReached();

private:
    QString filePath;
    QMap<quint64, QString> fileLine;

    quint64 m_totalLines;
    quint64 m_lineCounter;


signals:
};

#endif // FILEDIALOG_H
