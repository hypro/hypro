#FROM fefrei/carl:19.01
FROM smtrat/carl:latest
RUN apt-get update \
    && apt-get install -y \
    gcc-8-base \
    openjdk-8-jre \
    uuid-dev \
    pkg-config \
    libboost-dev
COPY / /root/hypro/
RUN git submodule update --init
RUN cd /root/hypro && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release ..
RUN cd /root/hypro/build && make resources -j2
RUN cd /root/hypro/build && make -j2
