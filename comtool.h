#ifndef COMTOOL_H
#define COMTOOL_H

#include <QMainWindow>
#include <QList>
#include <QtCharts>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QStringListModel>

QT_BEGIN_NAMESPACE
namespace Ui { class ComTool; }
QT_END_NAMESPACE

class ComTool : public QMainWindow
{
    Q_OBJECT

public:
    ComTool(QWidget *parent = nullptr);
    ~ComTool();

    QStringList getPortNameList();
    void multiDendGroupBoxContrl(bool visible);
    bool isSerialPortOpen = false;
private:
    Ui::ComTool *ui;

    QList<QPointF> mData;
    int mCount;
    qreal mMaxY;
    qreal mMinY;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QSerialPort *mSerialPort;
    QSerialPortInfo *mSerialPortInfo;
    QStringList mPortNameList;
    QStringListModel *mPortNameModel;
};
#endif // COMTOOL_H
