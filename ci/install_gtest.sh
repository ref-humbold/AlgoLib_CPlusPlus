#! /bin/sh

set -e

cd /usr/src/googletest/googletest
sudo mkdir build
cd build
sudo -s cmake ..
sudo -s make
sudo cp *.a /usr/local/lib/
