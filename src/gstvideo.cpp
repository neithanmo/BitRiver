#include "gstvideo.h"

guintptr gstvideo::cam_window_handle;
static int effect = 0;
static GstPad *blockpad;
static GstElement *pipeline;

gstvideo::gstvideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gstvideo){

    ui->setupUi(this);
    ui->slider1->setRange(-100,100);//contrast 0 -> 2. default=1
    this->setWindowTitle("BitRiver");
    ui->slider1->setTickPosition(QSlider::TicksAbove);
    ui->slider2->setRange(-100,100);//brightness    -1 -> 1. default=0
    ui->slider2->setTickPosition(QSlider::TicksAbove);
    ui->slider3->setRange(-100,100);//saturation 0 -> 2. default=1
    ui->slider3->setTickPosition(QSlider::TicksAbove);
    ui->slider4->setRange(-100,100);//hue       -1 -> 1. default=0
    ui->slider4->setTickPosition(QSlider::TicksAbove);
    ui->slider1->setValue(0);
    ui->slider2->setValue(0);
    ui->slider3->setValue(0);
    ui->slider4->setValue(0);
    ui->slider5->setRange(0,10);
    ui->slider5->setTickPosition(QSlider::TicksAbove);
    ui->progressBar1->setValue(0);
    ui->progressBar1->setRange(-100,100);
    ui->progressBar2->setValue(0);
    ui->progressBar2->setRange(-100,100);
    ui->progressBar3->setValue(0);
    ui->progressBar3->setRange(-100,100);
    ui->progressBar4->setValue(0);
    ui->progressBar4->setRange(-100,100);
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

    input->exec();
    gst_init(NULL, FALSE);
    ui->widget->setFixedWidth(661);
    ui->widget->setFixedHeight(411);
    ui->bplay->hide();
    ui->videoList->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->audioList->setContextMenuPolicy(Qt::CustomContextMenu);
    g_print("video Resolution: \t%dx%d \n", input->resolutionX, input->resolutionY);
    g_print("audio rate is: \t%d; \t audio bitrate is: %d \n", input->arate, input->abrate);
    g_print("video settings \tframerate: %d \tvideo bitrate: %d \n",input->framerate, input->vbrate);
    g_print("audio channels is: \t%d \n", input->channels);

    //####################### Creating Elements ###################################################################

    conversor1 = gst_element_factory_make("videoconvert", "conversor1");
    defaultcamera = gst_element_factory_make("v4l2src", "localcamera");
    x264enc = gst_element_factory_make("x264enc","x264enc");
    h264parse = gst_element_factory_make("h264parse","h264parse");
    avdec_h264 = gst_element_factory_make("avdec_h264","avdec_h264");
    sink = gst_element_factory_make("ximagesink", "sink");
    videobalance = gst_element_factory_make("videobalance", "balance");
    curr = gst_element_factory_make("identity", "curr");
    conv_after = gst_element_factory_make("videoconvert", "conv_after");
    conv_before = gst_element_factory_make("videoconvert", "conv_before");
    videosinkconvert = gst_element_factory_make("videoconvert", "vsinkconvert");
    Svideoconvert = gst_element_factory_make("videoscale", "sconvert");
    videoscale = gst_element_factory_make("videoscale", "videoscale");
    Vscale = gst_element_factory_make("videoscale", "Vscale");
    this->Sscale = gst_element_factory_make("videoscale","Sscale");
    videoSelector = gst_element_factory_make("input-selector", "videoSelect");// its for select any video source from
    if (!x264enc || !h264parse || !videobalance
             || !conversor1 || !conv_before || !curr || !conv_after || !videosinkconvert || !Vscale || !Sscale){
        qDebug("any video or encoding element not found");
        return;
    }

    Adefault = gst_element_factory_make("alsasrc","localAudio");
    conv = gst_element_factory_make("audioconvert","aconv");
    volume = gst_element_factory_make("volume","volume");
    audiosink = gst_element_factory_make("autoaudiosink", "ausink");
    faac = gst_element_factory_make("faac","aacAudioencoder");
    aacparse = gst_element_factory_make("aacparse", "aacparse");
    audiosampler = gst_element_factory_make("audioresample", "audiosampler");
    audiorate = gst_element_factory_make("audiorate", "audiorate");
    audioparse = gst_element_factory_make("audioparse", "audiopar");
    audiomixer = gst_element_factory_make("audiomixer","audiomixer");
    if(audiomixer == NULL)
        exit(-2);
    if (!conv || !volume || !audiosampler || !faac || !aacparse || !audiosink
            || !audiorate || !audioparse || !audiomixer){
        qDebug("any audio element not found");
        return;
    }

    queue1 = gst_element_factory_make("queue", "queue1");
    queue2 = gst_element_factory_make("queue", "queue2");
    queue3 = gst_element_factory_make("queue", "queue3");
    queue4 = gst_element_factory_make("queue", "queue4");
    queue5 = gst_element_factory_make("queue", "queue5");
    queue6 = gst_element_factory_make("queue", "queue6");
    queue7 = gst_element_factory_make("queue", "queue7");
    queue8 = gst_element_factory_make("queue", "queue8");
    queue9 = gst_element_factory_make("queue", "queue9");
    vselqueue = gst_element_factory_make("queue", "vsel");
    aselqueue = gst_element_factory_make("queue", "asel");
    Ltee2 = gst_element_factory_make("tee","tee2");//audio branch tee for visualization
    Ltee1 = gst_element_factory_make("tee","tee1");//video branch tee for visualization
    scale = gst_element_factory_make("videoscale","scale");//for video streaming settings
    pipeline = gst_pipeline_new("pipeline");
    rtmp = gst_element_factory_make("fakesink","rtmp");
    flvmux = gst_element_factory_make("flvmux","flvmux");

    in_sel_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (videoSelector), "sink_%u"); //Pads template of
    mix_template = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (audiomixer), "sink_%u");//videoselectro and audiomixer
    gst_debug_set_active (true);

    if (!pipeline ){
        qDebug("pipeline not created");
        return;
    }

    //###########################################################################################################################
    int keyint = 2*input->framerate;
    QString location = "rtmp://a.rtmp.youtube.com/live2/x/" + input->youtube + "?videoKeyframeFrequency=1&totalDatarate=8128 app=live2 flashVer=FME/3.0%20(compatible;%20FMSc%201.0) swfUrl=rtmp://a.rtmp.youtube.com/live2";

    g_object_set(rtmp, "location", location.toUtf8().constData(), "sync", TRUE, NULL);
    g_object_set(volume, "volume", 1.0, NULL);
    g_object_set(faac, "bitrate", input->abrate, NULL);
    g_object_set(this->x264enc, "bitrate", input->vbrate, "key-int-max", keyint, "bframes", 0,
                 "byte-stream",false,"speed-preset", 1, "aud", true,"psy-tune",1,NULL);
    g_object_set(sink, "sync", TRUE, NULL);
    g_object_set(audiosink, "sync", TRUE, NULL);
    g_object_set(audioparse, "rate", input->arate, "channels", input->channels, NULL);
    g_object_set(flvmux, "streamable", TRUE, NULL);

    Vcaps = gst_caps_from_string("video/x-raw, format=I420");
    Scaps = gst_caps_new_simple("video/x-raw",
                                      "interlace-mode", G_TYPE_STRING, "progressive",
                                      "format", G_TYPE_STRING, "I420",
                                      "width", G_TYPE_INT, input->resolutionX,
                                      "height", G_TYPE_INT, input->resolutionY,
                                       NULL);
    Acaps = gst_caps_from_string("audio/x-raw, format=S16LE, layout=interleaved, rate=44100, channels=2");
    enVcaps = gst_caps_new_simple("video/x-h264",
                   "level", G_TYPE_STRING, "4.1",
                   "profile", G_TYPE_STRING, "main",
                   NULL);

    enAcaps = gst_caps_new_simple("audio/mpeg",
                   "mpegversion", G_TYPE_INT, 4,
                   "stream-format", G_TYPE_STRING, "raw",
                    NULL);

    //####################################################################################################################################
   //g_object_set(videoSelector, "sync-streams", true, "sync-mode", 0,NULL);
   //sy sync-mode != 0, el pad-probe en datasrc, se activa solo una vez.. curioso
    //g_object_set(videoSelector, "sync-streams", false, NULL);
     //g_object_set(audiomixer, "start-time-selection" ,1,"caps", Acaps, NULL);
     //g_object_set(videoSelector, "start-time-selection" , 1, NULL);
    //binpad = gst_element_get_static_pad(this->volume, "src");
    //GstPad *pad = gst_element_get_static_pad(this->videobalance, "src");

    window = ui->widget->winId();
    cam_window_handle=window;

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

    gst_bus_set_sync_handler (this->bus, (GstBusSyncHandler) bus_sync_handler, this, NULL);
    gst_object_unref (this->bus);

    GstBus *mbus = gst_pipeline_get_bus(GST_PIPELINE(pipeline));
    gst_bus_add_signal_watch(mbus);


    connect(ui->slider1, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
    connect(ui->slider3, SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
    connect(ui->slider4, SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
    connect(ui->slider5, SIGNAL(valueChanged(int)), this, SLOT(avolume(int)));
    connect(ui->bplay, SIGNAL(clicked()), this, SLOT (start()));
    connect(ui->bstop, SIGNAL(clicked()), this, SLOT(stop()));
    connect(ui->videoList, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(on_videoList_customContextMenuRequested(const QPoint &)));
    connect(ui->audioList, SIGNAL(customContextMenuRequested(const QPoint &)), this,
            SLOT(on_audioList_customContextMenuRequested(const QPoint &)));

    configure();

    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    g_signal_connect(mbus, "message::error", G_CALLBACK(callback), this);


    delete input;
}


gstvideo::~gstvideo(){
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
    g_main_loop_unref(loop);
    gst_object_unref(pipeline);
    delete ui;
    delete source;
}

void gstvideo::configure(){

    g_print("configuring the pipeline \n");
    QString videoDevice="/dev/"+input->localCamera;
    QString audioDevice = "plughw:"+input->localAudioCard;
    qDebug()<<"the sound card is " << audioDevice;
    qDebug()<<"video device is " << videoDevice;
    g_object_set(defaultcamera, "do-timestamp", TRUE, "device", "/dev/video0","name",
                 videoDevice.toUtf8().constData(), NULL);
    g_object_set(Adefault, "do-timestamp", TRUE, "device", "plughw:Generic",
                 "name", audioDevice.toUtf8().constData(), "provide-clock", false, NULL);
    blockpad = gst_element_get_static_pad(conversor1,"src");

    gst_bin_add_many(GST_BIN(pipeline), defaultcamera, videoSelector, queue1, this->scale, this->conversor1,
                                                 this->videobalance, conv_before, curr, conv_after,this->Ltee1,
                                                 queue7, this->Svideoconvert,this->x264enc,this->h264parse,
                                                 queue3, this->flvmux, queue4,
                                                 this->rtmp,
                                                 Adefault,audiomixer,this->conv, this->audiosampler, this->volume, this->Ltee2,
                                                 queue9, this->faac, this->aacparse, queue5,
                                                 queue8, this->audiosink,
                                                 queue6, this->videosinkconvert, this->sink, NULL);
    GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
    GstPad *a_pad = gst_element_get_static_pad(this->Adefault, "src");
    if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
             g_critical ("link audio source to audiomixer failed.\n");
             exit(1);
     }
    gchar * name = gst_pad_get_name(mixer_pad);
    this->mixerPads.push_back(name);//##################################################################
    ui->audioList->addItem(audioDevice);
    volPad = gst_element_get_static_pad (audiomixer, "sink0"); //default volume pad
    gdouble current_volume;
    ui->slider5->setValue(int(current_volume));
    GstPad *in_sel = gst_element_request_pad (videoSelector, in_sel_template, NULL, NULL);//link default camera to videoSelector
    GstPad *lo_pad = gst_element_get_static_pad(this->defaultcamera, "src");
    if (gst_pad_link (lo_pad, in_sel) != GST_PAD_LINK_OK ){
             g_critical ("object to input-selector failed.\n");
             exit(1);
     }
    name = gst_pad_get_name(in_sel);
    this->selectorPads.push_back(name);//##################################################################
    ui->videoList->addItem(videoDevice);

    gst_element_link_many(videoSelector, queue1, this->scale, this->conversor1, NULL);
    gst_element_link_many(this->videobalance,
                          conv_before, curr, conv_after,this->Ltee1, NULL);
    gst_element_link_filtered(this->conversor1, this->videobalance, this->Scaps);
    gst_element_link(queue7,this->Svideoconvert);
    gst_element_link_filtered (this->Svideoconvert, this->x264enc ,this->Vcaps);
    gst_element_link_many(queue6, this->videosinkconvert, this->sink,NULL);
    gst_element_link_many(this->x264enc, this->h264parse, queue3, NULL);
    gst_element_link_many(this->flvmux, queue4, this->rtmp, NULL);

    //*********************************audio elements ************************************************************

    gst_element_link_many(audiomixer, this->conv, this->audiosampler, NULL);
    gst_element_link_filtered(audiosampler, volume, Acaps);
    gst_element_link(volume, Ltee2);
    gst_element_link_many(queue8, this->audiosink, NULL);
    gst_element_link_many(queue9, this->faac, this->aacparse, NULL);
    gst_element_link(this->aacparse, queue5);
    GstPadTemplate *tee_src_pad_template1, *tee_src_pad_template2;
    GstPad *tee1_q6_pad, *tee1_q7_pad,*tee2_q8_pad, *tee2_q9_pad;
    GstPad *q6_pad, *q7_pad, *q8_pad, *q9_pad;
    if ( !(tee_src_pad_template1 = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (this->Ltee1), "src_%u"))) {
        gst_object_unref (pipeline);
        g_critical ("Unable to get pad template");
    }

    if ( !(tee_src_pad_template2 = gst_element_class_get_pad_template (GST_ELEMENT_GET_CLASS (this->Ltee2), "src_%u"))) {
        gst_object_unref (pipeline);
        g_critical ("Unable to get pad template");
    }

    tee1_q7_pad = gst_element_request_pad (this->Ltee1, tee_src_pad_template1, NULL, NULL);

    q7_pad = gst_element_get_static_pad (queue7, "sink");
    /* Link the tee to the queue 7 */
    if (gst_pad_link (tee1_q7_pad, q7_pad) != GST_PAD_LINK_OK ){ // t2 ----> queue7
        g_critical ("Tee1 for queue7 could not be linked.\n");
        gst_object_unref (pipeline);
        exit(1);
    }
    tee2_q9_pad = gst_element_request_pad (this->Ltee2, tee_src_pad_template2, NULL, NULL);
    q9_pad = gst_element_get_static_pad (queue9, "sink");
    /* Link the tee to the queue 7 */
    if (gst_pad_link (tee2_q9_pad, q9_pad) != GST_PAD_LINK_OK ){
        g_critical ("Tee2 for queue9 could not be linked.\n");
        gst_object_unref (pipeline);
        exit(1);
    }

    tee1_q6_pad = gst_element_request_pad (this->Ltee1, tee_src_pad_template1, NULL, NULL);
    q6_pad = gst_element_get_static_pad(queue6, "sink");
    /* Link the tee to the queue 6 */
    if (gst_pad_link(tee1_q6_pad, q6_pad) != GST_PAD_LINK_OK ){ //  t1 ----> queue6
        g_critical ("Tee1 for queue6 could not be linked.\n");
        gst_object_unref (pipeline);
        exit(1);
    }

    /* Obtaining request pads for the tee1 elements*/
    tee2_q8_pad = gst_element_request_pad (this->Ltee2, tee_src_pad_template2, NULL, NULL);
    q8_pad = gst_element_get_static_pad (queue8, "sink");
    /* Link the tee to the queue 6 */
    if (gst_pad_link (tee2_q8_pad, q8_pad) != GST_PAD_LINK_OK ){
        g_critical ("Tee2 for queue8 could not be linked.\n");
        gst_object_unref (pipeline);
        exit(1);
    }

    GstPadTemplate *flvmux_sink_pad_template_audio;
    if (!(flvmux_sink_pad_template_audio = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(this->flvmux), "audio"))) {
        gst_object_unref (pipeline);
        printf ("Unable to get pad template for audio for flvmux element");
        exit(1);
    }

    GstPad * audio_queue5_src_pad = gst_element_get_static_pad(queue5, "src");
    GstPad * flvmux_sink_audio_pad = gst_element_request_pad(flvmux, flvmux_sink_pad_template_audio, NULL, NULL);
    if (gst_pad_link (audio_queue5_src_pad, flvmux_sink_audio_pad) != GST_PAD_LINK_OK ) {
        printf("unable to link audio queue with flvmixer\n");
        exit(1);
    }

    GstPadTemplate *flvmux_sink_pad_template_video;
    if (!(flvmux_sink_pad_template_video = gst_element_class_get_pad_template(GST_ELEMENT_GET_CLASS(this->flvmux), "video"))) {
        gst_object_unref (pipeline);
        printf ("Unable to get pad template for video for flvmux element");
        exit(1);
    }

    GstPad * video_queue3_src_pad = gst_element_get_static_pad(queue3, "src");
    GstPad * flvmux_sink_video_pad = gst_element_request_pad(this->flvmux, flvmux_sink_pad_template_video, NULL, NULL);
    gst_pad_link(video_queue3_src_pad, flvmux_sink_video_pad);

    gst_object_unref(audio_queue5_src_pad);
    gst_object_unref(video_queue3_src_pad);
    gst_object_unref (q6_pad);
    gst_object_unref(q7_pad);
    gst_object_unref (q8_pad);
    gst_object_unref(q9_pad);
    gst_object_unref(tee_src_pad_template1);
    gst_object_unref(tee_src_pad_template2);
}

