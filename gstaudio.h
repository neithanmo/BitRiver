#ifndef GSTAUDIO_H
#define GSTAUDIO_H

#include <QWidget>
#include <glib.h>
#include <gst/gst.h>
#include <QMessageBox>
#include <QSlider>
#include <gst/audio/streamvolume.h>

static GstElement *bin;
class gstaudio
{
public:
    gstaudio();
    ~gstaudio();
    GstElement *audiosrc;
    GstElement *conv;
    //GstElement *volume;
    GstElement *asink;
    void start();
    void pause();
    void avolume(gint);
};

#endif // GSTAUDIO_H
