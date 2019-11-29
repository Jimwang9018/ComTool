#include "comtool.h"
#include "ui_comtool.h"

#include <QPushButton>
#include <QLayout>
#include <QtCharts>
#include <QTimer>
#include <math.h>
#include <QDebug>

ComTool::ComTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComTool),
      mCount(0),
      mMaxY(0.1),
      mMinY(-0.1)
{
    ui->setupUi(this);

    QTimer *pTimer1 = new QTimer(this);
    QTimer *pTimer2 = new QTimer(this);
    QLineSeries *series = new QLineSeries();

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Sin series");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QHBoxLayout *hLayout = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("Dong", this);
    QPushButton *button2 = new QPushButton("Jing", this);

    ui->verticalLayoutGraph->addLayout(hLayout);
    ui->verticalLayoutGraph->addWidget(chartView);
    hLayout->addWidget(button1);
    hLayout->addWidget(button2);
    hLayout->addStretch();

}

ComTool::~ComTool()
{
    delete ui;
}

