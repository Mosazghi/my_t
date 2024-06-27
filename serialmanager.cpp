#include "serialmanager.h"

SerialManager::SerialManager(Settings settings)
    : QSerialPort(settings.portName) {
  this->setBaudRate(settings.baudRate);
  this->setDataBits(settings.dataBits);
  this->setParity(settings.parity);
  this->setStopBits(settings.stopBits);
  this->setFlowControl(settings.flowControl);
}

SerialManager::~SerialManager() {}
