#! /bin/sh

set -e

cd /usr/src/googletest/googletest
sudo mkdir build
cd build
sudo -i cmake ..
sudo -i make
sudo cp *.a /usr/local/lib/
