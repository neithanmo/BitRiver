#ifndef DATASRC
#define DATASRC
#include <gst/gst.h>



class Datasrc
{
public:
    //Datasrc();
    //~Datasrc();
    virtual GstElement* get_bin(){return databin;}
    //virtual ~Datasrc(){ cout << "~Datasrc()";}
    friend class gstvideo;


protected:

    GstElement *databin;
    GstElement *src;
    GstElement *queue1;
    GstElement *queue2;
    GstElement *decoder;
    virtual void datasrc_set_ghost_vpad()=0;  // video ghost src pad of databin
    virtual void datasrc_set_ghost_apad()=0;  // audio ghost src pad of databin

};
#endif // DATASRC_H

/*
void Datasrc::datasrc_request_apad()
{
   GstPad *pad = gst_element_get_static_pad(queue2,"src");
   gst_element_add_pad (this->databin, gst_ghost_pad_new ("audiosrc", pad));
   g_object_unref(pad);
}
*/


