
#pragma once

#include <QChart>
#include <QChartView>
#include <QDateTime>
#include <QDateTimeAxis>
#include <QHash>
#include <QLineSeries>
#include <QObject>
#include <QVBoxLayout>
#include <QValueAxis>
#include <QWidget>
#include <deque>

struct Chart {
  QChart *chart;
  QLineSeries *series;
  QDateTimeAxis *axisX;
  QValueAxis *axisY;
  QChartView *chartView;
  std::deque<QDateTime> timestamps; // temporary timestamp values
  std::deque<double> values;        // temporary temperature values

  Chart()
      : chart(new QChart()), series(new QLineSeries()),
        axisX(new QDateTimeAxis()), axisY(new QValueAxis()),
        chartView(new QChartView(chart)) {}

  ~Chart() {
    delete chartView;
    delete chart;
    delete series;
    delete axisX;
    delete axisY;
  }
};

class ChartManager : public QWidget {
  Q_OBJECT
public:
  explicit ChartManager(QWidget *parent = nullptr);
  ~ChartManager();
  void addChart(QString &name);
  bool hasChart(QString &name);
  void updateChart(QString &name, double value);
signals:
  void windowClosed();

protected:
  void closeEvent(QCloseEvent *event) override;

private:
  QVBoxLayout *mainLayout;
  QGridLayout *chartLayout;
  QHash<QString, Chart *> m_charts;
  int m_chartCount;
};