void gstvideo::addSource(){
    newSource *add = new newSource;
    add->exec();
    switch(add->sourcetype) {
    case 0:{
        QString videoDevice="/dev/"+add->device;
        dsrc.push_back(new Datasrc(0, videoDevice));
        source = dsrc.back();
        g_object_set(source->src, "do-timestamp", TRUE, "device", videoDevice.toUtf8().constData(), NULL);//???
        gst_bin_add(GST_BIN(pipeline), source->get_bin());
        GstPad *in_sel = gst_element_request_pad (videoSelector, in_sel_template, NULL, NULL);
        GstPad *lo_pad = gst_element_get_static_pad(source->get_bin(), "videosrc");
        if (gst_pad_link (lo_pad, in_sel) != GST_PAD_LINK_OK ){
                 g_critical ("object to input-selector failed.\n");
                 exit(1);
         }
        gchar *name = gst_pad_get_name(in_sel);
        this->selectorPads.push_back(name);
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        g_object_unref(in_sel);
        g_object_unref(lo_pad);
        ui->videoList->addItem(add->sourceName);
        g_print("New source: %s\n", source->srcname->toUtf8().constData());

    }
        break;
    case 1:{
        QString dev = "alsasrc";
        QString audioDevice = "plughw:"+add->device;
        dsrc.push_back(new Datasrc(1, audioDevice));
        source = dsrc.back();
        //g_object_set(source->src, "do-timestamp", TRUE, "device", audioDevice.toUtf8().constData(), NULL);
        gst_bin_add(GST_BIN(pipeline), source->get_bin());
        GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
        GstPad *a_pad = gst_element_get_static_pad(source->get_bin(), "audiosrc");
        if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
                 g_critical ("link audio source to audiomixer failed.\n");
                 exit(1);
         }
        gchar *name = gst_pad_get_name(mixer_pad);
        this->mixerPads.push_back(name);
        g_object_unref(mixer_pad);
        g_object_unref(a_pad);
        gst_element_set_state(source->databin, GST_STATE_PLAYING);
        g_print("New source: %s\n", GST_ELEMENT_NAME(source->get_bin()));
        ui->audioList->addItem(audioDevice);

    }
        break;
    case 2:{  //file audio and video src
        bool loop = true;

        source = new Datasrc(add->sourcefilePath, add->sourceName, loop);
        dsrc.push_back(source);
        g_signal_connect(source->decoder, "pad-added",
                            G_CALLBACK(source->pad_added), dsrc.back());
        gst_bin_add(GST_BIN(pipeline), source->get_bin());
        //::::::::::::::::::: Video ::::::::::::::::::::::::::::::::::::::::::
        GstPad *in_sel = gst_element_request_pad (videoSelector, in_sel_template, NULL, NULL);
        GstPad *lo_pad = gst_element_get_static_pad(source->get_bin(), "videosrc");
        if (gst_pad_link (lo_pad, in_sel) != GST_PAD_LINK_OK ){
                 g_critical ("object to input-selector failed.\n");
                 exit(1);
         }
        gchar *name = gst_pad_get_name(in_sel);
        this->selectorPads.push_back(name);

        //:::::::::::::::::::Audio ::::::::::::::::::::::::::::::::::::::::::::
        GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
        GstPad *a_pad = gst_element_get_static_pad(source->get_bin(), "audiosrc");
        if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
                 g_critical ("link audio source to audiomixer failed.\n");
                 exit(1);
         }

        name = gst_pad_get_name(mixer_pad);
        this->mixerPads.push_back(name);
        //g_free(name);
        gst_element_set_state(source->databin, GST_STATE_PLAYING);
        GstClock *clock = gst_element_get_clock(pipeline);
        GstClockTime running_time = gst_clock_get_time(clock) - gst_element_get_base_time(pipeline);
        source->offset=running_time;
        g_print("New source: ""%s""\n", GST_ELEMENT_NAME(source->get_bin()));
        gst_pad_add_probe(source->videosrc, GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM,
                        (GstPadProbeCallback)source->bus_eos, dsrc.back(), NULL);
        g_timeout_add_seconds(5, GSourceFunc(source->doloop), dsrc.back());//loop the fil
        ui->videoList->addItem(add->sourceName);
        ui->audioList->addItem(add->sourceName);
        g_object_unref(mixer_pad);
        g_object_unref(a_pad);
        g_object_unref(in_sel);
        g_object_unref(lo_pad);

    }
        break;
    case 3:{     //file only audio src
        bool loop = true;
        source = new Datasrc(add->sourcefilePath, add->sourceName, loop);
        dsrc.push_back(source);
        g_signal_connect(source->decoder, "pad-added",
                            G_CALLBACK(source->pad_added), dsrc.back());
        gst_bin_add(GST_BIN(pipeline), source->get_bin());
        GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
        GstPad *a_pad = gst_element_get_static_pad(source->get_bin(), "audiosrc");
        if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
                 g_critical ("link audio source to audiomixer failed.\n");
                 exit(1);
         }
        gchar *name = gst_pad_get_name(mixer_pad);
        this->mixerPads.push_back(name);
        //g_free(name);
        g_object_unref(mixer_pad);
        g_object_unref(a_pad);
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        GstClock *clock = gst_element_get_clock(pipeline);
        GstClockTime running_time = gst_clock_get_time(clock) - gst_element_get_base_time(pipeline);
        source->offset=running_time;
        gst_pad_add_probe(source->audiosrc, GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM,
                        (GstPadProbeCallback)source->bus_eos, dsrc.back(), NULL);
        g_print("New source:""%s""\n", source->srcname->toUtf8().constData());
        g_timeout_add_seconds(5, GSourceFunc(source->doloop), dsrc.back());//loop the file
        ui->audioList->addItem(add->sourceName);

    }
        break;
    case 4:{    //file only video src
        bool loop = true;
        dsrc.push_back(new Datasrc(add->sourcefilePath, add->sourceName, loop));
        source = dsrc.back();
        g_signal_connect(source->decoder, "pad-added",
                            G_CALLBACK(source->pad_added), dsrc.back());
        gst_bin_add(GST_BIN(pipeline), source->get_bin());
        GstPad *in_sel = gst_element_request_pad (videoSelector, in_sel_template, NULL, NULL);
        GstPad *lo_pad = gst_element_get_static_pad(source->get_bin(), "videosrc");
        if (gst_pad_link (lo_pad, in_sel) != GST_PAD_LINK_OK ){
                 g_critical ("object to input-selector failed.\n");
                 exit(1);
         }
        gchar *name = gst_pad_get_name(in_sel);
        this->selectorPads.push_back(gst_pad_get_name(name));
        g_free(name);
        g_object_unref(in_sel);
        g_object_unref(lo_pad);
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        g_timeout_add_seconds(5, GSourceFunc(source->doloop), dsrc.back());//loop the file
        g_print("New source: %s\n", source->srcname->toUtf8().constData());
        ui->videoList->addItem(add->sourceName);

    }
        break;
    case 5:{

    }
        break;
    case 6:{

    }
        break;
    case 7:{

    }
        break;

    default:
        break;
    }

}

