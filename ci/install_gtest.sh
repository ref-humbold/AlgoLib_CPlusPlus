#! /bin/sh

set -e

cd /usr/src/googletest/googletest
sudo mkdir build
cd build
sudo cmake ..
sudo make
sudo cp *.a /usr/local/lib/
