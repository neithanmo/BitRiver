#include "gstvideo.h"

guintptr gstvideo::cam_window_handle;
static int effect = 0;
static GstPad *blockpad;

gstvideo::gstvideo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gstvideo)
{

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
    ui->slider5->setValue(0);
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
    gst_init(NULL, FALSE);
    input->exec();
    ui->widget->setFixedWidth(input->resolutionX);
    ui->widget->setFixedHeight(input->resolutionY);
    ui->bplay->hide();
    g_print("video Resolution: %dx%d \n", input->resolutionX, input->resolutionY);
    g_print("audio rate is: %d; audio bitrate is: %d \n", input->arate, input->abrate);
    g_print("video settings - framerate: %d, video bitrate: %d \n",input->framerate, input->vbrate);
    g_print("audio channels is: %d \n", input->channels);

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
    Svideoconvert = gst_element_factory_make("videoconvert", "sconvert");
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
    faac = gst_element_factory_make("voaacenc","aacAudioencoder");
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

    if (!pipeline ){
        qDebug("pipeline not created");
        return;
    }

    //###########################################################################################################################
    int keyint = 2*input->framerate;
    QString location = "rtmp://a.rtmp.youtube.com/live2/x/" + input->youtube + "?videoKeyframeFrequency=1&totalDatarate=8128 app=live2 flashVer=FME/3.0%20(compatible;%20FMSc%201.0) swfUrl=rtmp://a.rtmp.youtube.com/live2";

    g_object_set(rtmp, "location", location.toUtf8().constData(), "sync", FALSE, NULL);
    g_object_set(volume, "volume", 0, NULL);
    g_object_set(faac, "bitrate", input->abrate, NULL);
    g_object_set(x264enc, "bitrate", input->vbrate, "key-int-max", keyint, "bframes", 0, "byte-stream", false, "aud", true,
                 "threads", 2, "speed-preset", 1, "pass", 17, NULL);
    g_object_set(sink, "sync", TRUE, NULL);
    g_object_set(audiosink, "sync", TRUE, NULL);
    g_object_set(audioparse, "rate", input->arate, "channels", input->channels, NULL);
    g_object_set(flvmux, "streamable", TRUE, NULL);

    Vcaps = gst_caps_from_string("video/x-raw, format=BGRA, interlace-mode=progressive");
    Scaps = gst_caps_new_simple("video/x-raw",
                                      "interlace-mode", G_TYPE_STRING, "progressive",
                                      "width", G_TYPE_INT, input->resolutionX,
                                      "height", G_TYPE_INT, input->resolutionY,
                                       NULL);
    Acaps = gst_caps_from_string("audio/x-raw, format=S16LE, layout=interleaved, channels=2");
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
    //g_object_set(audiomixer, "start-time-selection" , 1, "caps", Acaps, NULL);
    //g_object_set(audiomixer, "caps",Acaps, NULL);
    //binpad = gst_element_get_static_pad(this->volume, "src");
    //GstPad *pad = gst_element_get_static_pad(this->videobalance, "src");

    window = ui->widget->winId();
    cam_window_handle=window;

    bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));

    gst_bus_set_sync_handler (this->bus, (GstBusSyncHandler) bus_sync_handler, this, NULL);
    gst_object_unref (this->bus);

    GstBus *mbus = gst_pipeline_get_bus(GST_PIPELINE(this->pipeline));
    gst_bus_add_signal_watch(mbus);


    connect(ui->slider1, SIGNAL(valueChanged(int)), this, SLOT(contrast(int)));
    connect(ui->slider2, SIGNAL(valueChanged(int)), this, SLOT(brightness(int)));
    connect(ui->slider3, SIGNAL(valueChanged(int)), this, SLOT(hue(int)));
    connect(ui->slider4, SIGNAL(valueChanged(int)), this, SLOT(saturation(int)));
    connect(ui->slider5, SIGNAL(valueChanged(int)), this, SLOT(avolume(int)));
    connect(ui->bplay, SIGNAL(clicked()), this, SLOT (start()));
    connect(ui->bstop, SIGNAL(clicked()), this, SLOT(stop()));
    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addSource()));

    configure();
    gst_element_set_state(this->pipeline, GST_STATE_PLAYING);

    g_signal_connect(mbus, "message::error", G_CALLBACK(callback), this);

    delete input;
}


gstvideo::~gstvideo(){
    gst_element_set_state(GST_ELEMENT(pipeline), GST_STATE_NULL);
    g_main_loop_quit(loop);
    gst_object_unref(pipeline);
    g_main_loop_quit(loop);
    delete ui;
    delete source;

}

