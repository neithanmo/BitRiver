#ifndef DATASRC
#define DATASRC
#include <gst/gst.h>
#include <QString>
#include <iostream>


class Datasrc
{
public:
    friend class gstvideo;
    Datasrc(int type, QString &name); //local data constructor
    Datasrc(QString &location, QString &name, bool &loop);//filesrc constructor
    Datasrc(QString &host, int &port, QString &name); //tcpsrc constructor
    ~Datasrc();
protected:

    GstElement *databin;
    GstElement *src;
    GstElement *decoder;
    GstElement *vqueue;
    GstElement *aqueue;
    GstElement *aconvert;
    GstElement *vconvert;
    GstElement *asample;
    GstCaps *acaps;
    GstCaps *vcaps;
    QString *srcname;
    GstPad *videosrc, *audiosrc;
    gboolean first_segment;
    GstClockTime offset;

    inline GstElement* get_bin(){return databin;}

    inline void datasrc_set_ghost_vpad(){
        videosrc = gst_element_get_static_pad(vqueue,"src");
        gst_element_add_pad (databin, gst_ghost_pad_new ("videosrc", videosrc));
    }

    inline void datasrc_set_ghost_apad(){
        audiosrc = gst_element_get_static_pad(aqueue,"src");
        gst_element_add_pad (databin, gst_ghost_pad_new ("audiosrc", audiosrc));
    }


    static void pad_added(GstElement *src, GstPad *new_pad, Datasrc *v);
    static gboolean bus_call(GstBus *ebus, GstMessage *msg, Datasrc *data);
    static GstPadProbeReturn bus_eos(GstPad * pad, GstPadProbeInfo * info, Datasrc *v);
    static void callb(GstObject *src, GstMessage, Datasrc *v);
    static gboolean doloop(Datasrc *v);

};
#endif // DATASRC_H



