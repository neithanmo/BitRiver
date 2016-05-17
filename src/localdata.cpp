#include "localdata.h"

localData::localData()
{
    databin = gst_bin_new("datasrcBin");
    src = gst_element_factory_make("v4l2src","camara");
    queue1 = gst_element_factory_make("queue","q1");
    gst_bin_add_many(GST_BIN(this->databin),src,queue1,NULL);
    gst_element_link_many(src,queue1,NULL);
    //GstPad *pad2 = gst_element_get_static_pad(databin,"videosrc");

}

void Datasrc::datasrc_request_vpad()
{
   GstPad *pad = gst_element_get_static_pad(queue1,"src");
   gst_element_add_pad (this->databin, gst_ghost_pad_new ("videosrc", pad));
   g_object_unref(pad);
}

