#include "datasrc.h"
static QString locate;

Datasrc::Datasrc(int type, QString &name){
    srcname = &name;
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

    srcname = &name;
    videosrc = NULL;
    audiosrc = NULL;
    first_segment = true;
    databin = gst_bin_new(name.toUtf8().constData());
    src = gst_element_factory_make("filesrc","file");
    decoder = gst_element_factory_make("decodebin","decoder");
    vqueue = gst_element_factory_make("queue","vqueue");
    vcaps = gst_caps_from_string("video/x-raw, format=I420, interlace-mode=progressive");
    vconvert = gst_element_factory_make("videoconvert","vconvert");
    aqueue = gst_element_factory_make("queue","aqueue");
    asample = gst_element_factory_make("audioresample","asample");
    aconvert = gst_element_factory_make("audioconvert","aconvert");
    acaps = gst_caps_from_string("audio/x-raw, format=S16LE, layout=interleaved");
    gst_bin_add_many(GST_BIN(databin),src,decoder,vconvert,
                     vqueue, aconvert,asample,aqueue, NULL);                         //FILESRC
    gst_element_link(src,decoder);
    gst_element_link_many(aconvert, asample, aqueue,NULL);
    gst_element_link(vconvert, vqueue);
    g_object_set(src, "do-timestamp", false, "location",
                 location.toUtf8().constData(), "typefind", false, NULL);
    datasrc_set_ghost_vpad();
    datasrc_set_ghost_apad();
    gst_element_set_state(databin, GST_STATE_READY);
     //GstBus *mbus = gst_pipeline_get_bus(GST_PIPELINE(databin));
//    GstBus *mbus;
//    gst_element_set_bus(GST_ELEMENT(databin), mbus);
//    if(mbus == NULL) g_print("bus is NULL\n");
    //gst_bus_add_signal_watch(mbus);
//    g_signal_connect(mbus, "message::eos", G_CALLBACK(bus_call), this);


    /*if(loop){
       gst_pad_add_probe(gst_element_get_static_pad(vconvert,"sink"), GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM,
                                (GstPadProbeCallback)bus_eos, this, NULL);
    }*/
}

Datasrc::Datasrc(QString &host, int &port, QString &name){
    srcname = &name;
    videosrc = NULL;
    audiosrc = NULL;
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
    g_object_unref(databin);
}

void Datasrc::pad_added(GstElement *src, GstPad *new_pad, Datasrc *v) {
    Q_UNUSED(src);
    GstPad *sinkpad = NULL;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
    if (g_strrstr (gst_structure_get_name (new_pad_struct), "video"))
         sinkpad = gst_element_get_static_pad(v->vconvert, "sink");
    else
         sinkpad = gst_element_get_static_pad (v->aconvert, "sink");
    gst_pad_set_offset(new_pad, v->offset);
    gst_pad_link (new_pad, sinkpad);
    //gst_pad_add_probe(new_pad, GST_PAD_PROBE_TYPE_EVENT_BOTH,
                             //(GstPadProbeCallback)bus_eos, v, NULL);
    gst_caps_unref (new_pad_caps);
    gst_object_unref (sinkpad);
}


GstPadProbeReturn Datasrc::bus_eos(GstPad * pad, GstPadProbeInfo * info, Datasrc *v){
    GstEvent *event_pad = gst_pad_probe_info_get_event(info);
    GstEventType event_type = event_pad->type;

    switch (event_type) {

    case GST_EVENT_SEGMENT_DONE:{
        g_print("SEGMENT_DONE from ""%s"" \t ---> seeking again \n", v->srcname->toUtf8().constData());
        GstSeekFlags seek_flags;
        int flags = GST_SEEK_FLAG_SEGMENT;
        seek_flags = GstSeekFlags(flags);
        //gst_debug_set_threshold_from_string ("decodebin:6", TRUE);
        gst_element_seek(v->decoder,1.0, GST_FORMAT_TIME, seek_flags,
                         GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_SET, -1);
        return GST_PAD_PROBE_DROP;
    }
        break;

     case GST_EVENT_QOS:{
        //g_print("QoS event, discarting \n");
        return GST_PAD_PROBE_DROP;
        }
        break;

     default:
        //g_print("upstream event type: %s\n", GST_EVENT_TYPE_NAME(event_pad));
        return GST_PAD_PROBE_OK;
        break;
    }

}

gboolean Datasrc::doloop(Datasrc *v){
    g_print("Firts loop\n");
    GstSeekFlags seek_flags;
    int flags = GST_SEEK_FLAG_SEGMENT;
    seek_flags = GstSeekFlags(flags);
    //gst_debug_set_threshold_from_string ("decodebin:6", TRUE);
    gst_element_seek(v->decoder, 1.0, GST_FORMAT_TIME, seek_flags,
                     GST_SEEK_TYPE_SET, 0, GST_SEEK_TYPE_SET, -1);
    return false;
}


gboolean Datasrc::bus_call(GstBus *bus, GstMessage* msg, Datasrc *v)
{

    g_print("Got message type: %s, from %s\n", GST_MESSAGE_TYPE_NAME(msg), gst_object_get_name(msg->src));
    GstSeekFlags seek_flags;
    gboolean ret;
    gint64 position_nano;
    gst_element_query_duration(v->decoder, GST_FORMAT_TIME, &position_nano);
    g_print ("Segment: %" GST_TIME_FORMAT "-%" GST_TIME_FORMAT "\n",
        GST_TIME_ARGS (0), GST_TIME_ARGS (position_nano));
    int flags = GST_SEEK_FLAG_ACCURATE | GST_SEEK_FLAG_SEGMENT;
    flags |= GST_SEEK_FLAG_FLUSH;
    seek_flags = GstSeekFlags(flags);
     //seek_flags = GST_SEEK_FLAG_SEGMENT;
     ret = gst_element_seek (v->decoder, 1.0, GST_FORMAT_TIME, seek_flags,
                              GST_SEEK_TYPE_SET, G_GINT64_CONSTANT (0), GST_SEEK_TYPE_SET, position_nano);
     return TRUE;
}








