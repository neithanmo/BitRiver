#include "inputbox.h"
#include "ui_inputbox.h"

inputBox::inputBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputBox)
{
    ui->setupUi(this);
    ui->comboBox->addItems(QStringList()<<"1080p" <<"720p"
                            <<"480p"<<"360p"<<"240p");
}


inputBox::~inputBox()
{
    delete ui;
}

void inputBox::on_buttonBox_accepted()
{
    youtube=ui->lineEdit->text();
}

void inputBox::on_comboBox_currentIndexChanged(int index)
{
    int i=ui->comboBox->currentIndex();
    switch (i){
    case 0:
        resolution = 1080;
        break;
    case 1:
        resolution = 720;
        break;
    case 2:
        resolution = 480;
        break;
    case 3:
        resolution = 360;
        break;
    case 4:
        resolution = 240;
        break;
    default:
        resolution = 480;
        break;
    }
}
