#ifndef DATASRC
#define DATASRC
#include <gst/gst.h>
#include <QString>
#include <iostream>


class Datasrc
{
public:
    friend class gstvideo;
    Datasrc(std::string &device);
    Datasrc(std::string &location, bool &loop);
    Datasrc(std::string &host, std::string &port);
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



    //static void bus_callback(GstBus *ebus, GstMessage *msg, Datasrc *data);

};
#endif // DATASRC_H



