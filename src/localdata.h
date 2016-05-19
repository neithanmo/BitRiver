#ifndef LOCALDATA_H
#define LOCALDATA_H
#include "datasrc.h"
#include<iostream>

class localData : public virtual Datasrc
{

public:
    localData();
    ~localData();
    GstElement* get_bin(){return databin;}
    void datasrc_set_ghost_vpad(){

       GstPad *pad = gst_element_get_static_pad(queue1,"src");
       gst_element_add_pad (databin, gst_ghost_pad_new ("videosrc", pad));
       g_object_unref(pad);
       std::cout<<"ghost pad listo"<<std::endl;
    }

    void datasrc_set_ghost_apad(){
        std::cout<<"nada que hacer"<<std::endl;

    }
};

#endif // LOCALDATA_H
//clases bases no declaran redefinen los metodos de la clase base.
