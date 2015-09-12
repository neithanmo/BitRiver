#!/bin/bash

########################### settings y formatos de video para cada feed ##############################################

WIDTH=1280
HEIGHT=720
VIDEOFORMAT="videoconvert ! videorate ! videoscale ! videoconvert ! video/x-raw, format=BGRA, pixel-aspect-ratio=1/1, interlace-mode=progressive, width=1280, height=720 "

######################Direcciones ip de los Pi #####################################################################

SRC1="tcpclientsrc host=163.178.119.218 port=5000 ! flvdemux name=demux1 ! h264parse ! avdec_h264 ! videorate "
SRC2="tcpclientsrc host=163.178.119.248 port=5500 ! flvdemux name=demux2 ! h264parse ! avdec_h264 ! videorate "
SRC3="tcpclientsrc host=163.178.119.249 port=5800 ! flvdemux name=demux3 ! h264parse ! avdec_h264 ! videorate "

###################### Settings para los sockets de cada feed #######################################################

#SHMSIZE='shm-size=116121600'
SHMSIZE='shm-size=51609600' #40541040000 -- 
SHMOPTION="wait-for-connection=0"
CONTROL_PIPE1=/tmp/feed1-control-pipe
CONTROL_PIPE2=/tmp/feed2-control-pipe
CONTROL_PIPE3=/tmp/feed3-control-pipe
SHMSINK1="shmsink socket-path=$CONTROL_PIPE1 $SHMSIZE $SHMOPTION"
SHMSINK2="shmsink socket-path=$CONTROL_PIPE2 $SHMSIZE $SHMOPTION"
SHMSINK3="shmsink socket-path=$CONTROL_PIPE3 $SHMSIZE $SHMOPTION"

############################# Pipeline de Gstreamer para recibir los 3 feed via tcp #################################

            gst-launch-1.0 $SRC3              !\
            $VIDEOFORMAT ! queue              !\
            $SHMSINK3 sync=true $SRC1         !\
            $VIDEOFORMAT ! queue              !\
            $SHMSINK1 sync=true  $SRC2        !\
            $VIDEOFORMAT ! queue              !\
            $SHMSINK2 sync=true 
