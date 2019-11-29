#ifndef COMTOOL_H
#define COMTOOL_H

#include <QMainWindow>
#include <QList>
#include <QtCharts>
//#include <QAbstractAxis>
//#include <QValueAxis>

QT_BEGIN_NAMESPACE
namespace Ui { class ComTool; }
QT_END_NAMESPACE

class ComTool : public QMainWindow
{
    Q_OBJECT

public:
    ComTool(QWidget *parent = nullptr);
    ~ComTool();

private:
    Ui::ComTool *ui;

    QList<QPointF> mData;
    int mCount;
    qreal mMaxY;
    qreal mMinY;
    QValueAxis *axisX;
    QValueAxis *axisY;
};
#endif // COMTOOL_H
