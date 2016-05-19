#include "localdata.h"

localData::localData(){
    std::cout<<"entring to constructor localData"<<std::endl;
    databin = gst_bin_new("localdata");
    src = gst_element_factory_make("v4l2src","camara");
    queue1 = gst_element_factory_make("queue","q1");
    gst_bin_add_many(GST_BIN(databin),src,queue1,NULL);
    gst_element_link_many(src,queue1,NULL);
    datasrc_set_ghost_vpad();
    //GstPad *pad2 = gst_element_get_static_pad(databin,"videosrc");

}


