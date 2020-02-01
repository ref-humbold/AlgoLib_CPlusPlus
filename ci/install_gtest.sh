#! /bin/sh

set -e

sudo -i \
cd /usr/src/googletest/googletest && \
mkdir build && \
cd build && \
cmake .. && \
make && \
cp *.a /usr/local/lib/
