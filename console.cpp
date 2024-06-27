
#include "console.h"
#include <QScrollBar>
#include <QTime>

Console::Console(QWidget *parent) : QTextEdit(parent) {
  this->setObjectName("console");
  this->setReadOnly(true);
}

void Console::updateConsole(const QString &data, const bool showTimestamp,
                            const bool autoScroll) {
  QString formattedData;

  if (!showTimestamp) {
    formattedData = data;
  } else {
    const QString time = QTime::currentTime().toString("hh:mm:ss");
    formattedData = QString("<i>[%1]</i> -> %2").arg(time).arg(data);
  }
  this->append(formattedData);

  if (autoScroll) {
    // Scroll to bottom
    QScrollBar *sb = this->verticalScrollBar();
    sb->setValue(sb->maximum());
  }
}

void Console::clearConsole() { this->clear(); }
