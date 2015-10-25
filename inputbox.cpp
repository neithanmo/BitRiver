#include "inputbox.h"
#include "ui_inputbox.h"
#include<QFileDialog>

inputBox::inputBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inputBox)
{
    ui->setupUi(this);
    ui->Resolution->addItems(QStringList()<<"240p" <<"360p"
                            <<"480p"<<"720p"<<"1080p"); //resolutions accepted by youtube servers
    //QObject::connect(ui->slider1, SIGNAL(valueChanged(int)),
                     //ui->progressBar1, SLOT(setValue(int)));
    ui->Channels->addItems(QStringList()<<"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8");
    ui->Audiorate->addItems(QStringList()<<"16 kHz"<<"22.05 kHz"<<"44.1 kHz"<<"48 kHz"<<"96 kHz");
    ui->Framerate->addItems(QStringList()<<"20"<<"25"<<"30"<<"60");
    ui->AudioBitRate->addItems(QStringList()<<"128 kbps"<<"256 kbps"<<"320 kbps");
    ui->VideoBitRate->addItems(QStringList()<<"400 kbit/s"<<"1 Mbit/s"<<"1.15 Mbit/s"<<"2.5 Mbit/s"<<"4 Mbit/s"
                               <<"8 Mbit/s"<<"10 Mbit/s"<<"15 Mbit/s"<<"20 Mbit/s");
    ui->VideoSRC->addItems(QStringList()<<""<<"tcp"<<"File");
    ui->AudioSRC->addItems(QStringList()<<""<<"tcp"<<"File"<<"the same");
    this->setWindowTitle("Streaming Settings");


}


inputBox::~inputBox()
{
    delete ui;
}

void inputBox::on_buttonBox_accepted()
{
    this->youtube=ui->youtubeLine->text();
    //this->abrate=ui->abitrate->
    this->audioPath=ui->AudioPath->text();
    this->videoPath=ui->VideoPath->text();

}

void inputBox::on_Resolution_currentIndexChanged(int index)
{
    //"240p" <<"360p"<<"480p"<<"720p"<<"1080p"
    switch (index){
    case 0:
        resolutionX = 426;
        resolutionY = 240;
        break;
    case 1:
        resolutionX = 640;
        resolutionY = 360;
        break;
    case 2:
        resolutionX = 854;
        resolutionY = 480;
        break;
    case 3:
        resolutionX = 1280;
        resolutionY = 720;
        break;
    case 4:
        resolutionX = 1920;
        resolutionY = 1080;
        break;
    default:
        resolutionX = 854;
        resolutionY = 480;
        break;
    }
}



void inputBox::on_Audiorate_currentIndexChanged(int index)
{
    //"8 kHz"<<"16 kHz"<<"22.05 kHz"<<"44.1 kHz"<<"48 kHz"<<"96 kHz");
    switch (index){
    case 0:
        this->arate = 16000;
        break;
    case 1:
        this->arate = 22050;
        break;
    case 2:
        this->arate = 44100;
        break;
    case 3:
        this->arate = 48000;
        break;
    case 4:
        this->arate = 96000;
        break;
    default:
        this->arate = 44100;
        break;
    }


}

void inputBox::on_Channels_currentIndexChanged(int index)
{
    //"1"<<"2"<<"3"<<"4"<<"5"<<"6"<<"7"<<"8"
    switch (index){
    case 0:
        this->channels = 1;
        break;
    case 1:
        this->channels = 2;
        break;
    case 2:
        this->channels = 3;
        break;
    case 3:
        this->channels = 4;
        break;
    case 4:
        this->channels = 5;
        break;
    case 5:
        this->channels = 6;
        break;
    case 6:
        this->channels = 7;
        break;
    case 7:
        this->channels = 8;
        break;
    default:
        this->channels = 2;
        break;
    }

}

void inputBox::on_VideoBitRate_currentIndexChanged(int index)
{
    //"400 kbit/s"<<"1 Mbit/s"<<"1.15 Mbit/s"<<"2.5 Mbit/s"<<"4 Mbit/s"
    //<<"8 Mbit/s"<<"10 Mbit/s"<<"20 Mbit/s"
    switch (index){
    case 0:
        this->vbrate = 1000;
        break;
    case 1:
        this->vbrate = 1115;
        break;
    case 2:
        this->vbrate = 2500;
        break;
    case 3:
        this->vbrate = 4000;
        break;
    case 4:
        this->vbrate = 8000;
        break;
    case 5:
        this->vbrate = 10000;
        break;
    case 6:
        this->vbrate = 15000;
        break;
    case 7:
        this->vbrate = 2000;
        break;
    default:
        this->vbrate = 4000;
        break;
    }

}

