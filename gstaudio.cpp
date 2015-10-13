#include "gstaudio.h"


static GstElement *volume;
gstaudio::gstaudio()
{
    /*g_print("%s", "hola audio");
    gst_init(NULL, FALSE);
    this->audiosrc = gst_element_factory_make("alsasrc", "asrc");
    this->conv = gst_element_factory_make("audioconvert","aconv");
    volume = gst_element_factory_make("volume","volume");
    this->asink = gst_element_factory_make("autoaudiosink","asink");
    bin = gst_pipeline_new("bin");
    if (!this->audiosrc || !this->conv || !bin || !volume){
        qDebug("no se crearon todos los elementos necesarios");
        return;
    }
    g_object_set(G_OBJECT(asink),"sync", "false", NULL);
    g_object_set(G_OBJECT(audiosrc),"do-timestamp", "true", NULL);
    g_object_set(volume, "volume", 0, NULL);
    gst_bin_add_many(GST_BIN(bin), this->audiosrc, this->conv, volume, NULL);
    gst_element_link_many(this->audiosrc, this->conv, volume, NULL);

}

gstaudio::~gstaudio(){
    //gst_element_set_state(GST_ELEMENT(bin), GST_STATE_NULL);
    //gst_object_unref(bin);
    exit(0);
}

void gstaudio::start(){
    //gst_element_set_state (bin, GST_STATE_PLAYING);
    g_print("%s", "playing audio from alsasrc ");
}

void gstaudio::pause(){
    if (bin != NULL)
    {
        //gst_element_set_state (bin, GST_STATE_PAUSED);
        //g_object_unref(bin);
    }
}

void gstaudio::avolume(gint value){
    gdouble y = value/10.0;
    g_print("%d", y);
    gst_stream_volume_set_volume (GST_STREAM_VOLUME(volume), GST_STREAM_VOLUME_FORMAT_LINEAR, y);*/

}

