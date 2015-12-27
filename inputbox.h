
/*
Copyright (C) 2015 by Natanael Mojica <neithanmo@gmail.com>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
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
    int arate, channels,framerate; //audio rate, channels and frame rate for system ettings
    int resolutionX, resolutionY;
    int vbrate,abrate, videoBIN; //What bin I will to use in my pipeline?
    QString youtube;
    QString videotcp, videoPath; //Line edith paths, ip and port or file path
    QString localCamera, localAudioCard; //local paths for sound cards and video locall cameras
    int vport;

private slots:
    void on_buttonBox_accepted();

    void on_Resolution_currentIndexChanged(int index);

    void on_Audiorate_currentIndexChanged(int index);

    void on_Channels_currentIndexChanged(int index);

    void on_VideoBitRate_currentIndexChanged(int index);

    void on_AudioBitRate_currentIndexChanged(int index);

    void on_Framerate_currentIndexChanged(int index);

    void on_VideoSRC_currentIndexChanged(int index);

    void on_checkBox_clicked(bool checked);

    void on_LocalCamera_currentIndexChanged(int index);

    void on_soundCards_currentIndexChanged(int index);


private:
    Ui::inputBox *ui;
};

#endif // INPUTBOX_H
