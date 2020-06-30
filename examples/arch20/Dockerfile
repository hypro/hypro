FROM hypro/hypro@sha256:ac7deb2f5546d6844d9d3a44147142a8f9ec79a19861e75975bdb5b76680c68e
COPY / /root/hypro/
RUN cd /root/hypro \ 
    && mkdir -p build && cd build && cmake .. -DHYPRO_STATISTICS=ON -DHYPRO_LOGGING=OFF -DCMAKE_BUILD_TYPE=Release \
    && make hydra
