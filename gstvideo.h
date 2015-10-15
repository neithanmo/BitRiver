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

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::gstvideo *ui;
    WId window;
    GstCaps *Vcaps; //filtro para visualizar el stream a 640x480
    GstCaps *Scaps; //resolucion del streaming, la resolucion es definida por el usuario
    GstElement *src;
    GstElement *conversor1; //videoconvert for visualization
    GstElement *videobalance;
    GstElement *sink;
    GstElement *audiosink;
    GstElement *audiosrc;
    GstElement *conv;       //audioconvert
    GstElement *abin;       //audio bin, para captura de microfono, control de volumen
                            // tambien se utiliza para el streaming
    GstElement *v4l2srcBin; //bin para captura local de la camara de la computadora
    GstElement *volume;
    GstElement *aacparse;
    GstElement *x264enc;
    GstElement *faac;
    GstElement *h264parse;
    GstElement *tcpclientsrc;
    GstElement *decodebin;
    GstElement *avdec_h264;
    GstElement *flvmux;
    GstElement *Ltee; //tee for live streaming and visualization on screen
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
    /*gst-launch-1.0 v4l2src ! videoconvert ! videobalance ! videoconvert ! agingtv ! videoconvert ! autovideosink*/

};

#endif // GSTVIDEO_H
