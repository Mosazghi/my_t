#include "toolbarmanager.h"

ToolbarManager::ToolbarManager(QWidget *parent) : QToolBar(parent) {
  createActions();
  this->setMovable(false);
}

ToolbarManager::~ToolbarManager() {}

void ToolbarManager::createActions() {
  // Connect
  actionConnect =
      new QAction(QIcon(":/icons/icons8-connect-50.png"), "Connect", this);
  actionConnect->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
  actionConnect->setStatusTip("Connect to the serial port");

  // Disconnect
  actionDisconnect = new QAction(QIcon(":/icons/icons8-disconnect-50.png"),
                                 "Disconnect", this);
  actionDisconnect->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));
  actionDisconnect->setStatusTip("Disconnect from the serial port");

  // Settings
  actionSettings =
      new QAction(QIcon(":/icons/icons8-settings-50.png"), "Settings", this);
  actionSettings->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));
  actionSettings->setStatusTip("Open the settings dialog");

  // Timestamp
  actionToggleTimestamp =
      new QAction(QIcon(":/icons/icons8-clock-50.png"), "Show timestamp", this);
  actionToggleTimestamp->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_T));
  actionToggleTimestamp->setStatusTip("Show timestamp in console");
  actionToggleTimestamp->setCheckable(true);
  // Graph
  actionShowCharts =
      new QAction(QIcon(":/icons/chart.svg"), "Show graph", this);
  actionShowCharts->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_G));
  actionShowCharts->setStatusTip("View charts");
  actionShowCharts->setCheckable(true);

  // Auto scroll
  actionToggleAutoScroll =
      new QAction(QIcon(":/icons/icons8-scroll-50.png"), "Auto scroll", this);
  actionToggleAutoScroll->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_A));
  actionToggleAutoScroll->setStatusTip("Auto scroll console");
  actionToggleAutoScroll->setCheckable(true);
  // Clear
  actionClearConsole =
      new QAction(QIcon(":/icons/icons8-clear-50.png"), "Clear", this);
  actionClearConsole->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  actionClearConsole->setStatusTip("Clear console");

  actionToggleWriteMode =
      new QAction(QIcon(":/icons/icons8-text-box-50.png"), "Write mode", this);
  actionToggleWriteMode->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_W));
  actionToggleWriteMode->setStatusTip("Toggle write mode");
  actionToggleWriteMode->setCheckable(true);

  // Connect Disconnect | Charts | Autoscroll Timestamp | . . . . Settings
  this->addAction(actionConnect);
  this->addAction(actionDisconnect);
  this->addSeparator();
  this->addAction(actionShowCharts);
  this->addSeparator();
  this->addAction(actionToggleAutoScroll);
  this->addAction(actionToggleTimestamp);
  this->addAction(actionClearConsole);
  this->addAction(actionToggleWriteMode);

  QWidget *space = new QWidget();
  space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
  this->addWidget(space);
  this->addAction(actionSettings);
}
