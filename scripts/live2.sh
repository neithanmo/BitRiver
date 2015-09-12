   #!/bin/bash

    ################### YouTube Settings ###################
    # These data are available to you when you create a Live event in YouTube
    # First Camera - INSERT YOUR OWN DATA
    youtube_auth1='your event key'
    # Second Camera - Optional
    youtube_auth2=''
    youtube_app='live2'
    serverurl='rtmp://a.rtmp.youtube.com/live2'
    ################### UStream Settings ###################
    # RTMP URL from your UStream Account : See www.ustream.tv -> Channel -> Remote
    rtmpurl='INSERT_YOUR_USTREAM_RTMP_URL_HERE'
    # This is your Stream Key : See www.ustream.tv -> Channel -> Remote
    streamkey='INSERT_YOUR_STREAM_KEY_HERE'
    ################### Twitch Settings ###################
    twitch_server=live.twitch.tv
    twitch_streamkey='INSERT_YOUR_STREAM_KEY_HERE'
    # twitch_streamkey=live_12345678_6asdk3khhewrkhqe4k32AswlH6hrwd
    ################### Akamai Settings ###################
    akamai_server='INSERT_YOUR_AKAMAI_SERVER_NAME_HERE'
    akamai_user='INSERT_YOUR_AKAMAI_USER_NAME_HERE'
    akamai_pass='INSERT_YOUR_AKAMAI_PASSWORD_NAME_HERE'
    ########################################################
    # You can change the settings below to suit your needs
    ###################### Settings ########################
    width=1280
    height=720
    audiorate=44100
    channels=2
    framerate='25/1'
    vbitrate=8000
    abitrate=128000
    GST_DEBUG="--gst-debug=flvmux:0,rtmpsink:0"
    ###################### Settings ########################
    ########################################################
    # THe following settings should not be changed
    h264_level=4.1
    h264_profile=main
    h264_bframes=0
    keyint=`echo "2 * $framerate" |bc`
    datarate=`echo "$vbitrate + $abitrate / 1000" |bc`
    flashver='FME/3.0%20(compatible;%20FMSc%201.0)'
    akamai_flashver="flashver=FMLE/3.0(compatible;FMSc/1.0) playpath=I4Ckpath_12@44448"
    ########################################################

    # This will detect gstreamer-1.0 over gstreamer-0.10
    gstlaunch=`which gst-launch-1.0`
    if [ X$gstlaunch != X ] ; then
      VIDEOCONVERT=videoconvert
      VIDEO='video/x-raw, format=(string)BGRA, pixel-aspect-ratio=(fraction)1/1, interlace-mode=(string)progressive'
      AUDIO=audio/x-raw
      # VIDEO=video/x-raw-yuv
      vfid=string
      afid="format=(string)S16LE, "
    else
        echo "Could not find gst-launch-1.0 or gst-launch-0.10. Stopping"
        exit
      fi
            if [ $1 = you2 -o $1 = youtube2 ] ; then
              auth="$youtube_auth2"
            else
              auth="$youtube_auth1"
            fi
            if [ X$auth = X ] ; then
              echo "auth was not set YouTube"
              exit 1
            fi
            ENCAUDIOFORMAT='aacparse ! audio/mpeg,mpegversion=4,stream-format=raw'
            videoencoder="x264enc bitrate=$vbitrate key-int-max=$keyint bframes=$h264_bframes byte-stream=false aud=true tune=zerolatency"
            audioencoder="faac bitrate=$abitrate"
            location=$serverurl'/x/'$auth'?videoKeyframeFrequency=1&totalDatarate='$datarate' app='$youtube_app' flashVer='$flashver' swfUrl='$serverurl
          
    ENCVIDEOFORMAT='h264parse ! video/x-h264,level=(string)'$h264_level',profile='$h264_profile
    VIDEOFORMAT='videoconvert ! '$VIDEO', framerate='$framerate', width='$width', height='$height
        AUDIOFORMAT="audio/x-raw, format=S16LE, layout=interleaved"
    TIMEOLPARMS='halignment=left valignment=bottom text="Stream time:" shaded-background=true'
    VIDEOSRC="tcpclientsrc host=163.1756.4567 port=6800 ! decodebin name=d ! videorate ! videoconvert "
    AUDIOSRC="d. ! queue ! audioconvert ! audioresample "

    gst-launch-1.0 -v $GST_DEBUG                         \
            $VIDEOSRC                               !\
            $VIDEOFORMAT                            !\
            queue                                   !\
            $VIDEOCONVERT                           !\
            $videoencoder                           !\
            $ENCVIDEOFORMAT                         !\
            queue                                   !\
            mux. $AUDIOSRC                          !\
            $AUDIOFORMAT                            !\
            queue                                   !\
            $audioencoder                           !\
            $ENCAUDIOFORMAT                         !\
            queue                                   !\
            flvmux streamable=true name=mux         !\
            queue                                   !\
            rtmpsink location="$location"
   



