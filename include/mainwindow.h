#pragma once

#include "chartmanager.h"
#include "common.h"
#include "console.h"
#include "serialmanager.h"
#include "settingsdialog.h"
#include "toolbarmanager.h"
#include <QLineEdit>
#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStatusBar>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);

  ~MainWindow();

 private slots:
  void onActionConnectEvent();
  void onActionDisconnectEvent();
  void readData();
  void writeData();
  void onChartClosed();

 private:
  bool m_isConnected = false;
  bool m_isChartVisible = false;

  Ui::MainWindow* m_ui = nullptr;
  SettingsDialog* m_settingsDialog = nullptr;
  Console* m_console = nullptr;
  ToolbarManager* m_toolbar = nullptr;
  QLabel* m_statusLabel = nullptr;
  QStatusBar* m_statusBar = nullptr;
  ChartManager* m_chartManager = nullptr;
  Settings m_settings;
  SerialManager* m_serialManager = nullptr;
  QVBoxLayout* m_layout = nullptr;
  QLineEdit* m_lineEdit = nullptr;

  void setStatusMessage(QString const& message);
};
