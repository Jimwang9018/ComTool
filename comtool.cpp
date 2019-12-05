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

    multiDendGroupBoxContrl(false);
    mSerialPort = new QSerialPort();
    mSerialPortInfo = new QSerialPortInfo();
    mPortNameModel = new QStringListModel();
    mPortNameList = getPortNameList();

    //connect()

    axisX = new QValueAxis;
    axisY = new QValueAxis;
    QTimer *pTimer1 = new QTimer(this);
    QTimer *pTimer2 = new QTimer(this);
    QLineSeries *series = new QLineSeries();

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
        series->attachAxis(axisX);
        series->attachAxis(axisY);
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
        ++ mCount;
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
    });
}

ComTool::~ComTool()
{
    if(mSerialPort->isOpen())
        mSerialPort->close();

    delete mSerialPort;
    delete mSerialPortInfo;
    delete mPortNameModel;

    delete axisX;
    delete axisY;

    delete ui;
}

QStringList ComTool::getPortNameList()
{
    QStringList serialPortName;

    foreach (*mSerialPortInfo, QSerialPortInfo::availablePorts()) {
        serialPortName << mSerialPortInfo->portName();

        if(!serialPortName.isEmpty()){
            mPortNameModel->setStringList(serialPortName);
            ui->comboBoxPort->setModel(mPortNameModel);
            ui->comboBoxPort->setCurrentText(serialPortName.first());
        }
    }

    mSerialPort->setParity(QSerialPort::NoParity);
    mSerialPort->setBaudRate(QSerialPort::Baud115200);
    mSerialPort->setDataBits(QSerialPort::Data8);
    mSerialPort->setStopBits(QSerialPort::OneStop);
    mSerialPort->setFlowControl(QSerialPort::NoFlowControl);

    return serialPortName;
}

void ComTool::multiDendGroupBoxContrl(bool visible)
{
    if(visible){
        ui->groupBoxMultiSend1->setVisible(true);
        ui->groupBoxMultiSend2->setVisible(true);
        ui->groupBoxMultiSend3->setVisible(true);
        ui->groupBoxMultiSend4->setVisible(true);
        ui->groupBoxMultiSend5->setVisible(true);
    } else {
        ui->groupBoxMultiSend1->setVisible(false);
        ui->groupBoxMultiSend2->setVisible(false);
        ui->groupBoxMultiSend3->setVisible(false);
        ui->groupBoxMultiSend4->setVisible(false);
        ui->groupBoxMultiSend5->setVisible(false);
    }
}

void ComTool::on_pushButtonConnection_pressed()
{
//    QStringList serialPortName;

//    foreach (*mSerialPortInfo, QSerialPortInfo::availablePorts()) {
//        serialPortName << mSerialPortInfo->portName();

//        if(!mSerialPortInfo->portName().isEmpty()) {
//            mPortNameModel->setStringList(serialPortName);//?
//            ui->comboBoxPort->setModel(mPortNameModel);
//        }
//    }
}

void ComTool::on_pushButtonConnection_clicked()
{
    if(isSerialPortOpen) {
        isSerialPortOpen = false;
        if(mSerialPort->isOpen()) {
            mSerialPort->close();
        }
        serialPortUiClose();
        getPortNameList();

    } else {
        isSerialPortOpen = true;
        if(mSerialPort->isOpen()) {
            mSerialPort->close();
        }
        serialPortUiOpen();
        mSerialPort->open(QIODevice::ReadWrite);
        connect(mSerialPort, SIGNAL(readyRead()),
                this, SLOT(serialPortReceiveData()));
    }
}

void ComTool::serialPortReceiveData()
{

}

void ComTool::on_comboBoxPort_currentTextChanged(const QString &arg1)
{
    mSerialPort->setPortName(arg1);
}

void ComTool::on_comboBoxBaudrate_currentIndexChanged(int index)
{
    QSerialPort::BaudRate baudRate;
    switch (index) {
    case 0:
        baudRate = QSerialPort::Baud115200; break;
    case 1:
        baudRate = QSerialPort::Baud9600; break;
    case 2:
        baudRate = QSerialPort::Baud19200; break;
    case 3:
        baudRate = QSerialPort::Baud38400; break;
    case 4:
        baudRate = QSerialPort::Baud57600; break;
    default:
        baudRate = QSerialPort::UnknownBaud; break;
    }

    mSerialPort->setBaudRate(baudRate);
}

void ComTool::on_comboBoxDataBits_currentIndexChanged(int index)
{
    QSerialPort::DataBits dataBits;
    switch (index) {
    case 0:
        dataBits = QSerialPort::Data8; break;
    case 1:
        dataBits = QSerialPort::Data7; break;
    case 2:
        dataBits = QSerialPort::Data6; break;
    case 3:
        dataBits = QSerialPort::Data5; break;
    default:
        dataBits = QSerialPort::UnknownDataBits; break;
    }

    mSerialPort->setDataBits(dataBits);
}

