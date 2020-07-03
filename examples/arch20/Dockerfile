FROM hypro/hypro@sha256:392d9e3aa11d348ce9397a6bdd9e9c578b83d45e80fc80a2535d7ce4de888010
COPY / /root/hypro/
RUN cd /root/hypro \
    && mkdir -p build && cd build && cmake .. -DHYPRO_STATISTICS=ON -DHYPRO_LOGGING=OFF -DCMAKE_BUILD_TYPE=Release \
    && make hydra
