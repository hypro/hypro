FROM fefrei/carl:18.04
COPY / /root/hypro/
RUN echo "deb http://http.us.debian.org/debian/ testing non-free contrib main" >> /etc/apt/sources.list
RUN apt-get update \
&& apt-get install -y \
    gcc-7 \
    openjdk-8-jre \
    uuid-dev \
    pkg-config \
    libboost-dev
RUN cd /root/hypro \
&& mkdir build && cd build && cmake ../ \
&& make resources \
&& make
