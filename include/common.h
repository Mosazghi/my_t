#pragma once
#include <QSerialPort>

struct Settings {
  QString portName;
  qint32 baudRate;
  QSerialPort::DataBits dataBits;
  QSerialPort::Parity parity;
  QSerialPort::StopBits stopBits;
  QSerialPort::FlowControl flowControl;

  Settings()
      : portName("ttyUSB0"), baudRate(QSerialPort::Baud115200),
        dataBits(QSerialPort::Data8), parity(QSerialPort::NoParity),
        stopBits(QSerialPort::OneStop),
        flowControl(QSerialPort::NoFlowControl) {}
};
