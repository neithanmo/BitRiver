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
#include <vector>
#include "ui_gstvideo.h"
#include "inputbox.h"
#include "gstvideo.h"//for moc compiling happiness
#include "datasrc.h"
#include <iostream>



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
    Datasrc *source;
    std::vector <Datasrc *> dsrc;  //Vector of datasrc objects - they may be local data, tcp or from a file
                                    //and will created dinamically
    // ################## Video Element ##############################################################
    GstCaps *Vcaps;
    GstCaps *enVcaps;
    GstElement *Vdefault;
    GstElement *conversor1;
    GstElement *videobalance;
    GstCaps *Scaps;
    GstElement *videosinkconvert;
    GstElement *videorate;
    GstElement *sink; //ximagesink
    GstElement *x264enc;
    GstElement *h264parse;
    GstElement *avdec_h264;
    GstElement *Vscale;
    GstElement *Sscale;
    GstElement *scale;
    GstElement *Svideoconvert;
    GstElement *Svideoconvert2;
    GstElement *videoSelector;
    GstElement * defaultcamera;


    //################## Audio elements #############################################################
    GstCaps *Acaps;
    GstCaps *enAcaps;
    GstElement *Adefault;
    GstElement *conv;
    GstElement *volume;
    GstElement *audiorate;
    GstElement *audiosampler;
    GstElement *audiosink;
    GstElement *aacparse;
    GstElement *faac;
    GstElement *audioparse;
    GstElement *audiomixer;
//####################### Encoding and others elements #############################################
    GstElement *flvmux;
    GstElement *Ltee1;
    GstElement *Ltee2;
    GstElement *rtmp;
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
    GstElement *filesink;
    GstElement *tcpsink;
    GstBus *bus;
    GMainLoop *loop;
    //##############################################################################################

    QString videopath, audiopath, youkey;

    //########################## Gstreamer functions ###############################################

    void update_color_channel (gchar*, gint, GstColorBalance*);
    static GstBusSyncReply bus_sync_handler (GstBus *, GstMessage *, gstvideo *v);
    static guintptr cam_window_handle;
    static GstPadProbeReturn event_eos(GstPad *pad, GstPadProbeInfo *info, gstvideo *v);
    static GstPadProbeReturn block_src(GstPad *pad, GstPadProbeInfo *info, gstvideo *v);
    static void callback(GstBus  *bus, GstMessage *msg, gstvideo *v);
    void configure();
    void addSource();


};

#endif // GSTVIDEO_H
