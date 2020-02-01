#! /bin/sh

set -ex

sudo -i \
    cd /usr/src/googletest/googletest && \
    mkdir build && \
    cd build && \
    pwd && \
    cmake .. && \
    make && \
    cp /usr/src/googletest/googletest/build/lib/*.a /usr/local/lib/
