FROM fefrei/carl:18.08
COPY / /root/hypro/
RUN echo "deb http://http.us.debian.org/debian/ testing non-free contrib main" >> /etc/apt/sources.list
RUN apt-get update \
&& apt-get install -y \
    gcc-8 \
    g++-8 \
    g++-8-multilib \
    openjdk-8-jre \
    uuid-dev \
    pkg-config \
    libboost-dev
RUN export CC="gcc-8" && \
    export CXX="g++-8"
RUN cd /root/hypro \
&& mkdir build && cd build && cmake .. -DCMAKE_CXX_COMPILER=g++-8 \
&& make resources \
&& make
