#include<iostream>
#include "newsource.h"
#include "ui_newsource.h"

newSource::newSource(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newSource)
{
    ui->setupUi(this);
    this->setWindowTitle("New media source");
    ui->listWidget->addItems(QStringList()<<"local camera"<<"audio card"<<"file - audio and video"<<"file-only audio"<<"file-only video"
                             <<"from tcp: audio and video"<<"from tcp: only audio"<<"from tcp: only video");
    ui->lineEdit->hide();
    ui->audioDev->hide();
    ui->videoDev->hide();
}

newSource::~newSource()
{
    delete ui;
}



void newSource::on_listWidget_currentRowChanged(int currentRow)
{
        sourcetype = currentRow;
        std::cout<<"current row is: "<<sourcetype<<std::endl;

        if(currentRow == 0){
            ui->videoDev->setVisible(true);
            ui->audioDev->clear();
            ui->audioDev->hide();
            QDir DevDir("/dev","video*",QDir::Name,QDir::System);
            ui->videoDev->addItems(DevDir.entryList());

        }
        else{

                if(currentRow == 1){
                    ui->audioDev->setVisible(true);
                    ui->videoDev->clear();
                    ui->videoDev->hide();
                    ui->lineEdit->hide();
                    ui->lineEdit->clear();
                    QFile file("/proc/asound/cards");
                    printf("%s \n", "Sound Cards ------------>");
                    if(file.exists() && file.open(QIODevice::ReadOnly))
                    {
                        QTextStream in(&file);
                        QString line = in.readLine();
                        while(!line.isEmpty()) {
                            QString part1 = line.section("]", -2, -2);
                            QString part2 = part1.section("[", -1, -1);
                            QString part3 = part2.section(" ", 0,0);
                            ui->audioDev->addItem(part3);
                            printf("%s \n", line.toUtf8().constData());
                            line = in.readLine();
                        }
                        file.close();
               }
            }
        }
        if((currentRow == 2)||(currentRow == 3)||(currentRow == 4)){
                ui->audioDev->hide();
                ui->videoDev->hide();
                ui->videoDev->clear();
                ui->audioDev->clear();
                ui->lineEdit->hide();
                 this->sourcefilePath = QFileDialog::getOpenFileName(this, tr("opening"), "/home",
                           "Media files(*.mp4);;(*.avi);;(*.flv);;(*.mkv);;(*.mp3);;(*.wav);;(*.flac);;(*.ogg)");

        }
        else{
            if((currentRow == 5)||(currentRow == 6)||(currentRow == 7)){
                ui->audioDev->hide();
                ui->videoDev->hide();
                ui->videoDev->clear();
                ui->audioDev->clear();
                QMessageBox::information(this,
                                     "tcp input stream example", "write your ip and port of your audio and video server on the lineEdit below\n"
                                     "for example: \n 192.168.0.1:6000 ; here the host is 192.168.0.1 and the port is: 6000 ",
                                     QMessageBox::Ok);

                ui->lineEdit->setVisible(true);
                ui->lineEdit->setFocus();

              }
        }

}



void newSource::on_Newmediasource_accepted()
{
    sourceIP = ui->lineEdit->text().section(":", -2, -2);
    qDebug()<<sourceIP;
    sourceName = ui->lineEdit_2->text();
    qDebug()<<sourceName;
}
