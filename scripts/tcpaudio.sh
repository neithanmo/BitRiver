#!/bin/bash
AUDIO=audio/x-raw-int
AUDIOFORMAT="audio/x-raw, format=S16LE, layout=interleaved"

(echo 'audio feed ctr isaudio 1';
gst-launch-1.0 -q tcpclientsrc host=163.178.119.212 port=6000 do-timestamp=true ! flvdemux name=d ! audioresample quality=8 ! audioconvert ! volume volume=0.65 ! $AUDIOFORMAT ! queue min-threshold-time=7000000000 ! fdsink fd=3 3>&1 1>&2 sync=true ) | nc 127.0.0.1 9999

### gst-launch-0.10 -q tcpclientsrc host=10.39.11.31 port=6000 ! flvdemux name=demux ! audioresample ! audioconvert ! autoaudiosink sync=false 

#### queue min-threshold-time (7000000000)
####7000000000 funciono perfecto, excelente sincronia 11-09-2015 si emite el pi.(audio sync=true y camaras sync=true) 
# 95505000 si uso salacullel

##

##gst-launch-0.10 -q tcpclientsrc host=163.178.119.210 port=6000 ! flvdemux name=demux ! audioresample ! audioconvert ! vorbisenc ! oggmux ! filesink location="sit.ogg"

