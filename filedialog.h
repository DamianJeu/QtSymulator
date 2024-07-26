#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QLabel>
#include <QFileDialog>
#include <QIODevice>
#include <QTextStream>
#include <QFile>


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
    void dataParsed(QString data);

signals:

    void sendToServer(QString data);
    void loadingProgress(int progress);


private:
    QString filePath;
    QMap<quint64, QString> fileLine;

    quint64 m_totalLines;
    quint64 m_lineCounter;


signals:
};

#endif // FILEDIALOG_H
