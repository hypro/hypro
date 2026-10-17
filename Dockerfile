#FROM fefrei/carl:19.01
#FROM smtrat/carl:latest
#FROM stefanschupp/carl:hscc23
#FROM hyprodockeruser/carl:v1
FROM realyst/carl_z3:latest

RUN apt-get update \
    && apt-get install -y \
    gcc \
    openjdk-8-jre \
    uuid-dev \
    pkg-config \
    libboost-dev \
    iputils-ping
COPY / /root/hypro/
WORKDIR /root/hypro

ARG BUILD_JOBS=1

RUN cd /root/hypro && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DHYPRO_LOGGING=OFF -DHYPRO_STATISTICS=ON -DHYPRO_USE_Z3=ON ..
# PROJECT_NAME is a CMake variable, not set here: "make ${PROJECT_NAME}-resources" ran "make -resources", i.e. all targets including the tests
RUN cd /root/hypro/build && make hypro-resources -j ${BUILD_JOBS}
RUN cd /root/hypro/build && cmake .. && make hypro -j ${BUILD_JOBS}
# docker run -it hashOfImage bash
