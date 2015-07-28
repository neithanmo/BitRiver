#include "gstvideo.h"
#include "ui_gstvideo.h"

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
    connect(ui->bplay, SIGNAL(clicked()), this, SLOT (start()));
    connect(ui->bstop, SIGNAL(clicked()), this, SLOT(stop()));


}

gstvideo::~gstvideo()
{
    gst_element_set_state(GST_ELEMENT(this->pipeline), GST_STATE_NULL);
    gst_object_unref(this->pipeline);
    delete ui;
}


//static GstBusSyncReply bus_callback (GstBus *bus, GstMessage *message, gpointer user_data)
//{
//    if (GST_MESSAGE_TYPE (message) != GST_MESSAGE_ELEMENT)
//        return GST_BUS_PASS;

//    if (!gst_message_has_name (message, "prepare-window-handle"))
//        return GST_BUS_PASS;

//    qDebug("Got message of type %s from %s", GST_MESSAGE_TYPE_NAME(message),
//           GST_ELEMENT_NAME (GST_MESSAGE_SRC (message)));
//    gstvideo *window = (gstvideo*)user_data;
//    WId win = window->ui->widget->winId();
//    if(win != 0)
//    {
//        gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY (message->src), win);
//    }
//    gst_message_unref (message);

//    return GST_BUS_DROP;
//}



void gstvideo::configure()
{
    gst_init(NULL, NULL);
    loop = g_main_loop_new (NULL, FALSE);

    // Elements
    this->src = gst_element_factory_make("videotestsrc", "src");
    this->conversor1 = gst_element_factory_make("videoconvert", "conversor1");
    this->sink = gst_element_factory_make("ximagesink", "sink");
    this->videobalance = gst_element_factory_make("videobalance", "balance");
    this->pipeline = gst_pipeline_new("pipeline");

    //se crearon todos los elementos ????

    if (!this->src || !this->sink || !this->conversor1 || !this->pipeline || !this->videobalance){
        qDebug("no se crearon todos los elementos necesarios");
        return;
    }
    gst_bin_add_many(GST_BIN(this->pipeline), this->src, this->conversor1, this->videobalance, this->sink, NULL);
    if(!gst_element_link_many(this->src, this->conversor1, this->videobalance, this->sink, NULL))
    {
        qDebug("error, no se pudo hacer link sobre todos los elementos");
        return;
    }
    window = ui->widget->winId();
    ui->widget->show();

    //this->bus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    //gst_bus_set_sync_handler (this->bus, bus_callback, this, NULL);

    gst_video_overlay_set_window_handle(GST_VIDEO_OVERLAY (this->sink), window);
    gst_element_set_state (this->pipeline, GST_STATE_READY);

}


void gstvideo::start()
{
    gst_element_set_state (pipeline, GST_STATE_PLAYING);
}

void gstvideo::stop()
{
    if (this->pipeline != NULL)
    {
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
    }
}
