#include "datasrc.h"
#include <math.h>

Datasrc::Datasrc(){
    std::cout<<"entering to constructor localData"<<std::endl;
    databin = gst_bin_new("localdata");
    src = gst_element_factory_make("v4l2src","camara");
    queue1 = gst_element_factory_make("queue","q1");
    queue2 = gst_element_factory_make("queue","q2");
    gst_bin_add_many(GST_BIN(databin),src,queue1,NULL);
    gst_element_link_many(src,queue1,NULL);
    vpad = gst_element_get_static_pad(queue1,"src");
    apad = gst_element_get_static_pad(queue2,"src");
    x = rand();
    std::cout<<"X = :"<< x << std::endl;
    //g_object_set(src, "do-timestamp", TRUE, "device", videoDevice.toUtf8().constData(), NULL);
    //datasrc_set_ghost_vpad();
}

Datasrc::~Datasrc(){
    g_object_unref(databin);
}