void gstvideo::configure(){

    g_print("configuring the pipeline \n");
    QString videoDevice="/dev/"+input->localCamera;
    QString audioDevice = "plughw:"+input->localAudioCard;
    qDebug()<<"the sound card is " << audioDevice;
    qDebug()<<"video device is " << videoDevice;
    ui->videoList->addItem(videoDevice);


     //videoDevice.toUtf8().constData()
    g_object_set(defaultcamera, "do-timestamp", TRUE, "device", "/dev/video0","name",
                 videoDevice.toUtf8().constData(), NULL);
    g_object_set(Adefault, "do-timestamp", TRUE, "provide-clock", false, "device", "plughw:Generic",
                 "name", audioDevice.toUtf8().constData(), NULL);
    //g_object_set(audiotestsrc, "is-live", TRUE, "wave", 2, "do-timestamp", TRUE, NULL);
    blockpad = gst_element_get_static_pad(conversor1,"src");

    gst_bin_add_many(GST_BIN(pipeline),this->defaultcamera, this->videoSelector, vselqueue,this->scale, this->conversor1,
                     this->videobalance, conv_before, curr, conv_after,this->Ltee1, queue7, this->x264enc,
                     queue3, this->flvmux, queue4,
                     this->rtmp, this->Adefault, this->audiomixer, aselqueue, this->conv, this->audiosampler, this->volume, this->Ltee2,
                     queue9, this->faac, this->aacparse, queue5,
                     queue8, this->audiosink,
                     queue6, this->videosinkconvert, this->sink, NULL);

    GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
    GstPad *a_pad = gst_element_get_static_pad(this->Adefault, "src");
    if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
             g_critical ("link audio source to audiomixer failed.\n");
             exit(1);
     }
    ui->audioList->addItem(audioDevice);


    gst_element_link_many(this->audiomixer, this->aselqueue,this->conv, this->audiosampler, this->volume, this->Ltee2, NULL);
    gst_element_link(this->audioparse, this->volume);

    GstPad *in_sel = gst_element_request_pad (videoSelector, in_sel_template, NULL, NULL);//link default camera to videoSelector
    GstPad *lo_pad = gst_element_get_static_pad(this->defaultcamera, "src");
    if (gst_pad_link (lo_pad, in_sel) != GST_PAD_LINK_OK ){
             g_critical ("object to input-selector failed.\n");
             exit(1);
     }

    gst_element_link_many(this->videoSelector,this->vselqueue,this->scale, this->conversor1, NULL);

    gst_element_link_filtered(this->conversor1, this->videobalance,this->Scaps);
    gst_element_link_many(this->videobalance, conv_before, curr, conv_after, this->Ltee1,NULL);//tee1 for video visualization
                                                                      //and streaming branch
    gst_element_link_many(queue6, this->videosinkconvert, this->sink, NULL);//for local visualization
    gst_element_link_many(queue7, this->x264enc, queue3, NULL); //queue3 will be linked with flvmux by requesting
    gst_element_link_filtered(this->conversor1, this->videobalance,this->Scaps);
    gst_element_link_many(this->flvmux, queue4, this->rtmp, NULL);
    gst_element_link_many(queue8, this->audiosink, NULL); // audio local branch
    gst_element_link_many(queue9, this->faac, this->aacparse, NULL);//audio streaming branch
    gst_element_link_filtered(this->aacparse, queue5, this->enAcaps);//queue5 will be link with flvmux

    //****** Linking requesting pads ******************************

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
     if (gst_pad_link (tee1_q7_pad, q7_pad) != GST_PAD_LINK_OK ){
      g_critical ("Tee1 for queue7 could not be linked.\n");
      gst_object_unref (pipeline);
      exit(1);
     }//Tee linked with queue7 for video branch to x264enc!!!

     tee2_q9_pad = gst_element_request_pad (this->Ltee2, tee_src_pad_template2, NULL, NULL);

      q9_pad = gst_element_get_static_pad (queue9, "sink");
      /* Link the tee to the queue 7 */
      if (gst_pad_link (tee2_q9_pad, q9_pad) != GST_PAD_LINK_OK ){
       g_critical ("Tee2 for queue9 could not be linked.\n");
       gst_object_unref (pipeline);
       exit(1);
      }//Tee linked with queue9 for video branch to aacenc!!!

      tee1_q6_pad = gst_element_request_pad (this->Ltee1, tee_src_pad_template1, NULL, NULL);

      q6_pad = gst_element_get_static_pad(queue6, "sink");
      /* Link the tee to the queue 6 */
      if (gst_pad_link(tee1_q6_pad, q6_pad) != GST_PAD_LINK_OK ){ //  t1 ----> queue6
       g_critical ("Tee1 for queue6 could not be linked.\n");
       gst_object_unref (pipeline);
       exit(1);
      } //Tee linked with queue6 for local visualization!!!

      tee2_q8_pad = gst_element_request_pad (this->Ltee2, tee_src_pad_template2, NULL, NULL);
      q8_pad = gst_element_get_static_pad (queue8, "sink");
      /* Link the tee to the queue 6 */
      if (gst_pad_link (tee2_q8_pad, q8_pad) != GST_PAD_LINK_OK ){
       g_critical ("Tee2 for queue8 could not be linked.\n");
       gst_object_unref (pipeline);
       exit(1);
       } //Tee linked with queue6 for local visualization!!!

     /*######################### Linking queue 3 and 5 to flvmux ###########################################################*/

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
         if (gst_pad_link(video_queue3_src_pad, flvmux_sink_video_pad) == GST_PAD_LINK_OK ) {
             printf("link video queue with flvmixer\n");
         }

         gst_object_unref(audio_queue5_src_pad);
         gst_object_unref(video_queue3_src_pad);
         gst_object_unref (q6_pad);
         gst_object_unref(q7_pad);
         gst_object_unref (q8_pad);
         gst_object_unref(q9_pad);
         gst_object_unref(tee_src_pad_template1);
         gst_object_unref(tee_src_pad_template2);
         gst_object_unref (a_pad);
         gst_object_unref (mixer_pad);
}

