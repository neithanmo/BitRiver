#!/bin/bash

WIDTH=1280
HEIGHT=720
abitrate=128000 
AUDIOSRC='fdsrc fd=0 do-timestamp=true ! queue '
VIDEOSRC='shmsrc socket-path=/tmp/mixer1 do-timestamp=true ! queue '
AUDIOFORMAT='audio/x-raw, format=S16LE, layout=interleaved'
AUDIOFORMATOUT='audio/mpeg,mpegversion=4, stream-format=raw'
VIDEOFORMAT='video/x-raw, format=BGRA, framerate=(fraction)25/1, pixel-aspect-ratio=(fraction)1/1, interlace-mode=progressive, width=1280, height=720'
VIDEOFORMATOUT='video/x-h264, alignment=au, stream-format=byte-stream, profile=(string)main'
ENCAUDIOFORMAT='aacparse ! audio/mpeg,mpegversion=4,stream-format=raw'
audioencoder="faac bitrate=$abitrate"

(echo audio sink ctr isaudio 1 ; sleep 100000000) | \
  /bin/nc 127.0.0.1 9999      | \
 (head -1
  gst-launch-1.0 \
    $AUDIOSRC !\
    $AUDIOFORMAT !\
    audioparse channels=1 !\
    audioconvert !\
    faac bitrate=128000 !\
    $AUDIOFORMATOUT !\
    aacparse !\
    queue !\
    muxer. $VIDEOSRC !\
    $VIDEOFORMAT !\
    queue  !\
    videoconvert !\
    x264enc bitrate=10000 tune=zerolatency speed-preset=2 key-int-max=50 bframes=0 !\
    $VIDEOFORMATOUT !\
    h264parse !\
    queue !\
    flvmux name=muxer streamable=true !\
    queue !\
    tcpserversink host=x.x.x.x port=6800 sync-method=2 recover-policy=keyframe
)


#para ver y oir este streaming

#ver
#gst-launch-0.10 -vvv tcpclientsrc host=163.178.119.249 port=5800 ! flvdemux name=demux ! ffdec_h264 ! xvimagesink sync=false 
# gst-launch-0.10 -vvv tcpclientsrc host=163.178.119.248 port=5500 ! flvdemux name=demux ! ffdec_h264 ! xvimagesink sync=false

#gst-launch-0.10 -vvv tcpclientsrc host=10.39.11.54 port=5800 ! flvdemux name=demux ! ffdec_h264 ! xvimagesink sync=false 
#gst-launch-0.10 -vvv tcpclientsrc host=10.39.11.53 port=5500 ! flvdemux name=demux ! ffdec_h264 ! xvimagesink sync=false

#gst-launch-0.10 tcpclientsrc port=6800 host=10.39.12.6 ! queue ! demux name=demux ! ffdec_h264 ! xvimagesink sync=false demux. ! audioresample ! audioconvert ! autoaudiosink sync=false
#gst-launch-0.10 -vvv tcpclientsrc host=163.178.119.249 port=5800 ! flvdemux name=demux ! ffdec_h264 ! xvimagesink sync=false demux. ! audioresample ! audioconvert ! autoaudiosink
#gst-launch-1.0 -vv tcpclientsrc host=163.178.119.210 port=6800 ! decodebin name=decoder ! autovideosink sync=false decoder. ! audioconvert ! alsasink sync=false en el pi

##oir
# gst-launch-0.10 -q tcpclientsrc host=163.178.119.210 port=6800 ! flvdemux name=demux ! audioresample ! audioconvert ! autoaudiosink sync=false


######################################################################### GRABAR #######################################################################################################################

# gst-launch-1.0 tcpclientsrc port=6800 ! queue ! filesink location="conferencia-24-08-2015.mkv"

########################################################################################################################################################################################################


## raspberry pi pantalla /
 # gst-launch-1.0 tcpclientsrc host=163.178.119.210 port=6800 ! decodebin name=decoder ! queue ! autovideosink sync=false decoder. ! audioconvert ! queue ! autoaudiosink sync=false en el pi (720p)

# gst-launch-1.0 -v tcpclientsrc host=163.178.119.210 port=6800 ! flvdemux name=demux demux.video_00 ! h264parse ! omxh264dec ! videoconvert !  eglglessink sync=true demux.audio ! queue ! mad ! alsasink sync=false ( no funciona la seccion de audio se pega.. investigar)

# gst-launch-1.0 -vv tcpclientsrc host=163.178.119.210 port=6800 ! decodebin name=decoder ! eglglessink sync=true decoder. ! audioconvert ! alsasink sync=true (funciona creo)


###################3


###  gst-launch-1.0 tcpclientsrc host=163.178.119.210 port=6800 ! flvdemux name=demux1 ! h264parse ! 
avdec_h264 ! videorate ! videoconvert ! queue ! autovideosink sync=false demux1.audio ! aacparse ! 
avdec_aac ! audioconvert ! queue ! autoaudiosink sync=false

 



