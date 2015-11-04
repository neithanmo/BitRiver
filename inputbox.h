#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QDialog>
#include <QString>
#include <QMessageBox>
#include <QDir>
#include<QTextStream>
#include <glib.h>
#include <gst/gst.h>
#include <stdio.h>
#include <QDebug>

static QString path;
static QString apath;


namespace Ui {
class inputBox;
}

class inputBox : public QDialog
{
    Q_OBJECT

public:
    explicit inputBox(QWidget *parent = 0);
    ~inputBox();
    bool local; //isLocal = true ---->> get Local path devices, for videoBIN and audioBIN pipeline
    int VBIN;
    int arate, channels,framerate; //audio rate, channels and frame rate for system ettings
    int resolutionX, resolutionY;
    int vbrate,abrate, videoBIN, audioBIN; //What bin I will to use in my pipeline?
    QString youtube;
    QString audioPath, videoPath; //Line edith paths, ip and port or file path
    QString localCamera, localAudioCard; //local paths for sound cards and video locall cameras
    //bool same;

private slots:
    void on_buttonBox_accepted();

    void on_Resolution_currentIndexChanged(int index);

    void on_Audiorate_currentIndexChanged(int index);

    void on_Channels_currentIndexChanged(int index);

    void on_VideoBitRate_currentIndexChanged(int index);

    void on_AudioBitRate_currentIndexChanged(int index);

    void on_Framerate_currentIndexChanged(int index);

    void on_VideoSRC_currentIndexChanged(int index);

    void on_AudioSRC_currentIndexChanged(int index);

    void on_checkBox_clicked(bool checked);


    void on_LocalCamera_currentIndexChanged(int index);

    void on_soundCards_currentIndexChanged(int index);

private:
    Ui::inputBox *ui;
};

#endif // INPUTBOX_H