GstPadProbeReturn gstvideo::bus_eos(GstPad * pad, GstPadProbeInfo * info, Datasrc *v){
    GstEvent *event_pad = gst_pad_probe_info_get_event(info);
    GstEventType event_type = event_pad->type;

    switch (event_type) {
//    case GST_EVENT_EOS:{
//        g_print("EOS event droped downstream\n");
//        return GST_PAD_PROBE_DROP;
//    }
//        break;
     default:
        //g_print("downstream event type: %s\n", GST_EVENT_TYPE_NAME(event_pad));
        return GST_PAD_PROBE_OK;
        break;
    }
}

void gstvideo::callback(GstBus *bus, GstMessage* msg, gstvideo* v){

    g_print("Got message type: %s, from %s\n", GST_MESSAGE_TYPE_NAME(msg), gst_object_get_name(msg->src));
    GError *err;
    gchar *debug;
    gst_message_parse_error(msg, &err, &debug);
    g_print("Message: %s\n", err->message);
    g_error_free(err);
    g_free(debug);

}


GstBusSyncReply gstvideo::bus_sync_handler (GstBus *bus, GstMessage *message, gstvideo *v)
{
    if (!gst_is_video_overlay_prepare_window_handle_message (message))
        return GST_BUS_PASS;

    GstVideoOverlay *overlay;
    overlay = GST_VIDEO_OVERLAY (GST_MESSAGE_SRC (message));
    gst_video_overlay_set_window_handle (overlay, cam_window_handle);
    gst_message_unref (message);
    return GST_BUS_DROP;
    //arriba añado los elementos creados en el constructor a la pipeline de gstreamer
    //luego los conecto
    //obtengo el ID de la ventana creada en qt la cual asignare al ximagesink de gstreamer
    //y aseguro de sincronizar el llamado de la ventana a traves de mensajes en el bus de gstreamer
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

}



