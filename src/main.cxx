#include <clipboard_qt.h>
#include <clipboard_x11.h>

#include <QApplication>
#include <QCommandLineParser>
#include <QDebug>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  QApplication::setApplicationName("clipboard-task");
  QApplication::setApplicationVersion("01.00");

  QCommandLineParser parser;
  parser.setApplicationDescription("clipboard-task");
  parser.addHelpOption();
  parser.addVersionOption();

  QCommandLineOption option_use_qt(
      "qt", QCoreApplication::translate("main", "Use Qt lib"));
  parser.addOption(option_use_qt);

  QCommandLineOption option_use_x11(
      "x11", QCoreApplication::translate("main", "Use X11/Xlib"));
  parser.addOption(option_use_x11);

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

  bool is_set_qt = parser.isSet(option_use_qt);
  bool is_set_x11 = parser.isSet(option_use_x11);
  bool is_set_file = parser.isSet(option_file);
  bool is_set_string = parser.isSet(option_string);

  int number_of_libs =
      static_cast<int>(is_set_qt) + static_cast<int>(is_set_x11);
  if (number_of_libs != 1) {
    qDebug()
        << "ОШИБКА выбора библиотеки. Выберите библиотеку qt или x11. "
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
  } else if (is_set_x11) {
    clipboard = new ClipboardX11();
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
