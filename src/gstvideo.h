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
#include <QObject>
#include <math.h>
#include <QLineEdit>
#include <gst/audio/streamvolume.h>
#include <string.h>
#include "ui_gstvideo.h"
#include "inputbox.h"
#include "gstvideo.h"//for moc compiling happiness
#include "localdata.h"


namespace Ui {
class gstvideo;

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
    void contrast(int);
    void brightness(int);
    void hue(int);
    void saturation(int);
    void on_comboBox_currentIndexChanged(int index);
    void avolume(int);
private:
    Ui::gstvideo *ui;
    WId window;
    inputBox *input = new inputBox;
    GstCaps *Vcaps;
    GstCaps *Scaps;
    GstCaps *Acaps;
    GstCaps *enAcaps;
    GstCaps *enVcaps;
    GstElement *Vlocalsrc;
    GstElement *Vtcpsrc;
    GstElement *Vfilesrc;
    GstElement *Atcpsrc;
    GstElement *Afilesrc;
    GstElement *conversor1;
    GstElement *conversor2;
    GstElement *videobalance;
    GstElement *sink;
    GstElement *audiosink;
    GstElement *Alocalsrc;
    GstElement *conv;
    GstElement *audiosampler;
    GstElement *videosinkconvert;
    GstElement *videorate;
    GstElement *audiorate;
    GstElement *audioparse;
    GstElement *abin;
    GstElement *vV4L2bin;
    GstElement *volume;
    GstElement *aacparse;
    GstElement *x264enc;
    GstElement *faac;
    GstElement *h264parse;
    GstElement *tcpclientsrc;
    GstElement *avdec_h264;
    GstElement *flvmux;
    GstElement *Ltee1;
    GstElement *Ltee2;
    GstElement *rtmp;
    GstElement *scale;
    GstElement *Vscale;
    GstElement *Sscale;
    GstElement *Svideoconvert;
    GstElement *Svideoconvert2;
    GstElement *queue1;
    GstElement *queue2;
    GstElement *queue3;
    GstElement *queue4;
    GstElement *queue5;
    GstElement *queue6;
    GstElement *queue7;
    GstElement *queue8;
    GstElement *queue9;
    GstElement *pipeline;
    GstElement *curr ;
    GstElement *conv_before;
    GstElement *conv_after;
    GstElement *vdecoder;


    GstBus *bus;
    GMainLoop *loop;
    QString videopath, audiopath, youkey;
    bool audioSame;
    void update_color_channel (gchar*, gint, GstColorBalance*);

    static GstBusSyncReply bus_sync_handler (GstBus *, GstMessage *, gstvideo *v);
    static guintptr cam_window_handle;
    static GstPadProbeReturn event_eos(GstPad *pad, GstPadProbeInfo *info, gstvideo *v);
    static GstPadProbeReturn block_src(GstPad *pad, GstPadProbeInfo *info, gstvideo *v);
    static void callback(GstBus  *bus, GstMessage *msg, gstvideo *v);
    static void videoPad_added_handler(GstElement *src, GstPad *new_pad, gstvideo *v);



};

#endif // GSTVIDEO_H