GstPadProbeReturn gstvideo::block_src(GstPad *pad, GstPadProbeInfo *info, gstvideo *v){

    GstPad *srcpad, *sinkpad;
    gst_pad_remove_probe(blockpad, GST_PAD_PROBE_INFO_ID(info));
    /* install new probe for EOS */
    srcpad = gst_element_get_static_pad (v->curr, "src");
    if(!pad){
        g_print("no se pudo obtener el pad del elemento para enviar un EOS");
        exit(1);
     }
    gst_pad_add_probe(srcpad, GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM, (GstPadProbeCallback)event_eos, v, NULL);
    gst_object_unref (srcpad);

    /* push EOS into the element, the probe will be fired when the
     * EOS leaves the effect and it has thus drained all of its data */

    sinkpad = gst_element_get_static_pad (v->curr, "sink");
    gst_pad_send_event (sinkpad, gst_event_new_eos ());
    gst_object_unref (sinkpad);

    return GST_PAD_PROBE_OK;
}


GstPadProbeReturn gstvideo::event_eos(GstPad * pad, GstPadProbeInfo * info, gstvideo *v){

  if (GST_EVENT_TYPE (GST_PAD_PROBE_INFO_DATA (info)) != GST_EVENT_EOS)
    return GST_PAD_PROBE_OK;
  gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));
  gst_element_set_state (v->curr, GST_STATE_NULL);
  gst_bin_remove (GST_BIN (pipeline), v->curr);

  switch (effect){
  case 0:
      v->curr = gst_element_factory_make("identity", "next");
      break;
  case 1:
      v->curr = gst_element_factory_make("dicetv", "next");
      break;
  case 2:
      v->curr = gst_element_factory_make("warptv", "next");
      break;
  case 3:
      v->curr = gst_element_factory_make("shagadelictv", "next");
      break;
  case 4:
      v->curr = gst_element_factory_make("revtv", "next");
      break;
  case 5:
      v->curr = gst_element_factory_make("radioactv", "next");
      break;
  case 6:
      v->curr = gst_element_factory_make("rippletv", "next");
      break;
  case 7:
      v->curr = gst_element_factory_make("frei0r-filter-tehroxx0r", "next");
      break;
  case 8:
      v->curr = gst_element_factory_make("frei0r-filter-cartoon", "next");
      break;
  case 9:
      v->curr = gst_element_factory_make("frei0r-filter-invert0r", "next");
      break;
  case 10:
      v->curr = gst_element_factory_make("frei0r-filter-pixeliz0r", "next");
      break;
  case 11:
      v->curr = gst_element_factory_make("frei0r-filter-nervous", "next");
      break;
  case 12:
      v->curr = gst_element_factory_make("frei0r-filter-vertigo", "next");
      break;
  case 13:
      v->curr = gst_element_factory_make("frei0r-filter-color-distance", "next");
      break;
  case 14:
      v->curr = gst_element_factory_make("frei0r-filter-perspective", "next");
      g_object_set(v->curr, "top-left-x", 0.8, "top-left-Y", 0.01, "top-right-x",0.01, "top-right-Y",0.03490 ,  NULL);
      break;
  case 15:
      v->curr = gst_element_factory_make("frei0r-filter-b", "next");
      break;
  case 16:
      v->curr = gst_element_factory_make("frei0r-filter-baltan", "next");
      break;
  case 17:
      v->curr = gst_element_factory_make("frei0r-filter-twolay0r", "next");
      break;
  case 18:
      v->curr = gst_element_factory_make("frei0r-filter-threelay0r", "next");
      break;
  case 19:
      v->curr = gst_element_factory_make("frei0r-filter-bw0r", "next");
      break;
  case 20:
      v->curr = gst_element_factory_make("frei0r-filter-sobel", "next");
      break;
  case 21:
      v->curr = gst_element_factory_make("frei0r-filter-distort0r", "next");
      break;
  default:
      v->curr = gst_element_factory_make("identity", "next");
      break;
    }

  gst_bin_add (GST_BIN (pipeline), v->curr);
  gst_element_link_many (v->conv_before, v->curr, v->conv_after, NULL);
  gst_element_set_state (v->curr, GST_STATE_PLAYING);
  return GST_PAD_PROBE_DROP;
}


