#! /bin/sh

set -e

sudo -i -- sh -c \
"cd /usr/src/googletest/googletest && \
mkdir build && \
cd build && \
pwd && \
cmake .. && \
make && \
cp /usr/src/googletest/googletest/build/lib/*.a /usr/local/lib/"
