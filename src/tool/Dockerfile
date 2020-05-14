FROM hypro/hypro:alpha
COPY / /root/hypro/
RUN cd /root/hypro \
    && mkdir -p build && cd build && cmake .. -DHYPRO_STATISTICS=ON -DHYPRO_LOGGING=OFF -DCMAKE_BUILD_TYPE=Release \
    && make hydra