void gstvideo::start()
{
    ui->bplay->hide();
    ui->bstop->setVisible(true);
    if(GST_STATE(pipeline) == GST_STATE_READY){
        g_print("change pipeline from ready to playing");
        gst_element_set_state (pipeline, GST_STATE_PLAYING);
        g_main_loop_run(loop);
    }
    else {
        if(GST_STATE(pipeline) == GST_STATE_PAUSED){
            g_print("change pipeline state from paused to playing");
            gst_element_set_state (pipeline, GST_STATE_PLAYING);

        }
    }

    //qDebug()<<"the Pipeline State is changing to playing STATE";

}

void gstvideo::stop(){
    ui->bplay->setVisible(true);
    ui->bstop->hide();
    if(GST_STATE(pipeline) == GST_STATE_PLAYING){
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
        qDebug()<<"the Pipeline State is changing to Paused";
    }

}

void gstvideo::contrast(int c){
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


void gstvideo::on_comboBox_currentIndexChanged(int index){
     Q_UNUSED(index);
    effect=ui->comboBox->currentIndex();
    //gstvideo *v;
    gst_pad_add_probe(blockpad, GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, (GstPadProbeCallback)block_src,this, NULL);
}

void gstvideo::avolume(int y){
     gdouble x = y/10.0;
     GstPad *pad = gst_element_get_static_pad(audiomixer, audiopad);
     g_object_set (G_OBJECT(pad), "volume", x, NULL);
     g_object_unref(pad);
}


void gstvideo::on_pushButton_clicked(){
    gstvideo::addSource();
}

void gstvideo::on_videoList_currentRowChanged(int currentRow){

        gboolean active = false;
        GValue p = G_VALUE_INIT;
        gchar *name1;
        GstIterator* it = gst_element_iterate_sink_pads(videoSelector);
        while ((gst_iterator_next(it, &p) == GST_ITERATOR_OK) && !active){
                name1 = gst_pad_get_name(g_value_get_object(&p));
                g_print("comparing video %s with  %s\n", this->selectorPads.at(currentRow), name1);
                if(g_strcmp0(this->selectorPads.at(currentRow), name1) == 0){
                     g_object_set (videoSelector, "active-pad", g_value_get_object(&p), NULL);
                     active = true;
                 }
         }
        gst_iterator_free(it);
        g_value_unset(&p);
        g_free(name1);
}

void gstvideo::on_audioList_currentRowChanged(int currentRow){ //volume control of sources

    gboolean active = false;
    GValue p = G_VALUE_INIT;
    GstIterator* it = gst_element_iterate_sink_pads(audiomixer);
    while ((gst_iterator_next(it, &p) == GST_ITERATOR_OK) && !active){
            audiopad = gst_pad_get_name(g_value_get_object(&p));
            g_print("comparing audio %s with  %s\n", this->mixerPads.at(currentRow), audiopad);
            if(g_strcmp0(this->mixerPads.at(currentRow), audiopad) == 0){
                gdouble current_volume;
                g_object_get(G_OBJECT(g_value_get_object(&p)), "volume", &current_volume, NULL);
                ui->slider5->setValue(int(current_volume*10.0));
                 active = true;
             }
     }
    gst_iterator_free(it);
    g_value_unset(&p);
}



void gstvideo::on_videoList_customContextMenuRequested(const QPoint &pos){

    QPoint globalPos = ui->videoList->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("effect", this, SLOT(veffectItem()));
    myMenu.addAction("delete",  this, SLOT(vdeleteItem()));
    myMenu.addAction("properties",  this, SLOT(vpropertyItem()));
    myMenu.exec(globalPos);

}

void gstvideo::on_audioList_customContextMenuRequested(const QPoint &pos){

    QPoint globalPos = ui->videoList->mapToGlobal(pos);

    // Create menu and insert some actions
    QMenu myMenu;
    myMenu.addAction("effect", this, SLOT(aeffectItem()));
    myMenu.addAction("delete", this, SLOT(adeleteItem()));
    myMenu.addAction("properties", this, SLOT(apropertyItem()));
    myMenu.exec(globalPos);

}

void gstvideo::vdeleteItem(){

    GstPad *pad = gst_element_get_static_pad (videoSelector, "sink_0");
    g_object_set (videoSelector, "active-pad", pad, NULL);
    g_object_unref(pad);
    gboolean active = false;
    int item = ui->videoList->currentRow();
    QListWidgetItem *video = ui->videoList->item(item);
    QListWidgetItem *audio;
    g_print("DSRC SIZE IS: %u \n", dsrc.size());

    for(int v = 0; v < dsrc.size(); v++){
        source = dsrc.at(v);
        g_print("SOURCE: %s \n", source->srcname->toUtf8().constData());
        if(g_strcmp0(source->srcname->toUtf8().constData(), video->text().toUtf8().constData()) == 0){
            if((source->videosrc != NULL) && (source->audiosrc != NULL) && (item != 0)){

                GstElement *srcx = gst_bin_get_by_name(GST_BIN(pipeline), source->srcname->toUtf8().constData());
                gst_element_set_state(srcx, GST_STATE_NULL);

                for(int i = 1; i < ui->audioList->count(); i++){//loop para encontrar el item seleccionado en videoList en audioList
                    audio = ui->audioList->item(i);              //y asi eliminarlo
                    if(g_strcmp0(video->text().toUtf8().constData(), audio->text().toUtf8().constData()) == 0){
                        QListWidgetItem *el = ui->videoList->takeItem(item);
                        delete el;
                        el = ui->audioList->takeItem(i); //elimino el item de la lista de audio sources
                        delete el;
                        gchar *name2; //ahora procedemos a liberar los pads solicitados de videoSelector y audiomixer.
                        GstIterator* it = gst_element_iterate_sink_pads(videoSelector);
                        GValue p = G_VALUE_INIT;
                        while ((gst_iterator_next(it, &p) == GST_ITERATOR_OK) && !active){
                            name2 = gst_pad_get_name(g_value_get_object(&p));
                            g_print("comparing video %s with  %s\n", this->selectorPads.at(item), name2);
                            if(g_strcmp0(this->selectorPads.at(item), name2) == 0){
                                gst_pad_unlink(source->videosrc, GST_PAD(g_value_get_object(&p)));
                                gst_element_release_request_pad(this->videoSelector, GST_PAD(g_value_get_object(&p)));
                                active = true;
                            }
                        }
                        active = false;
                        it = gst_element_iterate_sink_pads(audiomixer);
                        while ((gst_iterator_next(it, &p) == GST_ITERATOR_OK) && !active){
                            name2 = gst_pad_get_name(g_value_get_object(&p));
                            g_print("comparing audio %s with  %s\n", this->mixerPads.at(item), name2);
                            if(g_strcmp0(this->mixerPads.at(i), name2) == 0){
                                gst_pad_unlink(source->audiosrc, GST_PAD(g_value_get_object(&p)));
                                gst_element_release_request_pad(this->audiomixer, GST_PAD(g_value_get_object(&p)));
                                //g_object_unref(g_value_get_object(&p));
                                active = true;
                            }
                        }

                        gst_bin_remove(GST_BIN(pipeline), srcx);
                        g_print("Source %s was deleted\n", source->srcname->toUtf8().constData());
                        g_free(name2);
                        gst_iterator_free(it);
                        g_value_unset(&p);
                        gst_object_unref(srcx);
                        dsrc.erase(dsrc.begin() + item-1);
                        selectorPads.erase(selectorPads.begin() + item);
                        mixerPads.erase(mixerPads.begin() + i);

                    }
                }//fin del for
            }//segundo if

        }//primer if
    }


}

void gstvideo::veffectItem(){
    int item = ui->videoList->currentRow();
    g_print("item was modified D\n");
}

void gstvideo::vpropertyItem(){
    int item = ui->videoList->currentRow();
    Datasrc *src = dsrc.at(item-1);
    QString name = *src->srcname;
    GList *pads = GST_ELEMENT_PADS(audiomixer);
    guint number = g_list_length(pads) - 1;
    g_print("item is showed\n");
}

void gstvideo::apropertyItem(){

}

void gstvideo::aeffectItem(){

}

void gstvideo::adeleteItem(){

    gboolean active = false;
    int item = ui->audioList->currentRow();
    QListWidgetItem *video;
    QListWidgetItem *audio =  ui->audioList->item(item);

    for(int v = 0; v < dsrc.size(); v++){
        source = dsrc.at(v);
        if(g_strcmp0(source->srcname->toUtf8().constData(), audio->text().toUtf8().constData()) == 0){
            if((source->videosrc != NULL) && (source->audiosrc != NULL) && (item != 0)){
                GstPad *pad = gst_element_get_static_pad (videoSelector, "sink_0");
                g_object_set (videoSelector, "active-pad", pad, NULL);
                g_object_unref(pad);
                GstElement *srcx = gst_bin_get_by_name(GST_BIN(pipeline), source->srcname->toUtf8().constData());
                gst_element_set_state(srcx, GST_STATE_NULL);

                for(int i = 1; i < ui->videoList->count(); i++){
                    video = ui->videoList->item(i);
                    if(g_strcmp0(video->text().toUtf8().constData(), audio->text().toUtf8().constData()) == 0){
                        QListWidgetItem* el = ui->videoList->takeItem(i);
                        delete el;
                        el = ui->audioList->takeItem(item);
                        delete el;
                        gchar *name2;
                        GstIterator* it = gst_element_iterate_sink_pads(videoSelector);
                        GValue p = G_VALUE_INIT;
                        while ((gst_iterator_next(it, &p) == GST_ITERATOR_OK) && !active){
                            name2 = gst_pad_get_name(g_value_get_object(&p));
                            g_print("comparing video %s with  %s\n", this->selectorPads.at(i), name2);
                            if(g_strcmp0(this->selectorPads.at(i), name2) == 0){
                                gst_pad_unlink(source->videosrc, GST_PAD(g_value_get_object(&p)));
                                gst_element_release_request_pad(this->videoSelector, GST_PAD(g_value_get_object(&p)));
                                active = true;
                            }
                        }
                        active = false;
                        it = gst_element_iterate_sink_pads(audiomixer);
                        while ((gst_iterator_next(it, &p) == GST_ITERATOR_OK) && !active){
                            name2 = gst_pad_get_name(g_value_get_object(&p));
                            g_print("comparing audio %s with  %s\n", this->mixerPads.at(item), name2);
                            if(g_strcmp0(this->mixerPads.at(item), name2) == 0){
                                gst_pad_unlink(source->audiosrc, GST_PAD(g_value_get_object(&p)));
                                gst_element_release_request_pad(this->audiomixer, GST_PAD(g_value_get_object(&p)));
                                //g_object_unref(g_value_get_object(&p));
                                active = true;
                            }
                        }

                        gst_bin_remove(GST_BIN(pipeline), srcx);
                        g_print("Source %s was deleted\n", source->srcname->toUtf8().constData());
                        g_free(name2);
                        gst_iterator_free(it);
                        g_value_unset(&p);
                        gst_object_unref(srcx);
                        dsrc.erase(dsrc.begin() + item-1);
                        selectorPads.erase(selectorPads.begin() + i);
                        mixerPads.erase(mixerPads.begin() + item);

                    }
                }//fin segundo for
            }//fin segundo if
            else{

            }
        }//primer if
    }//primer for
}

