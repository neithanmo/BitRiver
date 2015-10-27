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


namespace Ui {
class gstvideo;
//class gstaudio;
}


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
    GstCaps *Vcaps; //filtro para visualizar el stream a 640x480
    GstCaps *Scaps; //resolucion del streaming, la resolucion es definida por el usuario
    GstElement *Vlocalsrc;
    GstElement *Vtcpsrc; //tcp videosource;
    GstElement *Vfilesrc;
    GstElement *Atcpsrc; //tcp audio source;
    GstElement *Afilesrc; //file audio source
    GstElement *conversor1; //videoconvert for visualization
    GstElement *videobalance;
    GstElement *sink;
    GstElement *audiosink;
    GstElement *Alocalsrc;
    GstElement *conv;       //audioconvert
    GstElement *queue;
    GstElement *audiosampler;
    // ######## Custom Bins ##########################################################################
    GstElement *abin;       //audio bin, para captura de microfono, control de volumen
                            // tambien se utiliza para el streaming
    GstElement *aTCPbin;    // Audio bin for tcp audio source
    GstElement * aFILEbin;  // audio file source bin
    GstElement *vTCPbin;    //tcp video source bin
    GstElement *vV4L2bin;   //video local camera source bin
    GstElement *vFILEbin;   //video file source bin
    GstElement *volume;
    GstElement *aacparse;
    GstElement *x264enc;
    GstElement *faac;
    GstElement *h264parse;
    GstElement *tcpclientsrc;
    GstElement *decoder;
    GstElement *avdec_h264;
    GstElement *flvmux;
    GstElement *Ltee; //tee for live streaming and visualization on screen
    GstElement *rtmp;
    GstBus *bus;
    GMainLoop *loop;
    static GstBusSyncReply bus_sync_handler (GstBus *, GstMessage *, gpointer);//window sync
    static guintptr cam_window_handle;
    void update_color_channel (gchar*, gint, GstColorBalance*);
    static GstPadProbeReturn event_eos(GstPad *pad, GstPadProbeInfo *info, gpointer user_data);
    static GstPadProbeReturn block_src(GstPad *pad, GstPadProbeInfo *info, gpointer user_data);
    static gboolean to_block_src(gpointer user_data);
    //void avolume(gint);
    //int effect;
    // BIN V4L2 SOURCE/##################################
    /* gst-launch-1.0 v4l2src ! videoconvert ! videobalance ! videoconvert ! agingtv ! videoconvert ! autovideosink */

     // BIN TCPVIDEOSRC ###########################################################################################
      /* "tcpclientsrc host=163.178.119.218 port=5000 ! flvdemux name=demux1 ! h264parse ! avdec_h264 max-threads=4 ! videorate" */


};

#endif // GSTVIDEO_H
