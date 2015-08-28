#ifndef GSTVIDEO_H
#define GSTVIDEO_H

#include <QWidget>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/colorbalance.h>
#include <gst/video/videooverlay.h>
#include <QMessageBox>
#include <QSlider>
#include "gstaudio.h"
#include <math.h>


namespace Ui {
class gstvideo;
class gstaudio;
}


class gstvideo : public QWidget
{
    Q_OBJECT

public:
    gstvideo(QWidget *parent = 0);
    ~gstvideo();
    gstaudio *audio;

private slots:
    void start();
    void stop();
    void contrast(int); //slots para llamar a update_color_balance, ya que esta no se puede llamar directamente
    void brightness(int); //debido a que SIGNALS and SLOTS deben concordar en cuanto a sus parametros
    void hue(int);
    void saturation(int);
    void on_comboBox_currentIndexChanged(int index);
    void volume(int);

private:
    Ui::gstvideo *ui;
    WId window;
    GstCaps *caps;
    GstElement *src;
    GstElement *conversor1;
    GstElement *videobalance;
    GstElement *sink;
    GstElement *audiosink;
    GstBus *bus;
    GMainLoop *loop;
    static GstBusSyncReply bus_sync_handler (GstBus *, GstMessage *, gpointer);
    static guintptr cam_window_handle;
    void update_color_channel (gchar*, gint, GstColorBalance*);
    static GstPadProbeReturn event_eos(GstPad *pad, GstPadProbeInfo *info, gpointer user_data);
    static GstPadProbeReturn block_src(GstPad *pad, GstPadProbeInfo *info, gpointer user_data);
    static gboolean to_block_src(gpointer user_data);
    //int effect;
    /*st-launch-1.0 v4l2src ! videoconvert ! videobalance ! videoconvert ! agingtv ! videoconvert ! autovideosink*/

};

#endif // GSTVIDEO_H
