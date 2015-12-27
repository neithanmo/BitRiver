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

#ifndef GSTVIDEO_H
#define GSTVIDEO_H

#include <QWidget>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/colorbalance.h>
#include <gst/video/videooverlay.h>
#include <QMessageBox>
#include <QSlider>
#include <math.h>
#include <QLineEdit>
#include <gst/audio/streamvolume.h>
#include "ui_gstvideo.h"
#include "inputbox.h"
#include <string.h>

namespace Ui {
class gstvideo;
//class gstaudio;
}
//..

class gstvideo : public QWidget
{
    Q_OBJECT

public:
    gstvideo(QWidget *parent = 0);
    ~gstvideo();


private slots:
    void start();
    void stop();
    void contrast(int); //slots para llamar a update_color_balance, ya que esta no se puede llamar directamente
    void brightness(int); //debido a que SIGNALS and SLOTS deben concordar en cuanto a sus parametros
    void hue(int);
    void saturation(int);
    void on_comboBox_currentIndexChanged(int index);
    void avolume(int);    

private:
    Ui::gstvideo *ui;
    WId window;
    inputBox *input = new inputBox;
    GstCaps *Vcaps; //filtro para visualizar el stream a 640x480
    GstCaps *Scaps; //resolucion del streaming, la resolucion es definida por el usuario
    GstCaps *Acaps;
    GstCaps *enAcaps; //audio encoding output format
    GstCaps *enVcaps;//video encoding output format
    GstElement *Vlocalsrc;
    GstElement *Vtcpsrc; //tcp videosource;
    GstElement *Vfilesrc;
    GstElement *Atcpsrc; //tcp audio source;
    GstElement *Afilesrc; //file audio source
    GstElement *conversor1; //videoconvert for visualization
    GstElement *conversor2;
    GstElement *videobalance;
    GstElement *sink;
    GstElement *audiosink;
    GstElement *Alocalsrc;
    GstElement *conv;       //audioconvert
    GstElement *audiosampler;
    GstElement *videosinkconvert;
    GstElement *videorate;
    GstElement *audiorate;
    GstElement *audiosinkconvert;
    GstElement *audioparse;
    GstElement *abin;       //audio bin, para captura de microfono, control de volumen
    GstElement *vV4L2bin;   //video local camera source bin
    GstElement *volume;
    GstElement *aacparse;
    GstElement *x264enc;
    GstElement *faac;
    GstElement *h264parse;
    GstElement *tcpclientsrc;
    GstElement *avdec_h264;
    GstElement *flvmux;
    GstElement *Ltee1; //tee for video
    GstElement *Ltee2;//tee for audio
    GstElement *rtmp;
    GstElement *scale;
    GstElement *Vscale;

    GstBus *bus;
    GMainLoop *loop;
    QString videopath, audiopath, youkey;//path al archivo y key para youtube
    bool audioSame;
    static GstBusSyncReply bus_sync_handler (GstBus *, GstMessage *, gpointer);//window sync
    static guintptr cam_window_handle;
    void update_color_channel (gchar*, gint, GstColorBalance*);
    static GstPadProbeReturn event_eos(GstPad *pad, GstPadProbeInfo *info, gpointer user_data);
    static GstPadProbeReturn block_src(GstPad *pad, GstPadProbeInfo *info, gpointer user_data);
    static gboolean to_block_src(gpointer user_data);
    static void callback(GstBus  *bus, GstMessage *msg, gpointer user_data);
    static void videoPad_added_handler(GstElement *src, GstPad *new_pad, gpointer user_data);

};

#endif // GSTVIDEO_H
