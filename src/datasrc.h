#ifndef DATASRC
#define DATASRC
#include <gst/gst.h>
#include <QString>
#include <iostream>


class Datasrc
{
public:
    friend class gstvideo;
    Datasrc(QString &device, QString &name); //local data constructor
    Datasrc(QString &location, QString &name, bool &loop);//filesrc constructor
    Datasrc(QString &host, int &port, QString &name); //tcpsrc constructor
    ~Datasrc();
protected:

    GstElement *databin;
    GstElement *src;
    GstElement *decoder;
    GstElement *vqueue;
    GstElement *aqueue;

    inline GstElement* get_bin(){return databin;}

    inline void datasrc_set_ghost_vpad(){
        GstPad *pad = gst_element_get_static_pad(vqueue,"src");
        gst_element_add_pad (databin, gst_ghost_pad_new ("videosrc", pad));
        g_object_unref(pad);
    }

    inline void datasrc_set_ghost_apad(){
        GstPad *pad = gst_element_get_static_pad(aqueue,"src");
        gst_element_add_pad (databin, gst_ghost_pad_new ("audiosrc", pad));
        g_object_unref(pad);
    }


    static void pad_added(GstElement *src, GstPad *new_pad, Datasrc *v);
    static void bus_callback(GstBus *ebus, GstMessage *msg, Datasrc *data);
    static GstPadProbeReturn bus_eos(GstPad * pad, GstPadProbeInfo * info, Datasrc *v);

};
#endif // DATASRC_H