void gstvideo::addSource(){
    newSource *add = new newSource;
    add->exec();
    switch(add->sourcetype) {
    case 0:{
        QString dev = "v4l2src";
        QString videoDevice="/dev/"+add->device;
        dsrc.push_back(new Datasrc(0, videoDevice));
        source = dsrc.back();
        //g_object_set(source->src, "do-timestamp", TRUE, "device", videoDevice.toUtf8().constData(), NULL);
        gst_bin_add(GST_BIN(this->pipeline), source->get_bin());
        GstPad *in_sel = gst_element_request_pad (videoSelector, in_sel_template, NULL, NULL);
        GstPad *lo_pad = gst_element_get_static_pad(source->get_bin(), "videosrc");
        if (gst_pad_link (lo_pad, in_sel) != GST_PAD_LINK_OK ){
                 g_critical ("object to input-selector failed.\n");
                 exit(1);
         }
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        g_object_unref(in_sel);
        g_object_unref(lo_pad);
        ui->videoList->addItem(add->sourceName);
        //  GST_DEBUG_OBJECT (pad, "clean up %" GST_PTR_FORMAT " and  %" GST_PTR_FORMAT,
        //selpad, pad);

        g_print("the new element added into the pipeline is: %s\n", GST_ELEMENT_NAME(source->get_bin()));

    }
        break;
    case 1:{
        QString dev = "alsasrc";
        QString audioDevice = "plughw:"+add->device;
        dsrc.push_back(new Datasrc(1, audioDevice));
        source = dsrc.back();
        //g_object_set(source->src, "do-timestamp", TRUE, "device", audioDevice.toUtf8().constData(), NULL);
        gst_bin_add(GST_BIN(this->pipeline), source->get_bin());
        GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
        GstPad *a_pad = gst_element_get_static_pad(source->get_bin(), "audiosrc");
        if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
                 g_critical ("link audio source to audiomixer failed.\n");
                 exit(1);
         }
        g_object_unref(mixer_pad);
        g_object_unref(a_pad);
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        g_print("the new element added into the pipeline is: %s\n", GST_ELEMENT_NAME(source->get_bin()));
        ui->audioList->addItem(audioDevice);

    }
        break;
    case 2:{  //file audio and video src
        bool loop = true;
        dsrc.push_back(new Datasrc(add->sourcefilePath, add->sourceName, loop));
        source = dsrc.back();
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
        //:::::::::::::::::::Audio ::::::::::::::::::::::::::::::::::::::::::::
        GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
        GstPad *a_pad = gst_element_get_static_pad(source->get_bin(), "audiosrc");
        if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
                 g_critical ("link audio source to audiomixer failed.\n");
                 exit(1);
         }
        long int position_nano;
        gst_element_query_position(pipeline, GST_FORMAT_TIME, &position_nano);
        g_print ("Duration: %" GST_TIME_FORMAT "\n", GST_TIME_ARGS (position_nano));
        gst_pad_set_offset(lo_pad, position_nano);
        gst_pad_set_offset(a_pad, position_nano);
        gst_element_sync_state_with_parent(source->get_bin());
        //gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        gst_pad_add_probe(gst_element_get_static_pad(source->src,"src"), GST_PAD_PROBE_TYPE_EVENT_DOWNSTREAM,
                          (GstPadProbeCallback)source->bus_eos, dsrc.back(), NULL);
        g_print("the new element added into the pipeline is: %s\n", GST_ELEMENT_NAME(source->get_bin()));
        GList *pads = GST_ELEMENT_PADS(audiomixer);
        guint number = g_list_length(pads);
        g_print("current number of audiomixer pads is: %u \n", number);
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
        dsrc.push_back(new Datasrc(add->sourcefilePath, add->sourceName, loop));
        source = dsrc.back();
        g_signal_connect(source->decoder, "pad-added",
                            G_CALLBACK(source->pad_added), dsrc.back());
        gst_bin_add(GST_BIN(pipeline), source->get_bin());
        GstPad *mixer_pad = gst_element_request_pad (audiomixer, mix_template, NULL, NULL);
        GstPad *a_pad = gst_element_get_static_pad(source->get_bin(), "audiosrc");
        if (gst_pad_link (a_pad, mixer_pad) != GST_PAD_LINK_OK ){
                 g_critical ("link audio source to audiomixer failed.\n");
                 exit(1);
         }
        g_object_unref(mixer_pad);
        g_object_unref(a_pad);
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        g_print("the new element added into the pipeline is: %s\n", GST_ELEMENT_NAME(source->get_bin()));
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
        g_object_unref(in_sel);
        g_object_unref(lo_pad);
        gst_element_set_state(source->get_bin(), GST_STATE_PLAYING);
        g_print("the new element added into the pipeline is: %s\n", GST_ELEMENT_NAME(source->get_bin()));
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


