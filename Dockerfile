FROM smtrat/carl:latest
RUN apt-get update \
&& apt-get install -y \
openjdk-8-jre \
uuid-dev \
pkg-config \
libboost-dev
COPY / /root/hypro/
RUN cd /root/hypro \
&& mkdir build && cd build && cmake .. \
&& make resources \
&& make
