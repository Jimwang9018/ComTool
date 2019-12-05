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
private slots:
    void on_pushButtonConnection_pressed();

    void on_pushButtonConnection_clicked();

    void serialPortReceiveData();

    void on_comboBoxPort_currentTextChanged(const QString &arg1);

    void on_comboBoxBaudrate_currentIndexChanged(int index);

    void on_comboBoxDataBits_currentIndexChanged(int index);

    void on_comboBoxParity_currentIndexChanged(int index);

    void on_comboBoxStopBits_currentIndexChanged(int index);

    void on_comboBoxFlowType_currentIndexChanged(int index);

    void on_radioButtonHex_clicked();

    void on_radioButtonASCII_clicked();

    void on_pushButtonClearReceive_clicked();

    void on_radioButtonHex_2_clicked();

    void on_radioButtonASCII_2_clicked();

    void on_checkBoxLoopSend_stateChanged(int arg1);

    void on_pushButtonClearSend_clicked();

    void on_pushButtonMultiSend_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonMultiSend1_clicked();

    void on_checkBoxHex1_stateChanged(int arg1);

    void on_pushButtonMultiSend2_clicked();

    void on_checkBoxHex2_stateChanged(int arg1);

    void on_pushButtonMultiSend3_clicked();

    void on_checkBoxHex3_stateChanged(int arg1);

    void on_pushButtonMultiSend4_clicked();

    void on_checkBoxHex4_stateChanged(int arg1);

    void on_pushButtonMultiSend5_clicked();

    void on_checkBoxHex5_stateChanged(int arg1);

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

    void serialPortUiClose();
    void serialPortUiOpen();
};
#endif // COMTOOL_H
