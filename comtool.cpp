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
    axisX = new QValueAxis;
    axisY = new QValueAxis;

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    axisX->setRange(0, 720);
    axisY->setRange(-1.1, 1.1);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setTitle("Sin series");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QHBoxLayout *hLayout = new QHBoxLayout();
    QPushButton *button1 = new QPushButton("Dong", this);
    QPushButton *button2 = new QPushButton("Jing", this);
    QPushButton *buttonStop = new QPushButton("Stop", this);
    QPushButton *buttonClear = new QPushButton("Clear", this);

    ui->verticalLayoutGraph->addLayout(hLayout);
    ui->verticalLayoutGraph->addWidget(chartView);
    hLayout->addWidget(button1);
    hLayout->addWidget(button2);
    hLayout->addWidget(buttonStop);
    hLayout->addWidget(buttonClear);
    hLayout->addStretch();

    connect(button1, &QPushButton::clicked, [=]() {
        series->clear();
        mData.clear();
        mCount = 0;
        axisX->setRange(0, 720);
        axisY->setRange(-1.1, 1.1);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        pTimer2->stop();
        pTimer1->start(2);
        for (int i = 0; i < 720; i++) {
            qreal x = i;
            mData.append(QPointF(i, qSin(2.0 * 3.141592 * x / 360.0)));
        }
        series->append(mData);
    });

    connect(button2, &QPushButton::clicked, [=]() {
        series->clear();
        pTimer1->stop();
        mCount = 0;
        mMaxY = 0;
        mMinY = 0;
        axisX->setRange(0, 1);
        axisY->setRange(0, 1);
//        series->attachAxis(axisX);
//        series->attachAxis(axisY);
        pTimer2->start(2);
        qDebug() << "Button2";
    });

    connect(pTimer1, &QTimer::timeout, [=]() {
        qreal x = mCount;
        for (int i = 0; i < mData.size(); ++i)
            mData[i].setX(mData.at(i).x() - 1);

        mData.append(QPointF(720, qSin(2.0 * 3.141592 * x / 360.0)));
        mData.removeFirst();
        series->replace(mData);

        ++ mCount;
        if(mCount > 360)
            mCount = 0;
    });

    connect(pTimer2, &QTimer::timeout, [=]() {
        qreal x = mCount;
        QPointF point = QPointF(mCount, qSin(2.0 * 3.141592 * x / 360.0));
        mMaxY = (mMaxY < point.y()) ? point.y() : mMaxY;
        mMinY = (mMinY > point.y()) ? point.y() : mMinY;
        axisX->setRange(0, point.x());
        axisY->setRange(mMinY, mMaxY);
        series->attachAxis(axisX);
        series->attachAxis(axisY);
        series->append(point);
        qDebug() << "max y = " << mMaxY << "min y = " << mMinY;
        ++ mCount;
        //qDebug() << "time2 x = " << point.x() << " y = " << point.y();
    });

    connect(buttonStop, &QPushButton::clicked, [=]() {
        pTimer1->stop();
        pTimer2->stop();
    });

    connect(buttonClear, &QPushButton::clicked, [=]() {
        series->clear();
        mCount = 0;
        mMaxY = 0;
        mMinY = 0;
//        mData.clear();
    });
}

ComTool::~ComTool()
{
    delete ui;
}

