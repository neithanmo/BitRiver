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
    ui->slider1->setRange(0,100);
    ui->slider2->setRange(0,100);
    ui->slider3->setRange(0,100);
    ui->slider4->setRange(0,100);
    ui->slider1->setValue(0);
    ui->slider2->setValue(0);
    ui->slider3->setValue(0);
    ui->slider4->setValue(0);
    ui->progressBar1->setValue(0);
    ui->progressBar1->setRange(0,100);
    ui->progressBar2->setValue(0);
    ui->progressBar2->setRange(0,100);
    ui->progressBar3->setValue(0);
    ui->progressBar3->setRange(0,100);
    ui->progressBar4->setValue(0);
    ui->progressBar4->setRange(0,100);
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


void gstvideo::start()
{
    this->configure();//antes de poper la pipeline a playing state, debo de añadir lo elementos a esta
    //vigilar el bus, etc etc
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void gstvideo::stop()
{
    if (this->pipeline != NULL)
    {
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
    }
}
