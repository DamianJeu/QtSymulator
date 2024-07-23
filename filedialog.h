#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QLabel>
#include <QFileDialog>

class FileDialog : public QObject
{
    Q_OBJECT
public:
    explicit FileDialog(QObject *parent = nullptr);


public slots:
    void openFolderDialog();

private:
    QString folderPath;

signals:
};

#endif // FILEDIALOG_H
