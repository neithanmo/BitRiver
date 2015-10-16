#include "inputbox.h"
#include "ui_inputbox.h"

inputBox::inputBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputBox)
{
    ui->setupUi(this);
}

inputBox::~inputBox()
{
    delete ui;
}
