# Bitriver

First release of Bitriver
With this first version still in development, you can make streaming to youtube
You can configure this stream, and initially choose the data sources, from the local cameras and sound cards, local file or connect to a streaming server for  get the data

to compile bitriver you must first install the dependencies:

Gstreamer-1.0 
qt 

1)for gstreamer. first install plugins dependencies:

apt-get install libasound2-dev libgudev-1.0-dev libxt-dev libvorbis-dev libcdparanoia-dev libpango1.0-dev libtheora-dev libvisual-0.4-dev iso-codes libgtk-3-dev libraw1394-dev libiec61883-dev libavc1394-dev libv4l-dev libcairo2-dev libcaca-dev libspeex-dev libpng-dev libshout3-dev libjpeg-dev libaa1-dev libflac-dev libdv4-dev libtag1-dev libwavpack-dev libpulse-dev libsoup2.4-dev libbz2-dev libcdaudio-dev libdc1394-22-dev ladspa-sdk libass-dev libcurl4-gnutls-dev libdca-dev libdirac-dev libdvdnav-dev libexempi-dev libexif-dev libfaad-dev libgme-dev libgsm1-dev libiptcdata0-dev libkate-dev libmimic-dev libmms-dev libmodplug-dev libmpcdec-dev libofa0-dev libopus-dev librsvg2-dev librtmp-dev libschroedinger-dev libslv2-dev libsndfile1-dev libsoundtouch-dev libspandsp-dev libx11-dev libxvidcore-dev libzbar-dev libzvbi-dev liba52-0.7.4-dev libcdio-dev libdvdread-dev libmad0-dev libmp3lame-dev libmpeg2-4-dev libopencore-amrnb-dev libopencore-amrwb-dev libsidplay1-dev libtwolame-dev libx264-dev
then

2) clone gstreamer plugins
> git clone git://anongit.freedesktop.org/git/gstreamer/gstreamer
> git clone git://anongit.freedesktop.org/git/gstreamer/orc
> git clone git://anongit.freedesktop.org/git/gstreamer/gst-plugins-base
> git clone git://anongit.freedesktop.org/git/gstreamer/gst-plugins-good
> git clone git://anongit.freedesktop.org/git/gstreamer/gst-plugins-bad
> git clone git://anongit.freedesktop.org/git/gstreamer/gst-plugins-ugly
> git clone git://anongit.freedesktop.org/git/gstreamer/gst-libav
> git clone git://anongit.freedesktop.org/git/gstreamer/gst-omx

3) Build GStreamer, orc, gst-plugins-base, gst-plugins-good,
gst-plugins-ugly, gst-plugins-bad and gst-libav (in that order) by running these commands
inside their directories:
    ./configure
    make
    sudo make install

4)then you need instal QT libraries for your linux distribution

5) compiling BitRiver, go to the bitriver directory and run:
      make
