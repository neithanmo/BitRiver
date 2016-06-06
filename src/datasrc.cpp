#include "datasrc.h"


Datasrc::Datasrc(int type, QString &name){
    databin = gst_bin_new(name.toUtf8().constData());
    if(type == 0){
        src = gst_element_factory_make("v4l2src","local");
        vqueue = gst_element_factory_make("queue","vqueue");
        gst_bin_add_many(GST_BIN(databin),src,vqueue,NULL);
        gst_element_link_many(src,vqueue,NULL);
        g_object_set(src, "do-timestamp", TRUE,
                     "device", name.toUtf8().constData(),NULL);
        datasrc_set_ghost_vpad();
    }
    if(type == 1){
        src = gst_element_factory_make("alsasrc",NULL);
        acaps = gst_caps_from_string("audio/x-raw, format=S16LE, layout=interleaved");
        aqueue = gst_element_factory_make("queue","aqueue");
        gst_bin_add_many(GST_BIN(databin),src,aqueue,NULL);
        gst_element_link_filtered(src, aqueue, acaps);
        g_object_set(src, "do-timestamp", TRUE,
                     "device", name.toUtf8().constData(), NULL);
        datasrc_set_ghost_apad();
    }
}

Datasrc::Datasrc(QString &location, QString &name, bool &loop){

    std::cout<<"entering to filesrc constructor"<<std::endl;
    databin = gst_bin_new(name.toUtf8().constData());
    src = gst_element_factory_make("filesrc","file");
    decoder = gst_element_factory_make("decodebin","decoder");
    vqueue = gst_element_factory_make("queue","vqueue");
    vcaps = gst_caps_from_string("video/x-raw, format=BGRA, interlace-mode=progressive");
    vconvert = gst_element_factory_make("videoconvert","vconvert");
    aqueue = gst_element_factory_make("queue","aqueue");
    aconvert = gst_element_factory_make("audioconvert","aconvert");
    acaps = gst_caps_from_string("audio/x-raw, format=S16LE, layout=interleaved");
    gst_bin_add_many(GST_BIN(databin),src,decoder,vconvert,
                     vqueue, aconvert,aqueue, NULL);                         //FILESRC
    gst_element_link_many(src,decoder,NULL);
    gst_element_link_filtered(aconvert, aqueue, acaps);
    gst_element_link_filtered(vconvert, vqueue, vcaps);
    g_object_set(src, "do-timestamp", false, "location",
                 location.toUtf8().constData(), "typefind", false, NULL);
    datasrc_set_ghost_vpad();
    datasrc_set_ghost_apad();
}

Datasrc::Datasrc(QString &host, int &port, QString &name){
    databin = gst_bin_new(name.toUtf8().constData());
    src = gst_element_factory_make("tcpclientsrc","tcp-server");
    decoder = gst_element_factory_make("decodebin","decoder");
    vqueue = gst_element_factory_make("queue","vqueue");
    vcaps = gst_caps_from_string("video/x-raw, format=BGRA, interlace-mode=progressive");
    vconvert = gst_element_factory_make("videoconvert","vconvert");
    aqueue = gst_element_factory_make("queue","aqueue");
    aconvert = gst_element_factory_make("audioconvert","aconvert");
    acaps = gst_caps_from_string("audio/x-raw, format=S16LE, layout=interleaved");
    gst_bin_add_many(GST_BIN(databin),src,decoder,vconvert,
                     vqueue, aconvert,aqueue, NULL);                         //TCPSRC
    gst_element_link_many(src,decoder,NULL);
    gst_element_link_filtered(aconvert, aqueue, acaps);
    gst_element_link_filtered(vconvert, vqueue, vcaps);
    g_object_set(src, "host", host.toUtf8().constData(), "port", port, NULL);
    datasrc_set_ghost_vpad();
    datasrc_set_ghost_apad();
}

Datasrc::~Datasrc(){
    //g_object_unref(databin);
}

void Datasrc::pad_added(GstElement *src, GstPad *new_pad, Datasrc *v) {
    Q_UNUSED(src);
    GstPad *sinkpad = NULL;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    if (g_strrstr (gst_structure_get_name (new_pad_struct), "video")){ //checking if there is video caps
         sinkpad = gst_element_get_static_pad(v->vconvert, "sink");
    }
    else
         sinkpad = gst_element_get_static_pad (v->aconvert, "sink"); //it is a audio caps structure
    gst_pad_link (new_pad, sinkpad);
    gst_caps_unref (new_pad_caps);
    gst_object_unref (sinkpad);
}


GstPadProbeReturn Datasrc::bus_eos(GstPad * pad, GstPadProbeInfo * info, Datasrc *v)
{
    //Q_UNUSED(data);
    //Q_UNUSED(ebus);
    //Q_UNUSED(msg);
    if (GST_EVENT_TYPE (GST_PAD_PROBE_INFO_DATA (info)) != GST_EVENT_EOS)
        return GST_PAD_PROBE_OK;
     g_print("recibing EOS message from \n");
     gst_element_seek(v->src,
                   1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
                   GST_SEEK_TYPE_SET, 0,
                   GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE);
     g_print("removing eos probe \n");
     gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));
     return GST_PAD_PROBE_DROP;

}




