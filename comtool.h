#ifndef COMTOOL_H
#define COMTOOL_H

#include <QMainWindow>

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
};
#endif // COMTOOL_H
