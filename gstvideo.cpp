#include "gstvideo.h"

guintptr gstvideo::cam_window_handle;

static GstElement *pipeline; //= gst_pipeline_new("pipeline");
//static GstElement *bin; // audio bin
static GstElement *curr ;//= gst_element_factory_make("identity", "curr"); //current efect
static GstPad *blockpad; //source pad de mi fuente
static GstElement *conv_before;// = gst_element_factory_make("videoconvert", "conv_after");
static GstElement *conv_after;// = gst_element_factory_make("videoconvert", "conv_after");
static GstPad *binpad; //ghost pad para el "bin"
static GstElement *queue1;
static GstElement *queue2;
static int audioSAME;
static GstElement *vdecoder;
static GstElement *adecoder;
//static GstElement *volume;
static int effect=0;

//constructor, inicializo el gui, conecto los objetos, inicializo gstreamer,
//creo los elementos de gstreamer
gstvideo::gstvideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gstvideo)
{
    ui->setupUi(this);
    ui->slider1->setRange(-100,100);//contraste 0 -> 2. default=1
    ui->slider1->setTickPosition(QSlider::TicksAbove);
    ui->slider2->setRange(-100,100);//brillo    -1 -> 1. default=0
    ui->slider2->setTickPosition(QSlider::TicksAbove);
    ui->slider3->setRange(-100,100);//saturacion 0 -> 2. default=1
    ui->slider3->setTickPosition(QSlider::TicksAbove);
    ui->slider4->setRange(-100,100);//hue       -1 -> 1. default=0
    ui->slider4->setTickPosition(QSlider::TicksAbove);
    ui->slider1->setValue(0);
    ui->slider2->setValue(0);
    ui->slider3->setValue(0);
    ui->slider4->setValue(0);
    ui->slider5->setRange(0,10);//control del volumen
    ui->slider5->setValue(0);
    ui->slider5->setTickPosition(QSlider::TicksAbove);
    ui->progressBar1->setValue(0);
    ui->progressBar1->setRange(-100,100);//muestra el valor actual del contraste
    ui->progressBar2->setValue(0);
    ui->progressBar2->setRange(-100,100);//valor del brillo
    ui->progressBar3->setValue(0);
    ui->progressBar3->setRange(-100,100);//valor de la saturacion
    ui->progressBar4->setValue(0);
    ui->progressBar4->setRange(-100,100);//valor del HUE
    ui->comboBox->addItems(QStringList()<<"identity" <<"dicetv"
                            <<"warptv"<<"shagadelictv"<< "revtv"<< "radioactv"<< "rippletv"<<"TehRoxx0r"<<"Cartoon"<<"invert"
                           <<"pixeliz0r"<<"Nervous"<<"Vertigo"<<"Color Distance"<<"perspective"<<"color-B"<<"Baltan"<<"Twolay0r"<<"threelay0r"
                           <<"bw0r"<<"Sobel"<<"Distort0r");
    QObject::connect(ui->slider1, SIGNAL(valueChanged(int)),
                     ui->progressBar1, SLOT(setValue(int)));
    QObject::connect(ui->slider2, SIGNAL(valueChanged(int)),
                     ui->progressBar2, SLOT(setValue(int)));
    QObject::connect(ui->slider3, SIGNAL(valueChanged(int)),
                     ui->progressBar3, SLOT(setValue(int)));
    QObject::connect(ui->slider4, SIGNAL(valueChanged(int)),
                     ui->progressBar4, SLOT(setValue(int)));
    ui->widget->setFixedWidth(640);
    ui->widget->setFixedHeight(480);
    gst_init(NULL, FALSE);
    inputBox *input = new inputBox;
    input->exec();
    QString youkey = input->youtube;
    int width = input->resolutionX;
    int heigth = input->resolutionY;
    int framerate = input->framerate;
    int audiorate = input->arate;
    int channels = input->channels;
    int abitrate = input->abrate;
     int vbitrate = input->vbrate;
    audioSAME = input->audioBIN;
    this->videopath = input->videoPath;
    this->audiopath = input->audioPath;
    this->videoBIN = input->videoBIN;
    g_print("youtube key is : %s \n", youkey.toUtf8().constData());
    g_print("video Resolution: %dx%d \n", width, heigth);
    g_print("audio rate is: %d; audio bitrate is: %d \n", audiorate, abitrate);
    g_print("video settings - framerate: %d, video bitrate: %d \n",framerate, vbitrate);
    g_print("audio channels is: %d \n", channels);
    //WId window = ui->widget->winId();


//building all elements and BINS

    this->Vlocalsrc = gst_element_factory_make("v4l2src", "src");
    this->Alocalsrc = gst_element_factory_make("alsasrc", "asrc");
    this->conversor1 = gst_element_factory_make("videoconvert", "conversor1");
    this->conv = gst_element_factory_make("audioconvert","aconv");
    this->volume = gst_element_factory_make("volume","volume");
    this->x264enc = gst_element_factory_make("x264enc","x264enc");
    this->h264parse = gst_element_factory_make("h264parse","h264parse");
    this->avdec_h264 = gst_element_factory_make("avdec_h264","avdec_h264");
    this->sink = gst_element_factory_make("ximagesink", "sink");               //for local view
    this->videobalance = gst_element_factory_make("videobalance", "balance");
    this->audiosink = gst_element_factory_make("autoaudiosink", "ausink");
    this->faac = gst_element_factory_make("avenc_aac","faac");
    this->aacparse = gst_element_factory_make("aacparse", "aacparse");
    this->Afilesrc= gst_element_factory_make("filesrc", "Afilesrc");
    this->Atcpsrc = gst_element_factory_make("tcpclientsrc", "Atcpsrc");
    this->Vtcpsrc = gst_element_factory_make("tcpclientsrc", "Vtcpsrc");
    this->Vfilesrc = gst_element_factory_make("filesrc", "Vtcpsrc");
    queue1 = gst_element_factory_make("queue", "queue1");
    this->audiosampler = gst_element_factory_make("audioresample", "audiosampler");
    queue2 = gst_element_factory_make("queue", "queue2");
    this->Ltee2 = gst_element_factory_make("tee","tee1");

    this->abin = gst_bin_new("abin");
    this->aTCPbin = gst_bin_new("aTCPbin");
    this->aFILEbin = gst_bin_new("aFILEbin");


    this->vFILEbin = gst_bin_new("vFILEbin");
    this->vTCPbin = gst_bin_new("vTCPbin");
     this->vV4L2bin = gst_bin_new("vV4L2bin");

    int keyint = 2*framerate;
    //###### statics elements only for effects #########################################

    conv_after = gst_element_factory_make("videoconvert", "conv_after");
    conv_before = gst_element_factory_make("videoconvert", "conv_before");
    curr = gst_element_factory_make("identity", "curr");
    //#################################################################################

    g_object_set(this->volume, "volume", 0, NULL);
    g_object_set(this->faac, "bitrate", abitrate, NULL);
    g_object_set(this->x264enc, "bitrate", vbitrate, "key-int-max", keyint, "bframes", 0, "byte-stream", false, "aud", true, "tune", 2,
                 "threads", 0, "speed-preset", 2, NULL);
    const std::string path = this->videopath.toUtf8().constData();
    g_object_set(this->Vfilesrc, "location", "hola.mp4", NULL);
    g_object_set(this->Afilesrc, "location", this->audiopath.toUtf8().constData(), NULL);

   // "x264enc bitrate=$vbitrate key-int-max=$keyint bframes=$h264_bframes byte-stream=false aud=true tune=zerolatency"

    pipeline = gst_pipeline_new("pipeline");
    this->rtmp = gst_element_factory_make("rtmpsink","rtmp");
    this->flvmux = gst_element_factory_make("flvmux","flvmux");
    vdecoder = gst_element_factory_make("decodebin","vdecodebin");
    adecoder = gst_element_factory_make("decodebin","adecodebin");
    this->Ltee = gst_element_factory_make("tee","tee");
    this->Vcaps = gst_caps_new_simple("video/x-raw",
                   "width", G_TYPE_INT, 640,
                   "height", G_TYPE_INT, 480,
                    NULL);
    this->Scaps = gst_caps_new_simple("video/x-raw",
                   "width", G_TYPE_INT, width,
                   "height", G_TYPE_INT, heigth,
                   NULL);
    this->Acaps = gst_caps_new_simple("audio/x-raw",
                                      "format", G_TYPE_STRING, "S16LE",
                                      "layout", G_TYPE_STRING, "interleaved",
                   NULL);
    //video/x-h264,level=(string)'$h264_level',profile='$h264_profile
    this->enVcaps = gst_caps_new_simple("video/x-h264",
                   "level", G_TYPE_STRING, "4.1",
                   "profile", G_TYPE_STRING, "main",
                   NULL);
    //audio/mpeg,mpegversion=4,stream-format=raw
    this->enAcaps = gst_caps_new_simple("audio/mpeg",
                   "mpegversion", G_TYPE_INT, 4,
                   "stream-format", G_TYPE_STRING, "raw",
                    NULL);




    //########################### audio source BINS ###################################################
/*

    gst_bin_add_many(GST_BIN(this->aTCPbin), this->Atcpsrc, adecoder, queue2, this->conv, this->audiosampler, this->volume, NULL);
    gst_element_link_many(this->Afilesrc, adecoder, NULL); //adecoder->queue2 linked after, we need a callback and padd-added signal
    gst_element_link_many(queue2, this->conv, this->audiosampler, this->volume,  NULL);
    gst_element_add_pad (this->aTCPbin, gst_ghost_pad_new ("src", binpad));



    gst_bin_add_many(GST_BIN(this->aFILEbin), this->Afilesrc, adecoder, queue2, this->conv, this->audiosampler, this->volume,  NULL);
    gst_element_link_many(this->Afilesrc, adecoder, NULL);
    gst_element_link_many(queue2, this->conv, this->audiosampler, this->volume,  NULL);
    gst_element_add_pad (this->aTCPbin, gst_ghost_pad_new ("src", binpad));

    gst_object_unref(binpad);*/

    //################################################################################################

    //################################# video source BINS ############################################
/*


    gst_bin_add_many(GST_BIN(this->vFILEbin), this->Vfilesrc, vdecoder, queue1,  this->conversor1,
                     this->videobalance, conv_before, curr, conv_after, NULL);
    gst_element_link_many(this->Vfilesrc, vdecoder); //link vdecoder with queue1 dinamic
    gst_element_link_many(queue1,  this->conversor1);
    gst_element_link_filtered (this->conversor1,this->videobalance ,this->Scaps);
    gst_element_link_many(this->videobalance,conv_before, curr, conv_after, NULL);
    gst_element_add_pad (this->vFILEbin, gst_ghost_pad_new ("src", pad));



    gst_bin_add_many(GST_BIN(this->vTCPbin), this->Vtcpsrc, vdecoder, queue1,  this->conversor1,
                     this->videobalance, conv_before, curr, conv_after, NULL);
    gst_element_link_many(this->Vfilesrc, vdecoder); //link vdecoder with queue1 dinamic
    gst_element_link_many(queue1,  this->conversor1);
    gst_element_link_filtered (this->conversor1,this->videobalance ,this->Scaps);
    gst_element_link_many(this->videobalance,conv_before, curr, conv_after, NULL);
    gst_element_add_pad (this->vTCPbin, gst_ghost_pad_new ("src", pad));

    gst_object_unref(pad);*/

    // ########### Checking for errores building the elements ########################################################################

    if (!this->Vlocalsrc || !this->sink || !this->conversor1 || !pipeline || !this->videobalance ||
            !conv_before || !curr || !conv_after || !Vfilesrc || !Vtcpsrc ){
        qDebug("no se crearon todos los elementos de video necesarios");
        return;
    }
    if (!this->Alocalsrc || !this->conv || !this->volume || !audiosampler || !Atcpsrc || !Afilesrc || !faac || !aacparse){
        qDebug("no se crearon todos los elementos de audio necesarios");
        return;
    }


    if (!this->x264enc || !vdecoder || !this->h264parse || !flvmux || !Ltee || !queue1 || !queue2 || !rtmp || !Vcaps || !Scaps){
        qDebug("no se crearon todos los elementos de encodificación necesarios encoders");
        return;
    }


    /* if (!this->aFILEbin || !aTCPbin || !abin || !vFILEbin || !vTCPbin || !vV4L2bin){
         qDebug("any BINS created - error!! closing");
         return;
     } */

    //####################################################################################################################################
    binpad = gst_element_get_static_pad(this->volume, "src");               //getting pads for linking
    GstPad *pad = gst_element_get_static_pad(this->videobalance, "src");    //using them for ghost pads in my bins
    GstPad *pada = gst_element_get_static_pad(this->conv, "sink");

    if(input->isLocal)
    {
     // i will to use the vV4L2bin and abin - into my pipeline
        //recordar los elementos ue activan sus pad a solicitud (tee - flvmux - etc)

        blockpad = gst_element_get_static_pad(this->Vlocalsrc, "src");
                                   //audio local bin
        gst_bin_add_many(GST_BIN(this->abin), this->Alocalsrc, this->conv, this->volume, NULL);
        gst_element_link_many(this->Alocalsrc, this->conv, this->volume, NULL);
                     //ghostpad for my audio bin
        gst_element_add_pad (this->abin, gst_ghost_pad_new ("src", binpad));
        gst_bin_add_many(GST_BIN(this->vV4L2bin), this->Vlocalsrc, this->conversor1,
                         this->videobalance, NULL);
        gst_element_link_many(this->Vlocalsrc, this->conversor1, NULL);
        gst_element_link_filtered (this->conversor1,this->videobalance ,this->Vcaps);
        gst_element_add_pad (this->vV4L2bin, gst_ghost_pad_new ("src", pad));
        gst_object_unref(binpad);
        gst_object_unref(pad);
        gst_bin_add_many(GST_BIN(pipeline), this->vV4L2bin, conv_before, curr, conv_after, this->sink, this->abin, this->audiosink, NULL);
        gst_element_link_many(this->vV4L2bin,conv_before, curr, conv_after,this->sink,  NULL);
        gst_element_link_many(this->abin, this->audiosink, NULL);
    }
    else
    {
        if(audioSAME==3)//the source is the same for audio and video, share decoder
        {
            qDebug("construyendo pipeline para audio y video misma fuente ================>");
            g_print("seleccionando: %d \n", this->videoBIN);
            switch (this->videoBIN){
            case 1://tcp input source

                blockpad = gst_element_get_static_pad(this->Vtcpsrc, "src");

                gst_bin_add_many(GST_BIN(this->vTCPbin), this->Vtcpsrc, vdecoder, queue1,  this->conversor1,
                                 this->videobalance, NULL);
                gst_element_link_many(this->Vfilesrc, vdecoder, NULL);
                gst_element_link_many(queue1, this->conversor1, NULL);
                gst_element_link_filtered (this->conversor1,this->videobalance ,this->Vcaps);
                gst_element_add_pad (this->vTCPbin, gst_ghost_pad_new ("src", pad));

                gst_bin_add_many(GST_BIN(this->aTCPbin), this->conv, this->audiosampler, this->volume, NULL);
                //adecoder->queue2 linked after, we need a callback and padd-added signal
                gst_element_link_many(this->conv, this->audiosampler, this->volume,  NULL);

                gst_element_add_pad (this->aTCPbin, gst_ghost_pad_new ("src", binpad));

                gst_element_add_pad (this->aTCPbin, gst_ghost_pad_new ("sink", pada));
                //sink pad of the bin for linking it with padd-added callback


                gst_bin_add_many(GST_BIN(pipeline), this->vTCPbin, conv_before, curr, conv_after, this->sink, queue2, this->aTCPbin, this->audiosink, NULL);
                gst_element_link_many(this->vTCPbin,conv_before, curr, conv_after,this->sink,  NULL);
                gst_element_link_many(queue2, this->aTCPbin, this->audiosink, NULL);

                gst_object_unref(binpad);
                gst_object_unref(pad);
                gst_object_unref(pada);


                break;

            case 2:   //file source

                //blockpad = gst_element_get_static_pad(this->Vfilesrc, "src");
                //blocking source pad for video effects
               /* gst_bin_add_many(GST_BIN(this->vFILEbin), this->Vfilesrc, vdecoder, queue1,  this->conversor1,
                                 this->videobalance, NULL);
                gst_element_link_many(this->Vfilesrc, vdecoder, NULL);
                gst_element_link_many(queue1, this->conversor1, NULL);
                gst_element_link_filtered (this->conversor1,this->videobalance ,this->Vcaps);
                gst_element_add_pad (this->vFILEbin, gst_ghost_pad_new ("src", pad));*/

                gst_bin_add_many(GST_BIN(this->aFILEbin), this->conv, this->audiosampler, this->volume, NULL);
                //adecoder->queue2 linked after, we need a callback and padd-added signal
                gst_element_link_many(this->conv, this->audiosampler, this->volume,  NULL);

                gst_element_add_pad (this->aFILEbin, gst_ghost_pad_new ("src", binpad));//source pad of my Audio BIN

                gst_element_add_pad (this->aFILEbin, gst_ghost_pad_new ("sink", pada));//sink pad of my aBIN

                gst_bin_add_many(GST_BIN(pipeline), this->Vfilesrc, vdecoder, queue1,  this->conversor1,
                                 this->videobalance, conv_before, curr, conv_after, this->sink, queue2,
                                 this->aFILEbin, this->audiosink, NULL);
                gst_element_link_many(this->Vfilesrc, vdecoder, NULL); //vdecoder and queue1 will linking in callback function
                gst_element_link_many(queue1, this->conversor1, this->videobalance,conv_before, curr, conv_after,this->sink, NULL);
                //gst_element_link_filtered (this->conversor1,this->videobalance ,this->Vcaps);
                //gst_element_link_many(this->videobalance,conv_before, curr, conv_after,this->sink,  NULL);
                gst_element_link_many(queue2, this->aFILEbin, this->audiosink, NULL);

                gst_object_unref(binpad);
                gst_object_unref(pad);
                gst_object_unref(pada);
                break;
            default:
                gst_bin_add_many(GST_BIN(this->abin), this->Alocalsrc, this->conv, this->volume, NULL);
                gst_element_link_many(this->Alocalsrc, this->conv, this->volume, NULL);
                //ghostpad for my audio bin
                gst_element_add_pad (this->abin, gst_ghost_pad_new ("src", binpad));
                gst_bin_add_many(GST_BIN(this->vV4L2bin), this->Vlocalsrc, this->conversor1,
                                 this->videobalance, NULL);
                gst_element_link_many(this->Vlocalsrc, this->conversor1, NULL);
                gst_element_link_filtered (this->conversor1,this->videobalance ,this->Vcaps);

                gst_element_add_pad (this->vV4L2bin, gst_ghost_pad_new ("src", pad));
                gst_object_unref(binpad);
                gst_object_unref(pad);
                gst_bin_add_many(GST_BIN(pipeline), this->vV4L2bin, conv_before, curr, conv_after, this->sink, this->abin, this->audiosink, NULL);
                gst_element_link_many(this->vV4L2bin,conv_before, curr, conv_after,this->sink,  NULL);
                gst_element_link_many(this->abin, this->audiosink, NULL);

                break;
            }

        }



    }

    //#####################################################################################################################

    window = ui->widget->winId();

    cam_window_handle=window;
    this->bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    gst_bus_set_sync_handler (this->bus, (GstBusSyncHandler) bus_sync_handler, NULL, NULL);
    gst_object_unref (this->bus);

    connect(ui->slider1, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
    connect(ui->slider3, SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
    connect(ui->slider4, SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
    connect(ui->slider5, SIGNAL(valueChanged(int)), this, SLOT(avolume(int)));
    connect(ui->bplay, SIGNAL(clicked()), this, SLOT (start()));
    connect(ui->bstop, SIGNAL(clicked()), this, SLOT(stop()));
    g_signal_connect(vdecoder, "pad-added", G_CALLBACK(videoPad_added_handler), NULL);
    g_signal_connect(adecoder, "pad-added", G_CALLBACK(audioPad_added_handler), NULL);
    //connect(ui->pushButton,SIGNAL(clicked()), this, SLOT() )

    delete input;
}

//destructor
gstvideo::~gstvideo()
{
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
    gst_object_unref(pipeline);
    delete ui;
}


//funcion encargada de sincronizar la solicitud del objeto sink de un widget
// para presentar la imagen de la camara, y le asigno el creado en QT
GstBusSyncReply gstvideo::bus_sync_handler (GstBus *bus, GstMessage *message, gpointer user_data)
{
    if (!gst_is_video_overlay_prepare_window_handle_message (message))
        return GST_BUS_PASS;

    GstVideoOverlay *overlay;
    overlay = GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message));
    gst_video_overlay_set_window_handle (overlay, cam_window_handle);
    gst_message_unref (message);
    return GST_BUS_DROP;
}


//arriba añado los elementos creados en el constructor a la pipeline de gstreamer
//luego los conecto
//obtengo el ID de la ventana creada en qt la cual asignare al ximagesink de gstreamer
//y aseguro de sincronizar el llamado de la ventana a traves de mensajes en el bus de gstreamer

void gstvideo::update_color_channel (gchar *channel_name, gint dvalue, GstColorBalance *cb) {
  GstColorBalanceChannel *channel = NULL;
  const GList *channels, *l;

  /* Retrieve the list of channels and locate the requested one */
  channels = gst_color_balance_list_channels (cb);
  for (l = channels; l != NULL; l = l->next) {
    GstColorBalanceChannel *tmp = (GstColorBalanceChannel *)l->data;

    if (g_strrstr (tmp->label, channel_name)) {
      channel = tmp;
      break;
    }
  }
  if (!channel)return;

    if (dvalue > channel->max_value)
    {
      dvalue = channel->max_value;
      g_print("%d/n", dvalue);
    }
    else {
        if (dvalue < channel->min_value)
            dvalue = channel->min_value;
         }
   gst_color_balance_set_value(cb, channel, dvalue);

}



GstPadProbeReturn gstvideo::block_src(GstPad *pad, GstPadProbeInfo *info, gpointer user_data){

    GstPad *srcpad, *sinkpad;
    //GST_DEBUG_OBJECT(pad, "blocking pad now");
    /*procedo a remover el probe, debido a que instalare un nuevo probe, ademas ya el
     * blockpad esta bloqueado*/

    gst_pad_remove_probe(pad, GST_PAD_PROBE_INFO_ID(info));
    /* install new probe for EOS */
    srcpad = gst_element_get_static_pad (curr, "src");
    gst_pad_add_probe(srcpad, GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM, (GstPadProbeCallback)event_eos, user_data, NULL);
    gst_object_unref (srcpad);

    /* push EOS into the element, the probe will be fired when the
     * EOS leaves the effect and it has thus drained all of its data */

    sinkpad = gst_element_get_static_pad (curr, "sink");
    gst_pad_send_event (sinkpad, gst_event_new_eos ());
    gst_object_unref (sinkpad);

    return GST_PAD_PROBE_OK;
}


GstPadProbeReturn gstvideo::event_eos(GstPad * pad, GstPadProbeInfo * info, gpointer user_data)
{
  GstElement *next;

  if (GST_EVENT_TYPE (GST_PAD_PROBE_INFO_DATA (info)) != GST_EVENT_EOS)
    return GST_PAD_PROBE_OK;
  gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));
  switch (effect){
  case 0:
      next = gst_element_factory_make("identity", "next");
      break;
  case 1:
      next = gst_element_factory_make("dicetv", "next");
      break;
  case 2:
      next = gst_element_factory_make("warptv", "next");
      break;
  case 3:
      next = gst_element_factory_make("shagadelictv", "next");
      break;
  case 4:
      next = gst_element_factory_make("revtv", "next");
      break;
  case 5:
      next = gst_element_factory_make("radioactv", "next");
      break;
  case 6:
      next = gst_element_factory_make("rippletv", "next");
      break;
  case 7:
      next = gst_element_factory_make("frei0r-filter-tehroxx0r", "next");
      break;
  case 8:
      next = gst_element_factory_make("frei0r-filter-cartoon", "next");
      break;
  case 9:
      next = gst_element_factory_make("frei0r-filter-invert0r", "next");
      break;
  case 10:
      next = gst_element_factory_make("frei0r-filter-pixeliz0r", "next");
      break;
  case 11:
      next = gst_element_factory_make("frei0r-filter-nervous", "next");
      break;
  case 12:
      next = gst_element_factory_make("frei0r-filter-vertigo", "next");
      break;
  case 13:
      next = gst_element_factory_make("frei0r-filter-color-distance", "next");
      break;
  case 14:
      next = gst_element_factory_make("frei0r-filter-perspective", "next");
      g_object_set(next, "top-left-x", 0.8, "top-left-Y", 0.01, "top-right-x",0.01, "top-right-Y",0.03490 ,  NULL);
      break;
  case 15:
      next = gst_element_factory_make("frei0r-filter-b", "next");
      break;
  case 16:
      next = gst_element_factory_make("frei0r-filter-baltan", "next");
      break;
  case 17:
      next = gst_element_factory_make("frei0r-filter-twolay0r", "next");
      break;
  case 18:
      next = gst_element_factory_make("frei0r-filter-threelay0r", "next");
      break;
  case 19:
      next = gst_element_factory_make("frei0r-filter-bw0r", "next");
      break;
  case 20:
      next = gst_element_factory_make("frei0r-filter-sobel", "next");
      break;
  case 21:
      next = gst_element_factory_make("frei0r-filter-distort0r", "next");
      break;
  default:
      next = gst_element_factory_make("identity", "next");
      break;
    }



  if(next==NULL){
      g_print("%s \n","error, no se puedo crear el elemento");
      g_print("%s \n","setting default effect: identity");
      next = gst_element_factory_make("identity", "next");
  }

  gst_element_set_state (curr, GST_STATE_NULL);

  gst_bin_remove (GST_BIN (pipeline), curr);
  gst_bin_add (GST_BIN (pipeline), next);
  gst_element_link_many (conv_before, next, conv_after, NULL);
  gst_element_set_state (next, GST_STATE_PLAYING);

  curr = next;
  GST_DEBUG_OBJECT (pipeline, "done");

  return GST_PAD_PROBE_DROP;
}




