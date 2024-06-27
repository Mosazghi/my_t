#include "mainwindow.h"

#include <QApplication>
#include <QFile>
// Hello
//
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // load the stylesheet
  QFile file(":/styles/styles.qss");
  file.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(file.readAll());
  a.setStyleSheet(styleSheet);

  MainWindow w;
  w.show();
  return a.exec();
}
