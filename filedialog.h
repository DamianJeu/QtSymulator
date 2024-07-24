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


public slots:
    void openFolderDialog();
    void openFile();
    QString getFileLine(quint64 line);
    void dataParsed(QString data);

signals:

    void sendToServer(QString data);


private:
    QString filePath;
    QMap<quint64, QString> fileLine;

signals:
};

#endif // FILEDIALOG_H
