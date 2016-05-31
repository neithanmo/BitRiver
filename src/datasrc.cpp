#include "datasrc.h"


Datasrc::Datasrc(std::string &device, std::string &name){
    std::cout<<"entering to v4l2src constructor"<<std::endl;
    databin = gst_bin_new(name.c_str());
    src = gst_element_factory_make("v4l2src","camara");                                    //V4L2SRC
    decoder = gst_element_factory_make("decodebin","decoder");
    vqueue = gst_element_factory_make("queue","vqueue");
    aqueue = gst_element_factory_make("queue","aqueue");
    gst_bin_add_many(GST_BIN(databin),src,decoder, vqueue,NULL);
    gst_element_link_many(src,decoder,NULL);
    g_object_set(src, "do-timestamp", TRUE, "device", device.c_str(), NULL);
    datasrc_set_ghost_vpad();
    std::cout<<"dispositivo = :"<< device << std::endl;
}

Datasrc::Datasrc(std::string &location, bool &loop, std::string &name){

    std::cout<<"entering to filesrc constructor"<<std::endl;
    databin = gst_bin_new(name.c_str());
    src = gst_element_factory_make("filesrc","file");
    decoder = gst_element_factory_make("decodebin","decoder");
    vqueue = gst_element_factory_make("queue","vqueue");
    aqueue = gst_element_factory_make("queue","aqueue");
//    ebus = gst_element_get_bus(src);
//    gst_bus_enable_sync_message_emission(ebus);
//    gst_bus_add_signal_watch(ebus);
    gst_bin_add_many(GST_BIN(databin),src,decoder, vqueue, aqueue, NULL);                      //FILESRC
    gst_element_link_many(src,decoder,NULL);
    g_object_set(src, "do-timestamp", TRUE, "location", location.c_str(), NULL);
    datasrc_set_ghost_vpad();
    datasrc_set_ghost_apad();
    std::cout<<"location = :"<< location << std::endl;
}

Datasrc::Datasrc(std::string &host, std::string &port, std::string &name){
    std::cout<<"entering to v4l2src constructor"<<std::endl;
    databin = gst_bin_new(name.c_str());
    src = gst_element_factory_make("tcpclientsrc","file");
    decoder = gst_element_factory_make("decodebin","decoder");
    vqueue = gst_element_factory_make("queue","vqueue");
    aqueue = gst_element_factory_make("queue","aqueue");
    gst_bin_add_many(GST_BIN(databin),src, decoder, vqueue, aqueue, NULL);                 //TCPSRC
    gst_element_link_many(src,decoder,NULL);
    g_object_set(src, "host", host.c_str(), "port", port.c_str(),NULL);
    datasrc_set_ghost_vpad();
    datasrc_set_ghost_apad();
}

Datasrc::~Datasrc(){
    //g_object_unref(databin);
}

void Datasrc::pad_added(GstElement *src, GstPad *new_pad, Datasrc *v) {
    //Q_UNUSED(src);
    g_print("entering into padd-added video function: \n");
    GstPad *sinkpad = NULL;
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);


    if (g_strrstr (gst_structure_get_name (new_pad_struct), "video")){ //checking if there is video caps
         g_print("new video pad added \n");
         sinkpad = gst_element_get_static_pad(v->vqueue, "sink");
         g_print("linked new pad with a peer done \n");
    }
    else
         sinkpad = gst_element_get_static_pad (v->aqueue, "sink"); //it is a audio caps structure
    gst_caps_unref (new_pad_caps);
    gst_pad_link (new_pad, sinkpad);
    gst_object_unref (sinkpad);
}



void Datasrc::bus_callback(GstBus *ebus, GstMessage *msg, Datasrc *data)
{
    //Q_UNUSED(data);
    //Q_UNUSED(ebus);
    //Q_UNUSED(msg);
    g_print("recibing EOS message from \n");
     /* restart playback if at end */
     if (!gst_element_seek(data->src,
              1.0, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
              GST_SEEK_TYPE_SET, 0,
              GST_SEEK_TYPE_NONE, GST_CLOCK_TIME_NONE)) {
                g_print("looping failed!\n");
            }
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




