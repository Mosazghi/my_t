#pragma once

#include <QAction>
#include <QIcon>
#include <QToolBar>

class ToolbarManager : public QToolBar {
  Q_OBJECT

public:
  ToolbarManager(QWidget *parent = nullptr);
  ~ToolbarManager();

  QAction *actionConnect;
  QAction *actionDisconnect;
  QAction *actionSettings;
  QAction *actionToggleTimestamp;
  QAction *actionShowCharts;
  QAction *actionToggleAutoScroll;
  QAction *actionClearConsole;
  QAction *actionToggleWriteMode;

private:
  void createActions();
};