void gstvideo::callback(GstBus *bus, GstMessage* msg, gstvideo* v)
{

    g_print("Got message type: %s, from %s\n", GST_MESSAGE_TYPE_NAME(msg), gst_object_get_name(msg->src));
    GError *err;
    gchar *debug;
    gst_message_parse_error(msg, &err, &debug);
    g_print("Message: %s\n", err->message);
    g_error_free(err);
    g_free(debug);

}

//sync callback function for ximagesink and qt widget
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
    if(!pad)
    {
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


GstPadProbeReturn gstvideo::event_eos(GstPad * pad, GstPadProbeInfo * info, gstvideo *v)
{

  if (GST_EVENT_TYPE (GST_PAD_PROBE_INFO_DATA (info)) != GST_EVENT_EOS)
    return GST_PAD_PROBE_OK;
  gst_pad_remove_probe (pad, GST_PAD_PROBE_INFO_ID (info));
  gst_element_set_state (v->curr, GST_STATE_NULL);
  gst_bin_remove (GST_BIN (v->pipeline), v->curr);

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

  gst_bin_add (GST_BIN (v->pipeline), v->curr);
  gst_element_link_many (v->conv_before, v->curr, v->conv_after, NULL);
  gst_element_set_state (v->curr, GST_STATE_PLAYING);
  return GST_PAD_PROBE_DROP;
}

void gstvideo::start()
{
    ui->bplay->hide();
    ui->bstop->setVisible(true);
    if(GST_STATE(this->pipeline) == GST_STATE_READY){
        g_print("change pipeline from ready to playing");
        gst_element_set_state (this->pipeline, GST_STATE_PLAYING);
        g_main_loop_run(loop);
    }
    else {
        if(GST_STATE(this->pipeline) == GST_STATE_NULL){
            g_print("change pipeline state from paused to playing");
            gst_element_set_state (this->pipeline, GST_STATE_PLAYING);

        }
    }

    //qDebug()<<"the Pipeline State is changing to playing STATE";

}

void gstvideo::stop()
{
    ui->bplay->setVisible(true);
    ui->bstop->hide();
    if(GST_STATE(this->pipeline) == GST_STATE_PLAYING){
        gst_element_set_state (this->pipeline, GST_STATE_NULL);
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


void gstvideo::on_comboBox_currentIndexChanged(int index)
{
     Q_UNUSED(index);
    effect=ui->comboBox->currentIndex();
    //gstvideo *v;
    gst_pad_add_probe(blockpad, GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, (GstPadProbeCallback)block_src,this, NULL);
}

void gstvideo::avolume(int y){
     gdouble x = y/10.0;
    gst_stream_volume_set_volume (GST_STREAM_VOLUME(this->volume), GST_STREAM_VOLUME_FORMAT_LINEAR, x);
}


void gstvideo::on_pushButton_clicked()
{
    g_print("adding new source\n");
    gstvideo::addSource();
}

void gstvideo::on_videoList_currentRowChanged(int currentRow){

    gchar *name1 = g_strdup_printf ("sink_%u", currentRow);
    GstPad *pad = gst_element_get_static_pad (videoSelector, name1);
    g_object_set (videoSelector, "active-pad", pad, NULL);
    g_free(name1);
    g_object_unref(pad);

}

void gstvideo::on_audioList_currentRowChanged(int currentRow)
{
    gchar *name1 = g_strdup_printf ("sink_%u", currentRow);
    GstPad *pad = gst_element_get_static_pad (audiomixer, name1);
    //g_object_set (audiomixer, "active-pad", pad, NULL);
    g_object_set (pad, "volume", 1.5, NULL);
    g_free(name1);
    g_object_unref(pad);
}


