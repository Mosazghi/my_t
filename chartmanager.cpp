#include "chartmanager.h"

static void customizeChart(QChart *chart);

ChartManager::ChartManager(QWidget *parent) : QWidget(parent), m_chartCount(0) {
  mainLayout = new QVBoxLayout(this);
  chartLayout = new QGridLayout();
  chartLayout->setSpacing(5);
  mainLayout->addLayout(chartLayout);
  setLayout(mainLayout);
}

ChartManager::~ChartManager() { m_charts.clear(); }

void ChartManager::addChart(QString &name) {
  Chart *newChart = new Chart;

  newChart->chart->setTitle("Real-time data for <i><b>" + name + "</b></i>");
  newChart->chart->legend()->hide();

  // Setup the X-axis
  newChart->axisX->setFormat("hh:mm:ss");
  newChart->axisX->setTitleText("Time");
  newChart->axisX->setTickCount(5);
  newChart->axisY->setTitleText(name);
  newChart->axisY->setTickCount(5);

  newChart->chart->addAxis(newChart->axisX, Qt::AlignBottom);
  newChart->chart->addAxis(newChart->axisY, Qt::AlignLeft);

  // Setup the chart view
  newChart->chartView->setMinimumSize(400, 300);
  newChart->chartView->setRenderHint(QPainter::Antialiasing);
  newChart->chartView->setRubberBand(QChartView::RectangleRubberBand);

  // Datetime
  QDateTime currentTime = QDateTime::currentDateTime();
  QDateTime startTime = currentTime.addSecs(-10);
  newChart->axisX->setRange(startTime, currentTime);

  // Series
  newChart->chart->addSeries(newChart->series);
  newChart->series->attachAxis(newChart->axisX);
  newChart->series->attachAxis(newChart->axisY);

  // Grid layout
  int row = m_chartCount / 2;
  int col = m_chartCount % 2;
  chartLayout->addWidget(newChart->chartView, row, col);

  m_charts.insert(name, newChart);
  customizeChart(newChart->chart);
  m_chartCount++;
}

bool ChartManager::hasChart(QString &name) { return m_charts.contains(name); }

void ChartManager::updateChart(QString &name, double value) {
  QDateTime currentTime = QDateTime::currentDateTime();
  Chart *chart = m_charts.value(name);
  chart->series->append(currentTime.toMSecsSinceEpoch(), value);

  chart->timestamps.push_back(currentTime);
  chart->values.push_back(value);

  // delete old data past 10 seconds
  while (!chart->timestamps.empty() &&
         chart->timestamps.front() < currentTime.addSecs(-10)) {
    chart->timestamps.pop_front();
    chart->values.pop_front();
  }

  double minVal = *std::min_element(chart->values.begin(), chart->values.end());
  double maxVal = *std::max_element(chart->values.begin(), chart->values.end());

  chart->axisY->setRange(minVal - 0.15, maxVal + 0.15);
  chart->axisX->setRange(currentTime.addSecs(-10), currentTime);
}

void ChartManager::closeEvent(QCloseEvent *event) {
  emit windowClosed();
  QWidget::closeEvent(event);
}

static void customizeChart(QChart *chart) {
  // Customize the chart
  chart->setTheme(QChart::ChartThemeDark);
  chart->setBackgroundRoundness(0);
  chart->setDropShadowEnabled(true);
  chart->setMargins(QMargins(0, 0, 0, 0));
  chart->setPlotAreaBackgroundVisible(true);
  chart->setPlotAreaBackgroundBrush(QBrush(QColor(0x00, 0x00, 0x00, 0x00)));
  chart->setPlotAreaBackgroundPen(QPen(Qt::black, 0, Qt::SolidLine));
}
