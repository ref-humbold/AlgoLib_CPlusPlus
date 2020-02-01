#! /bin/sh

set -e

sudo -i -- sh -c \
"cd /usr/src/googletest/googletest && \
mkdir build && \
cd build && \
cmake .. && \
make && \
cp *.a /usr/local/lib/"
