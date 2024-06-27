#pragma once

#include "common.h"
#include <QButtonGroup>
#include <QDialog>
#include <QSerialPort>
#include <QTimer>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  explicit SettingsDialog(QWidget *parent = nullptr);
  ~SettingsDialog();
  Settings settings() const;
  bool isPortListEmpty() const;

private slots:
  void on_buttonBox_accepted();

private:
  Ui::SettingsDialog *m_ui;
  QButtonGroup *m_dataBitsGroup = nullptr;
  QButtonGroup *m_stopBitsGroup = nullptr;
  Settings m_settings;
  QTimer *m_timer = nullptr;

  void fillParameters();
  void updateParameters();
  void updatePortList();
};
