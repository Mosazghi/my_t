#include "mainwindow.h"
#include "chartmanager.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSerialPort>
#include <qregularexpression.h>

static QRegularExpression const re("[=:]");

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_settingsDialog(new SettingsDialog(this)),
      m_console(new Console(this)),
      m_toolbar(new ToolbarManager(this)),
      m_statusLabel(new QLabel(this)),
      m_statusBar(new QStatusBar(this)),
      m_chartManager(new ChartManager(nullptr)),
      m_lineEdit(new QLineEdit(this)),
      m_layout(new QVBoxLayout()) {
  m_ui->setupUi(this);
  m_statusBar->addWidget(m_statusLabel);

  setStatusMessage("Not connected");
  this->setStatusBar(m_statusBar);

  // Toolbar and Console
  this->addToolBar(m_toolbar);

  QWidget* containerWidget = new QWidget(this);
  containerWidget->setLayout(m_layout);

  m_layout->addWidget(m_console);
  m_layout->addWidget(m_lineEdit);
  m_lineEdit->setVisible(false);

  this->setCentralWidget(containerWidget);

  // Signals
  connect(m_toolbar->actionConnect, &QAction::triggered, this,
          &MainWindow::onActionConnectEvent);
  connect(m_toolbar->actionDisconnect, &QAction::triggered, this,
          &MainWindow::onActionDisconnectEvent);
  connect(m_toolbar->actionSettings, &QAction::triggered, this,
          [this]() { m_settingsDialog->exec(); });
  connect(m_toolbar->actionClearConsole, &QAction::triggered, m_console,
          &Console::clearConsole);
  connect(m_toolbar->actionToggleWriteMode, &QAction::triggered, this,
          [this]() { m_lineEdit->setVisible(!m_lineEdit->isVisible()); });
  connect(m_lineEdit, &QLineEdit::returnPressed, this, &MainWindow::writeData);

  connect(m_chartManager, &ChartManager::windowClosed, this,
          &MainWindow::onChartClosed);
}

MainWindow::~MainWindow() {
  delete m_ui;
  delete m_console;
  delete m_serialManager;
  delete m_settingsDialog;
  delete m_toolbar;
  delete m_statusLabel;
  delete m_statusBar;
  delete m_chartManager;
  delete m_layout;
  delete m_lineEdit;
}

void MainWindow::onChartClosed() {
  m_isChartVisible = false;
  if (m_toolbar->actionShowCharts->isChecked()) {
    m_toolbar->actionShowCharts->setChecked(false);
  }
  qDebug() << "Chart closed";
}
void MainWindow::readData() {
  QByteArray data = m_serialManager->readAll();
  double now = QDateTime::currentSecsSinceEpoch();
  // Wait for ALL data to arrive
  while (m_serialManager->waitForReadyRead(10)) {
    data.append(m_serialManager->readAll());
  }

  // To remove "\r\n" (separators) from the data
  int index = 0;
  while ((index = data.indexOf('\n')) != -1) {
    QString line = data.left(index - 1);
    data.remove(0, index + 1);

    // Display chart(s)
    if (m_toolbar->actionShowCharts->isChecked()) {
      QStringList query = line.split(re);
      if (query.size() == 2) {
        QString key = query[0].trimmed();
        if (key.isValidUtf16()) {
          bool ok;
          double value = query[1].trimmed().toDouble(&ok);

          if (ok) {
            if (m_chartManager->hasChart(key)) {
              m_chartManager->updateChart(key, value);
            } else {
              m_chartManager->addChart(key);
            }

            if (!m_isChartVisible) {
              m_isChartVisible = true;
              m_chartManager->show();
              m_chartManager->setMinimumSize(960, 400);
            }

          } else {
            qDebug() << "Value is not a valid number: " << query[1].trimmed();
          }
        }
      }
    }

    // TODO: Reduce the number of arguments
    m_console->updateConsole(line,
                             m_toolbar->actionToggleTimestamp->isChecked(),
                             m_toolbar->actionToggleAutoScroll->isChecked());
  }
}

void MainWindow::onActionConnectEvent() {
  if (m_isConnected || m_settingsDialog->isPortListEmpty()) {
    QMessageBox::warning(this, "Error", "No ports available.");
    return;
  }

  Settings settings = m_settingsDialog->settings();

  m_serialManager = new SerialManager(settings);

  if (m_serialManager->open(QSerialPort::ReadWrite)) {
    double now;
    m_isConnected = true;
    m_toolbar->actionConnect->setEnabled(false);
    setStatusMessage(QString("Connected to: %1 | Baud: %3 ")
                         .arg(settings.portName)
                         .arg(settings.baudRate));
    // Connect signals
    connect(m_serialManager, &QSerialPort::readyRead, this,
            &MainWindow::readData);
    connect(m_serialManager, &QSerialPort::errorOccurred, this,
            [this](QSerialPort::SerialPortError error) {
              switch (error) {
                  // Means we disconnected the device
                case QSerialPort::ResourceError:
                  QMessageBox::critical(this, "Error",
                                        m_serialManager->errorString());
                  onActionDisconnectEvent();
                  break;
                default:
                  break;
              }
            });
    QMessageBox::information(this, "Connected",
                             "connected to " + settings.portName);

  } else {
    QMessageBox::critical(
        this, "Error",
        m_serialManager->errorString() +
            "\n\nHint: check if the baudrate is corresponds to the device.");
    setStatusMessage("Error: " + m_serialManager->errorString());
  }
}

void MainWindow::onActionDisconnectEvent() {
  if (m_serialManager && m_serialManager->isOpen()) {
    m_isChartVisible = false;
    m_isConnected = false;
    m_serialManager->close();
    delete m_serialManager;
    m_serialManager = nullptr;
    m_toolbar->actionConnect->setEnabled(true);
    QMessageBox::information(this, "Disconnected", "Disconnected from port");
    setStatusMessage("Disconnected");
  }
}

void MainWindow::setStatusMessage(QString const& message) {
  m_statusLabel->setText(message);
}

void MainWindow::writeData() {
  if (m_serialManager && m_serialManager->isOpen()) {
    auto const text = m_lineEdit->text().toUtf8();
    if (!text.isEmpty()) {
      m_serialManager->write(text);
      qDebug() << "Writing: " << text;
      // m_serialManager->flush();
      m_lineEdit->clear();
    }
  }
}