void ComTool::on_comboBoxParity_currentIndexChanged(int index)
{
    QSerialPort::Parity parity;
    switch (index) {
    case 0:
        parity = QSerialPort::NoParity; break;
    case 1:
        parity = QSerialPort::OddParity; break;
    case 2:
        parity = QSerialPort::EvenParity; break;
    default:
        parity = QSerialPort::UnknownParity; break;
    }

    mSerialPort->setParity(parity);
}

void ComTool::on_comboBoxStopBits_currentIndexChanged(int index)
{
    QSerialPort::StopBits stopBits;
    switch (index) {
    case 0:
        stopBits = QSerialPort::OneStop; break;
    case 1:
        stopBits = QSerialPort::OneAndHalfStop; break;
    case 2:
        stopBits = QSerialPort::TwoStop; break;
    default:
        stopBits = QSerialPort::UnknownStopBits; break;
    }

    mSerialPort->setStopBits(stopBits);
}

void ComTool::on_comboBoxFlowType_currentIndexChanged(int index)
{
    QSerialPort::FlowControl flowControl;
    switch (index) {
    case 0:
        flowControl = QSerialPort::NoFlowControl; break;
    case 1:
        flowControl = QSerialPort::HardwareControl; break;
    case 2:
        flowControl = QSerialPort::SoftwareControl; break;
    default:
        flowControl = QSerialPort::UnknownFlowControl; break;
    }

    mSerialPort->setFlowControl(flowControl);
}

void ComTool::on_radioButtonHex_clicked()
{

}

void ComTool::on_radioButtonASCII_clicked()
{

}

void ComTool::on_pushButtonClearReceive_clicked()
{

}

void ComTool::on_radioButtonHex_2_clicked()
{

}

void ComTool::on_radioButtonASCII_2_clicked()
{

}

void ComTool::on_checkBoxLoopSend_stateChanged(int arg1)
{
    if (arg1) {
        ui->spinBoxLoopTime->setEnabled(false);
    } else {
        ui->spinBoxLoopTime->setEnabled(true);
    }
}

void ComTool::on_pushButtonClearSend_clicked()
{

}

void ComTool::on_pushButtonMultiSend_clicked()
{
    if (ui->pushButtonMultiSend->isChecked()) {
        multiDendGroupBoxContrl(true);
    } else {
        multiDendGroupBoxContrl(false);
    }
}

void ComTool::on_pushButtonSend_clicked()
{

}

void ComTool::on_pushButtonMultiSend1_clicked()
{

}

void ComTool::on_checkBoxHex1_stateChanged(int arg1)
{

}

void ComTool::on_pushButtonMultiSend2_clicked()
{

}

void ComTool::on_checkBoxHex2_stateChanged(int arg1)
{

}

void ComTool::on_pushButtonMultiSend3_clicked()
{

}

void ComTool::on_checkBoxHex3_stateChanged(int arg1)
{

}

void ComTool::on_pushButtonMultiSend4_clicked()
{

}

void ComTool::on_checkBoxHex4_stateChanged(int arg1)
{

}

void ComTool::on_pushButtonMultiSend5_clicked()
{

}

void ComTool::on_checkBoxHex5_stateChanged(int arg1)
{

}

void ComTool::serialPortUiClose()
{
    ui->comboBoxPort->setEnabled(true);
    ui->comboBoxBaudrate->setEnabled(true);
    ui->comboBoxDataBits->setEnabled(true);
    ui->comboBoxParity->setEnabled(true);
    ui->comboBoxStopBits->setEnabled(true);
    ui->comboBoxFlowType->setEnabled(true);

    ui->pushButtonSend->setEnabled(false);
    ui->pushButtonMultiSend1->setEnabled(false);
    ui->pushButtonMultiSend2->setEnabled(false);
    ui->pushButtonMultiSend3->setEnabled(false);
    ui->pushButtonMultiSend4->setEnabled(false);
    ui->pushButtonMultiSend5->setEnabled(false);

    if(ui->checkBoxLoopSend->isChecked())
        ui->checkBoxLoopSend->setChecked(false);
    ui->checkBoxLoopSend->setEnabled(false);
    ui->pushButtonConnection->setText("Connection");
}

void ComTool::serialPortUiOpen()
{
    ui->comboBoxPort->setEnabled(false);
    ui->comboBoxBaudrate->setEnabled(false);
    ui->comboBoxDataBits->setEnabled(false);
    ui->comboBoxParity->setEnabled(false);
    ui->comboBoxStopBits->setEnabled(false);
    ui->comboBoxFlowType->setEnabled(false);

    ui->pushButtonSend->setEnabled(true);
    ui->pushButtonMultiSend1->setEnabled(true);
    ui->pushButtonMultiSend2->setEnabled(true);
    ui->pushButtonMultiSend3->setEnabled(true);
    ui->pushButtonMultiSend4->setEnabled(true);
    ui->pushButtonMultiSend5->setEnabled(true);

    ui->checkBoxLoopSend->setEnabled(true);
    ui->pushButtonConnection->setText("Connected");
}
