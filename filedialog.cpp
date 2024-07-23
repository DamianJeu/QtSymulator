#include "filedialog.h"

FileDialog::FileDialog(QObject *parent)
    : QObject{parent}
{



}

void FileDialog::openFolderDialog()
{
    QString folderPath = QFileDialog::getOpenFileName(nullptr, tr("Wybierz plik"), "/home",tr("Text files (*.txt)"));

    if (!folderPath.isEmpty())
    {
        folderPath=folderPath;
        qDebug () << "Folder path: " << folderPath;
    }
}
