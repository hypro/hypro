FROM realyst/carl:latest
RUN apt-get update \
    && apt-get install -y \
    gcc \
    openjdk-8-jre \
    uuid-dev \
    pkg-config \
    libboost-dev \
    iputils-ping
COPY / /root/hypro/
RUN cd /root/hypro && mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release -DHYPRO_LOGGING=OFF -DHYPRO_STATISTICS=ON ..
RUN cd /root/hypro/build && make ${PROJECT_NAME}-resources -j`nproc`
RUN cd /root/hypro/build && cmake .. && make hypro -j`nproc`
