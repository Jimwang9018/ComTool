#ifndef COMTOOL_H
#define COMTOOL_H

#include <QMainWindow>
#include <QList>

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
};
#endif // COMTOOL_H
