#! /bin/sh

set -e

sudo -i \
  cd /usr/src/googletest/googletest && \
  mkdir build && \
  cd build && \
  cmake .. && \
  make

cp /usr/src/googletest/googletest/lib/*.a /usr/local/lib/
