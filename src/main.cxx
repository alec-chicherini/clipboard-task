#include <clipboard_qt.h>
#include <clipboard_xcb.h>
#include <QCommandLineParser>
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QApplication::setApplicationName("clipboard-task");
  QApplication::setApplicationVersion("01.00");

  QCommandLineParser parser;
  parser.setApplicationDescription("clipboard-task");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption option_use_xcb(
      "xcb", QCoreApplication::translate("main", "Use xcb lib"));
  parser.addOption(option_use_xcb);

  QCommandLineOption option_use_qt(
      "qt", QCoreApplication::translate("main", "Use Qt lib"));
  parser.addOption(option_use_qt);

  QCommandLineOption option_file(
      "file", QCoreApplication::translate("main", "File to copy from <path>"),
      QCoreApplication::translate("main", "path"));
  parser.addOption(option_file);

  QCommandLineOption option_string(
      "string", QCoreApplication::translate("main", "String to copy <string>"),
      QCoreApplication::translate("main", "string"));
  parser.addOption(option_string);

  parser.process(app);
  const QStringList args = parser.positionalArguments();

  bool is_set_xcb = parser.isSet(option_use_xcb);
  bool is_set_qt = parser.isSet(option_use_qt);
  bool is_set_file = parser.isSet(option_file);
  bool is_set_string = parser.isSet(option_string);

  if ((is_set_xcb && is_set_qt) || (!is_set_xcb && !is_set_qt)) {
    qDebug() << "ОШИБКА выбора библиотеки. Выберите библиотеку qt или xcb. "
                "\nclipboard-task --help \n";
    exit(1);
  }
  if ((is_set_file && is_set_string) || (!is_set_file && !is_set_string)) {
    qDebug() << "ОШИБКА.Укажите одну из опций file или string\nclipboard-task "
                "--help \n";
    exit(1);
  }

  IClipboard *clipboard;
  if (is_set_qt) {
    clipboard = new ClipboardQt();
  } else if (is_set_xcb) {
    clipboard = new ClipboardXcb();
  }

  if (is_set_string) {
    QString string_value = parser.value(option_string);
    clipboard->CopyString(string_value);
  } else if (is_set_file) {
    QString file_path = parser.value(option_file);
    clipboard->CopyFile(file_path);
  }

  return app.exec();
}
