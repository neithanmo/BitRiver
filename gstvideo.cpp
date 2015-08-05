#include "gstvideo.h"
#include "ui_gstvideo.h"

guintptr gstvideo::cam_window_handle;

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
    ui->progressBar1->setValue(0);
    ui->progressBar1->setRange(-100,100);//muestra el valor actual del contraste
    ui->progressBar2->setValue(0);
    ui->progressBar2->setRange(-100,100);//valor del brillo
    ui->progressBar3->setValue(0);
    ui->progressBar3->setRange(-100,100);//valor de la saturacion
    ui->progressBar4->setValue(0);
    ui->progressBar4->setRange(-100,100);//valor del HUE
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
    this->pipeline = gst_pipeline_new("pipeline");
    this->caps = gst_caps_new_simple("video/x-raw",
                   "width", G_TYPE_INT, 640,
                   "height", G_TYPE_INT, 480,
                    NULL);

    //se crearon todos los elementos ????

    if (!this->src || !this->sink || !this->conversor1 || !this->pipeline || !this->videobalance){
        qDebug("no se crearon todos los elementos necesarios");
        return;
    }

    connect(ui->slider1, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
    connect(ui->slider3, SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
    connect(ui->slider4, SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
    connect(ui->bplay, SIGNAL(clicked()), this, SLOT (start()));
    connect(ui->bstop, SIGNAL(clicked()), this, SLOT(stop()));
}

//destructor
gstvideo::~gstvideo()
{
    gst_element_set_state(GST_ELEMENT(this->pipeline), GST_STATE_NULL);
    gst_object_unref(this->pipeline);
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
    g_print("solicitando ventana");

    gst_message_unref (message);
    return GST_BUS_DROP;
}


//aqui añado los elementos creados en el constructor a la pipeline de gstreamer
//luego los conecto
//obtengo el ID de la ventana creada en qt la cual asignare al ximagesink de gstreamer
//y aseguro de sincronizar el llamado de la ventana a traves de mensajes en el bus de gstreamer

void gstvideo::configure()
{

    gst_bin_add_many(GST_BIN(this->pipeline), this->src, this->conversor1, this->videobalance, this->sink, NULL);
    gst_element_link_filtered (this->conversor1,this->videobalance ,this->caps);
    gst_element_link_many(this->src, this->conversor1,NULL);
    gst_element_link_many(this->videobalance, this->sink,NULL);
    window = ui->widget->winId();
    cam_window_handle=window;
    this->bus = gst_pipeline_get_bus (GST_PIPELINE (this->pipeline));
    gst_bus_set_sync_handler (this->bus, (GstBusSyncHandler) bus_sync_handler, NULL, NULL);
    gst_object_unref (this->bus);

}

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
   g_print("%d\n", dvalue);
   g_print("%s", "maxValue");
   g_print("%d\n", channel->max_value);
   g_print("%s", "minValue");
   g_print("%d\n", channel->min_value);

}

// ##################################### SLOTS #############################################################################

void gstvideo::start()
{
    this->configure();//antes de poner la pipeline a playing state, debo de añadir lo elementos a esta
    //vigilar el bus, etc etc
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void gstvideo::stop()
{
    if (this->pipeline != NULL)
    {
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
        g_object_unref(this->pipeline);
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
