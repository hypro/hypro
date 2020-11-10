#FROM fefrei/carl:19.01
FROM smtrat/carl:19.10
RUN apt-get update \
    && apt-get install -y \
    gcc-8-base \
    openjdk-8-jre \
    uuid-dev \
    pkg-config \
    libboost-dev
COPY / /root/hypro/
RUN cd /root/hypro \
    && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release .. \
    && make resources \
    && make
