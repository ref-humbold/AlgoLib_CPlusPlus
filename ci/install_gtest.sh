#! /bin/sh

set -e

sudo -i \
/usr/src/googletest/googletest && \
mkdir build && \
cd build && \
cmake .. && \
make && \
cp *.a /usr/local/lib/
