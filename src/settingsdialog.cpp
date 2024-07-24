#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QRadioButton>
#include <QSerialPortInfo>

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent),
      m_ui(new Ui::SettingsDialog),
      m_dataBitsGroup(new QButtonGroup(this)),
      m_stopBitsGroup(new QButtonGroup(this)),
      m_timer(new QTimer(this)) {
  m_ui->setupUi(this);
  fillParameters();

  connect(m_timer, &QTimer::timeout, this, &SettingsDialog::updatePortList);
  m_timer->start(1000);
}

SettingsDialog::~SettingsDialog() { delete m_ui; }

void SettingsDialog::fillParameters() {
  /* DataBits */
  QMap<QString, QSerialPort::DataBits> dataBits = {{"5", QSerialPort::Data5},
                                                   {"6", QSerialPort::Data6},
                                                   {"7", QSerialPort::Data7},
                                                   {"8", QSerialPort::Data8}};

  for (auto it = dataBits.begin(); it != dataBits.end(); ++it) {
    QRadioButton* radioButton = new QRadioButton(it.key());
    m_ui->dataBitsContainer->addWidget(radioButton);
    m_dataBitsGroup->addButton(radioButton, it.value());
  }

  m_dataBitsGroup->buttons().last()->setChecked(true);

  /* Partiy */
  QMap<QString, QSerialPort::Parity> parity = {
      {"None", QSerialPort::NoParity},
      {"Even", QSerialPort::EvenParity},
      {"Odd", QSerialPort::OddParity},
      {"Space", QSerialPort::SpaceParity},
      {"Mark", QSerialPort::MarkParity}};
  for (auto it = parity.begin(); it != parity.end(); ++it) {
    m_ui->cmbParity->addItem(it.key(), it.value());
  }
  /* StopBits */
  QMap<QString, QSerialPort::StopBits> stopBits = {
      {"1", QSerialPort::OneStop},
      {"1.5", QSerialPort::OneAndHalfStop},
      {"2", QSerialPort::TwoStop}};

  for (auto it = stopBits.begin(); it != stopBits.end(); ++it) {
    QRadioButton* radioButton = new QRadioButton(it.key());
    m_ui->stopBitsContainer->addWidget(radioButton);
    m_stopBitsGroup->addButton(radioButton, it.value());
  }

  m_stopBitsGroup->buttons().last()->setChecked(true);

  /* FlowControl */
  QMap<QString, QSerialPort::FlowControl> flowControl = {
      {"None", QSerialPort::NoFlowControl},
      {"RTS/CTS", QSerialPort::HardwareControl},
      {"XON/XOFF", QSerialPort::SoftwareControl}};

  for (auto it = flowControl.begin(); it != flowControl.end(); ++it) {
    m_ui->cmbFlowControl->addItem(it.key(), it.value());
  }

  /* BaudRate */
  QMap<QString, QSerialPort::BaudRate> baudRate = {
      {"4800", QSerialPort::Baud4800},   {"9600", QSerialPort::Baud9600},
      {"19200", QSerialPort::Baud19200}, {"38400", QSerialPort::Baud38400},
      {"57600", QSerialPort::Baud57600}, {"115200", QSerialPort::Baud115200},
  };

  for (auto it = baudRate.begin(); it != baudRate.end(); ++it) {
    m_ui->cmbBaud->addItem(it.key(), it.value());
  }
}

void SettingsDialog::on_buttonBox_accepted() {
  updateParameters();
  qDebug() << "Settings accepted";
  qDebug() << "PortName: " << m_settings.portName;
  qDebug() << "BaudRate: " << m_settings.baudRate;
  qDebug() << "DataBits: " << m_settings.dataBits;
  qDebug() << "Parity: " << m_settings.parity;
  qDebug() << "StopBits: " << m_settings.stopBits;
  qDebug() << "FlowControl: " << m_settings.flowControl;

  accept();
}

void SettingsDialog::updateParameters() {
  m_settings.portName = m_ui->cmbPortList->currentText().trimmed();
  m_settings.baudRate =
      m_ui->cmbBaud->currentData().value<QSerialPort::BaudRate>();
  m_settings.dataBits =
      static_cast<QSerialPort::DataBits>(m_dataBitsGroup->checkedId());
  m_settings.parity =
      static_cast<QSerialPort::Parity>(m_ui->cmbParity->currentIndex());
  m_settings.stopBits =
      static_cast<QSerialPort::StopBits>(m_stopBitsGroup->checkedId());
  m_settings.flowControl = static_cast<QSerialPort::FlowControl>(
      m_ui->cmbFlowControl->currentIndex());
}

Settings SettingsDialog::settings() const { return m_settings; }

bool SettingsDialog::isPortListEmpty() const {
  return m_ui->cmbPortList->count() == 0;
}

void SettingsDialog::updatePortList() {
  QList<QString> ports;

  for (QSerialPortInfo const& port : QSerialPortInfo::availablePorts()) {
    QString const portName = port.portName();
    if (!portName.startsWith("ttyS")) {
      ports.append(portName);
    }
  }

  int uiCount = m_ui->cmbPortList->count();
  int portsCount = ports.count();
  int maxCount = qMax(uiCount, portsCount);

  for (int i = 0; i < maxCount; i++) {
    QString port = ports.value(i);
    int found = m_ui->cmbPortList->findText(port);

    if (found == -1 && port != "") m_ui->cmbPortList->addItem(port);

    // if port is not available anymore but is visible in the ui
    if (uiCount > portsCount) {
      QString port = m_ui->cmbPortList->itemText(i);
      if (!ports.contains(port)) m_ui->cmbPortList->removeItem(i);
    }
  }
}
