#include "gstvideo.h"
#include "ui_gstvideo.h"

guintptr gstvideo::cam_window_handle;

static GstElement *pipeline; //= gst_pipeline_new("pipeline");
static GstElement *curr ;//= gst_element_factory_make("identity", "curr"); //current efect
static GstPad *blockpad; //source pad de mi fuente, en este caso v4l2src
static GstElement *conv_before;// = gst_element_factory_make("videoconvert", "conv_after");
static GstElement *conv_after;// = gst_element_factory_make("videoconvert", "conv_after");
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

    //WId window = ui->widget->winId();
    ui->widget->setFixedWidth(640);
    ui->widget->setFixedHeight(480);
    gst_init(NULL, FALSE);
    this->src = gst_element_factory_make("v4l2src", "src");
    this->conversor1 = gst_element_factory_make("videoconvert", "conversor1");
    this->sink = gst_element_factory_make("ximagesink", "sink");
    this->videobalance = gst_element_factory_make("videobalance", "balance");
    this->audiosink = gst_element_factory_make("autoaudiosink", "ausink");
    pipeline = gst_pipeline_new("pipeline");
    this->caps = gst_caps_new_simple("video/x-raw",
                   "width", G_TYPE_INT, 640,
                   "height", G_TYPE_INT, 480,
                    NULL);
    blockpad = gst_element_get_static_pad(this->src, "src");
    conv_after = gst_element_factory_make("videoconvert", "conv_after");
    conv_before = gst_element_factory_make("videoconvert", "conv_before");
    curr = gst_element_factory_make("identity", "curr");
    //se crearon todos los elementos ????

    if (!this->src || !this->sink || !this->conversor1 || !pipeline || !this->videobalance || !conv_before || !curr || !conv_after){
        qDebug("no se crearon todos los elementos necesarios");
        return;
    }

    gst_bin_add_many(GST_BIN(pipeline), this->src, this->conversor1, this->videobalance, conv_before,
                     curr, conv_after, this->sink,NULL);
    gst_element_link_filtered (this->conversor1,this->videobalance ,this->caps);
    gst_element_link_many(this->src, this->conversor1,NULL);
    gst_element_link_many(this->videobalance,conv_before, curr, conv_after, this->sink,NULL);
    window = ui->widget->winId();
    cam_window_handle=window;
    this->bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
    gst_bus_set_sync_handler (this->bus, (GstBusSyncHandler) bus_sync_handler, NULL, NULL);
    gst_object_unref (this->bus);

    connect(ui->slider1, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
    connect(ui->slider3, SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
    connect(ui->slider4, SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
    connect(ui->slider5, SIGNAL(valueChanged(int)), this, SLOT(volume(int)));
    connect(ui->bplay, SIGNAL(clicked()), this, SLOT (start()));
    connect(ui->bstop, SIGNAL(clicked()), this, SLOT(stop()));
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
    g_print("solicitando ventana /n");

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
    GST_DEBUG_OBJECT(pad, "blocking pad now");

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
      g_print("%s","error, no se puedo crear el elemento /n");
      g_print("%s","setting default effect: identity /n");
      next = gst_element_factory_make("identity", "next");
  }

  gst_element_set_state (curr, GST_STATE_NULL);

  /* remove unlinks automatically */
  gst_bin_remove (GST_BIN (pipeline), curr);
  gst_bin_add (GST_BIN (pipeline), next);
  gst_element_link_many (conv_before, next, conv_after, NULL);

  gst_element_set_state (next, GST_STATE_PLAYING);

  curr = next;
  GST_DEBUG_OBJECT (pipeline, "done");

  return GST_PAD_PROBE_DROP;
}


// ##################################### SLOTS #############################################################################

void gstvideo::start()
{

    gst_element_set_state (pipeline, GST_STATE_PLAYING);
    audio->start();
}

void gstvideo::stop()
{
    if (pipeline != NULL)
    {
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
        //g_object_unref(pipeline);
    }
    audio->pause();
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
}

void gstvideo::volume(int y){
    audio->avolume(y);
}

void gstvideo::on_lineEdit_editingFinished()
{

}
