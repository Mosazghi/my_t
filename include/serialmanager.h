#pragma once
#include "common.h"
#include <QByteArray>
#include <QSerialPort>
#include <QToolBar>

class SerialManager : public QSerialPort {
public:
  SerialManager(Settings settings);
  ~SerialManager();
};
