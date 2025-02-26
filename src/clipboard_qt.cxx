#include <clipboard_qt.h>
#include <QClipboard>
#include <QMimeData>
#include <QApplication>
#include <QDebug>
void ClipboardQt::CopyString(const QString &string_value) {
  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(string_value, QClipboard::Clipboard);
  qDebug() << "Close app. Ctrl+C\n";
}

void ClipboardQt::CopyFile(const QString &file_path_cref) {
  QString file_path = file_path_cref;
  QClipboard *clipboard = QApplication::clipboard();
  clipboard->setText(file_path, QClipboard::Clipboard);
  QMimeData *mimeData = new QMimeData();
  mimeData->setData("text/plain;charset=utf-8", file_path.toUtf8());
  mimeData->setData("text/uri-list", file_path.prepend("file://").toUtf8());
  mimeData->setData("x-special/gnome-copied-files",
                    (QString("copy\n%1").arg(file_path)).toUtf8());
  mimeData->setData("x-special/mate-copied-files",
                    (QString("copy\n%1").arg(file_path)).toUtf8());
  clipboard->setMimeData(mimeData, QClipboard::Clipboard);
  qDebug() << "Do not close app untill file in clipboard\n";
}