void inputBox::on_AudioBitRate_currentIndexChanged(int index)
{
    //"128 kbps"<<"256 kbps"<<"320 kbps"
    switch (index){
    case 0:
        this->abrate = 128000;
        break;
    case 1:
        this->abrate = 256000;
        break;
    case 2:
        this->abrate = 320000;
        break;
    default:
        this->abrate = 128000;
        break;
    }


}

void inputBox::on_Framerate_currentIndexChanged(int index)
{
    //"20"<<"25"<<"30"<<"60"
    switch (index){
    case 0:
        this->framerate = 20;
        break;
    case 1:
        this->framerate = 25;
        break;
    case 2:
        this->framerate = 30;
        break;
    case 3:
        this->framerate = 60;
        break;
    default:
        this->framerate = 25;
        break;
    }

}

void inputBox::on_VideoSRC_currentIndexChanged(int index)
{
    //""<<"tcp"<<"File"
    this->videoBIN=index;
    QString filename;
    switch (index){
    case 0:
         break;
    case 1:
        QMessageBox::information(this,
                                 "tcp input stream example", "write your ip and port of your audio server on the lineEdit below\n"
                                 "for example: \n 192.168.0.1:6000 ; here the host is 192.168.0.1 and the port is: 6000 ",
                                 QMessageBox::Ok);
        break;
    case 2:
        filename = QFileDialog::getOpenFileName(this, tr("opening"), "/home", "All files(*)");
        g_print("%s \n", filename.toUtf8().constData());
        break;
    default:
        break;
    }

}

void inputBox::on_AudioSRC_currentIndexChanged(int index)
{
    //"microfono"<<"tcp"<<"File"<<"same Videosrc"
    this->audioBIN = index;
     QString filename;
    switch (index){
    case 0:
        break;
    case 1:
        QMessageBox::information(this,
                                 "tcp input stream example", "write your ip and port of your audio server on the lineEdit below\n"
                                 "for example: \n 192.168.0.1:6000 ; here the host is 192.168.0.1 and the port is: 6000 ",
                                 QMessageBox::Ok);
        break;
    case 2:
        filename = QFileDialog::getOpenFileName(this, tr("opening"), "/home", "All files(*)");
        g_print("%s \n", filename.toUtf8().constData());
        break;
    case 3:

        break;
    default:
        this->framerate = 25;
        break;
    }

}

void inputBox::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
        QDir DevDir("/dev","video*",QDir::Name,QDir::System);
        ui->LocalCamera->addItems(DevDir.entryList());
       QFile file("/proc/asound/cards");
       g_print("%s \n", "Sound Cards ------------>");
       if(file.exists() && file.open(QIODevice::ReadOnly))
       {
           QTextStream in(&file);
           QString line = in.readLine();
           while(!line.isEmpty()) {
               QString part1 = line.section("]", 0, 0);
               QString part2 = part1.section("[", 1, 1);
               ui->soundCards->addItem(part2);
               g_print("%s \n", line.toUtf8().constData());
               line = in.readLine();
               //fields = line.split(":");
               //model->appendRow(fields);

           }
            //ui->soundCards->addItems(fields);
           file.close();
       }

    }
    else
    {

        ui->VideoSRC->addItems(QStringList()<<""<<"tcp"<<"File");
        ui->AudioSRC->addItems(QStringList()<<""<<"tcp"<<"File"<<"the same");
        ui->LocalCamera->clear();
        ui->soundCards->clear();
    }

}




void inputBox::on_LocalCamera_currentIndexChanged(int index)
{
    this->localCamera = ui->LocalCamera->currentText();
    g_print("%s \n", localCamera.toUtf8().constData());
}

void inputBox::on_soundCards_currentIndexChanged(int index)
{
    this->localAudioCard = ui->soundCards->currentText();
    g_print("%s \n", localAudioCard.toUtf8().constData());
}
