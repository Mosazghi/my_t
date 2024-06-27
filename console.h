#pragma once
#include <QTextEdit>

class Console : public QTextEdit {
  Q_OBJECT
public:
  explicit Console(QWidget *parent = nullptr);
  void updateConsole(const QString &data, const bool showTime,
                     const bool autoScroll);
  void clearConsole();
};
