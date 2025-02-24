#include <QCommandLineParser>
#include <QCoreApplication>
#include <QDebug>
#include <clipboard_qt.h>
#include <clipboard_xcb.h>
int main(int argc, char *argv[]) {
  QCoreApplication app(argc, argv);
  QCoreApplication::setApplicationName("clipboard-task");
  QCoreApplication::setApplicationVersion("01.00");

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

  if (is_set_xcb && is_set_qt || !is_set_xcb && !is_set_qt) {
    qDebug()
        << "ОШИБКА. qt или xcb не указано. Выберите библиотеку qt или xcb\n";
    exit(1);
  }
  if (is_set_file && is_set_string || !is_set_file && !is_set_string) {
    qDebug() << "ОШИБКА.Укажите одну из опций file или string\n";
    exit(1);
  }

  if (is_set_file) {
    QString file_path = parser.value(option_file);
    qDebug() << "file_path = " << file_path;
    if (is_set_qt) {
      // qt copy file
    } else if (is_set_xcb) {
      // xcb copy file
    }
  } else if (is_set_string) {
    QString string_value = parser.value(option_string);
    qDebug() << "string_value = " << string_value;
    if (is_set_qt) {
      // qt copy string
    } else if (is_set_xcb) {
      // xcb copy string
    }
  }

  app.exec();
}
