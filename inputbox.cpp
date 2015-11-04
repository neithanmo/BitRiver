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
    ui->Channels->addItems(QStringList()<<"1"<<"2");
    ui->Audiorate->addItems(QStringList()<<"16 kHz"<<"22.05 kHz"<<"44.1 kHz"<<"48 kHz"<<"96 kHz");
    ui->Framerate->addItems(QStringList()<<"20"<<"25"<<"30"<<"60");
    ui->AudioBitRate->addItems(QStringList()<<"128 kbps"<<"256 kbps"<<"320 kbps");
    ui->VideoBitRate->addItems(QStringList()<<"400 kbit/s"<<"1 Mbit/s"<<"1.15 Mbit/s"<<"2.5 Mbit/s"<<"4 Mbit/s"
                               <<"8 Mbit/s"<<"10 Mbit/s"<<"15 Mbit/s"<<"20 Mbit/s");
    ui->VideoSRC->addItems(QStringList()<<""<<"tcp"<<"File");
    ui->AudioSRC->addItems(QStringList()<<""<<"tcp"<<"File"<<"the same");
    this->setWindowTitle("Streaming Settings");
    this->local=false;


}


inputBox::~inputBox()
{
    delete ui;
}

void inputBox::on_buttonBox_accepted()
{
    QString yout=ui->youtubeLine->text();
    //this->abrate=ui->abitrate->
    QString audioPath=ui->AudioPath->text();
    QString videoPath=ui->VideoPath->text();
}


void inputBox::on_Resolution_currentIndexChanged(int index)
{
    //"240p" <<"360p"<<"480p"<<"720p"<<"1080p"
    //int resolutionX, resolutionY;
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
    //emit width(resolutionX);
    //emit heigth(resolutionY);
}



void inputBox::on_Audiorate_currentIndexChanged(int index)
{
    //"8 kHz"<<"16 kHz"<<"22.05 kHz"<<"44.1 kHz"<<"48 kHz"<<"96 kHz");
    //int arate;
    switch (index){
    case 0:
        arate = 16000;
        break;
    case 1:
        arate = 22050;
        break;
    case 2:
        arate = 44100;
        break;
    case 3:
        arate = 48000;
        break;
    case 4:
        arate = 96000;
        break;
    default:
        arate = 44100;
        break;
    }
    //emit audiorate(arate);
}

void inputBox::on_Channels_currentIndexChanged(int index)
{
    //int y;
    switch (index){
    case 0:
       channels = 1;

        break;
    case 1:
        channels = 2;

        break;
    default:
        channels= 2;

        break;
    }
    //emit channels(y);

}

void inputBox::on_VideoBitRate_currentIndexChanged(int index)
{
   //int vbrate;
    switch (index){
    case 0:
        vbrate = 1000;
        break;
    case 1:
        vbrate = 1115;       
        break;
    case 2:
        vbrate = 2500;       
        break;
    case 3:
        vbrate = 4000;        
        break;
    case 4:
        vbrate = 8000;        
        break;
    case 5:
        vbrate = 10000;        
        break;
    case 6:
        vbrate = 15000;       
        break;
    case 7:
        vbrate = 20000;        
        break;
    default:
        vbrate = 4000;       
        break;
    }
    //emit videobitrate(vbrate);

}

void inputBox::on_AudioBitRate_currentIndexChanged(int index)
{
    //"128 kbps"<<"256 kbps"<<"320 kbps"
    //int abrate;
    switch (index){
    case 0:
        abrate = 128000;        
        break;
    case 1:
        abrate = 256000;
        break;
    case 2:
        abrate = 320000;       
        break;
    default:
        abrate = 128000;     
        break;
    }
    //emit audiobitrate(abrate);
}

void inputBox::on_Framerate_currentIndexChanged(int index)
{
    //"20"<<"25"<<"30"<<"60"
    //int framerate;
    switch (index){
    case 0:
        framerate = 20;

        break;
    case 1:
        framerate = 25;

        break;
    case 2:
        framerate = 30;

        break;
    case 3:
        framerate = 60;

        //emit frameinfo(60);
        break;
    default:
        framerate = 25;
        //this->emisor(framerate);

        break;
    }
    //emit frameinfo(framerate);

}

void inputBox::on_VideoSRC_currentIndexChanged(int index)
{
    //""<<"tcp"<<"File"
    videoBIN=index;
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
        this->videoPath = QFileDialog::getOpenFileName(this, tr("opening"), "/home",
                       "Video files(*.mp4);;(*.avi);;(*.flv);; (*.mkv)");
        //g_print("%s \n", this->videoPath.toUtf8().constData());
        break;
    default:
        break;
    }

}

void inputBox::on_AudioSRC_currentIndexChanged(int index)
{
     audioBIN=index;
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
        this->audioPath = QFileDialog::getOpenFileName(this, tr("opening"), "/home", "All files(*.mp3);; (*.mp4);;(*.flv)");
        g_print("%s \n", filename.toUtf8().constData());
        break;
    case 3://the same
        break;
    default:
        break;
    }

}

void inputBox::on_checkBox_clicked(bool checked)
{
    if(checked)
    {
       local = true;
       //emit isLocal(local);
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

           }
           file.close();
       }

    }
    else
    {
        local = false;
        ui->VideoSRC->addItems(QStringList()<<""<<"tcp"<<"File");
        ui->AudioSRC->addItems(QStringList()<<""<<"tcp"<<"File"<<"the same");
        ui->LocalCamera->clear();
        ui->soundCards->clear();
    }

}




void inputBox::on_LocalCamera_currentIndexChanged(int index)
{
    QString localCamera = ui->LocalCamera->currentText();
    g_print("%s \n", localCamera.toUtf8().constData());
}

void inputBox::on_soundCards_currentIndexChanged(int index)
{
    QString localAudioCard = ui->soundCards->currentText();
    g_print("%s \n", localAudioCard.toUtf8().constData());
}


