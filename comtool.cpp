#include "comtool.h"
#include "ui_comtool.h"

ComTool::ComTool(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ComTool)
{
    ui->setupUi(this);
}

ComTool::~ComTool()
{
    delete ui;
}