//################################## DINAMIC CALLBACK for vdecoder ########################################################

/* This function will be called by the pad-added signal */
void gstvideo::videoPad_added_handler(GstElement *src, GstPad *new_pad, gpointer user_data) {
    g_print("entering into padd-added video function: ");
  GstPad *sink_pad = gst_element_get_static_pad (queue2, "sink"); // pad for audio pipeline, the same data source
  GstPad *sink_pad_video = gst_element_get_static_pad(queue1, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("  We are already linked. Ignoring.\n");
    goto exit;
  }

  /*inicialmente habia puesto otro bloque if para verificar si el sink_pad_video ya habia sido
   * linkeado, esto no funcionaba ya que hacia link para audio pero no para video,
   * al quitarlo, todo funciono perfectamente*/

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_current_caps(new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  g_print("audioSAME is: %d  \n", audioSAME);

  if ((g_str_has_prefix (new_pad_type, "audio/x-raw")) && (audioSAME == 3) ) {

    /* Attempt the link */
    ret = gst_pad_link (new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
      g_print ("  Type is '%s' but link failed.\n", new_pad_type);
    } else {
      g_print ("  Link succeeded (type '%s').\n", new_pad_type);
    }

  } else if (g_str_has_prefix (new_pad_type, "video/x-raw")) {
     /* Attempt the link */
    blockpad = new_pad; // source pad to blocking in effects call back
    ret = gst_pad_link (new_pad, sink_pad_video);
    if (GST_PAD_LINK_FAILED (ret)) {
      g_print ("  Type is '%s' but link failed.\n", new_pad_type);
    } else {
      g_print ("  Link succeeded (type '%s').\n", new_pad_type);
    }
  } else {
    g_print ("  It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
    goto exit;
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
  gst_object_unref (sink_pad_video);
}


//##########################################################################################################################


//###########################################3 CALLBACK for adecoder #######################################################

void gstvideo::audioPad_added_handler (GstElement *src, GstPad *new_pad, gpointer user_data){
  GstPad *sink_pad = gst_element_get_static_pad (queue2, "sink");
  //GstPad *sink_pad_video = gst_element_get_static_pad (data->video_convert, "sink");
  GstPadLinkReturn ret;
  GstCaps *new_pad_caps = NULL;
  GstStructure *new_pad_struct = NULL;
  const gchar *new_pad_type = NULL;

  g_print ("Received new pad '%s' from '%s':\n", GST_PAD_NAME (new_pad), GST_ELEMENT_NAME (src));

  /* If our converter is already linked, we have nothing to do here */
  if (gst_pad_is_linked (sink_pad)) {
    g_print ("  We are already linked. Ignoring.\n");
    goto exit;
  }

  /* Check the new pad's type */
  new_pad_caps = gst_pad_get_current_caps(new_pad);
  new_pad_struct = gst_caps_get_structure (new_pad_caps, 0);
  new_pad_type = gst_structure_get_name (new_pad_struct);
  if (g_str_has_prefix (new_pad_type, "audio/x-raw")) {

    /* Attempt the link */
    ret = gst_pad_link (new_pad, sink_pad);
    if (GST_PAD_LINK_FAILED (ret)) {
      g_print ("  Type is '%s' but link failed.\n", new_pad_type);
    } else {
      g_print ("  Link succeeded (type '%s').\n", new_pad_type);
    }

  }
  else {
    g_print ("  It has type '%s' which is not raw audio. Ignoring.\n", new_pad_type);
    goto exit;
  }

exit:
  /* Unreference the new pad's caps, if we got them */
  if (new_pad_caps != NULL)
    gst_caps_unref (new_pad_caps);

  /* Unreference the sink pad */
  gst_object_unref (sink_pad);
}

//##########################################################################################################################





// ##################################### SLOTS #############################################################################

void gstvideo::start()
{
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void gstvideo::stop()
{
    if (pipeline != NULL)
    {
        gst_element_set_state (pipeline, GST_STATE_NULL);
        //g_object_unref(pipeline);
    }
}

void gstvideo::contrast(int c){
    //g_print("%d/n", x);
    c = c*10;
    this->update_color_channel("CONTRAST", c, GST_COLOR_BALANCE(this->videobalance));
}

void gstvideo::brightness(int b){
    b = b*10;
    this->update_color_channel("BRIGHTNESS", b, GST_COLOR_BALANCE(this->videobalance));
}

void gstvideo::hue(int h){
    h = h*10;
    this->update_color_channel("HUE", h, GST_COLOR_BALANCE(this->videobalance));
}

void gstvideo::saturation(int s){
    s = s*10;
    this->update_color_channel("SATURATION", s, GST_COLOR_BALANCE(this->videobalance));
}


void gstvideo::on_comboBox_currentIndexChanged(int index)
{
    effect=ui->comboBox->currentIndex();
    gst_pad_add_probe(blockpad, GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, (GstPadProbeCallback)block_src, this->loop, NULL);
    //GstPadProbeReturn gstvideo::event_eos(GstPad * pad, GstPadProbeInfo * info, gpointer user_data)
}

void gstvideo::avolume(int y){
    gdouble x = y/10.0;
    g_print("%d \n", x);
    gst_stream_volume_set_volume (GST_STREAM_VOLUME(this->volume), GST_STREAM_VOLUME_FORMAT_LINEAR, x);
}


