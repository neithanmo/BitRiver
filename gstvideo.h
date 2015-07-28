#ifndef GSTVIDEO_H
#define GSTVIDEO_H

#include <QWidget>
#include <glib.h>
#include <gst/gst.h>
#include <gst/video/colorbalance.h>
#include <gst/video/videooverlay.h>
#include <QSlider>


namespace Ui {
class gstvideo;
}

class gstvideo : public QWidget
{
    Q_OBJECT

public:
    gstvideo(QWidget *parent = 0);
    ~gstvideo();


//protected:
    //GMainLoop *loop;
    //GstBus *bus;
    //GstElement *pipeline;
    //static void update_color_channel (const gchar *channel_name,
                                      //gboolean increase, GstColorBalance *cb);

private slots:
    void start();
    void stop();
private:
    Ui::gstvideo *ui;
    WId window;
    GstCaps *caps;
    GstElement *src;
    GstElement *conversor1;
    GstElement *pipeline;
    GstElement *videobalance;
    GstElement *sink;
    GstBus *bus;
    GMainLoop *loop;
    void configure();
    static GstBusSyncReply bus_sync_handler (GstBus *, GstMessage *, gpointer);
    static guintptr cam_window_handle;

};

#endif // GSTVIDEO_H
