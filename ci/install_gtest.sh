#! /bin/sh

set -e

cd /usr/src/googletest/googletest
sudo mkdir build
cd build
sudo -E cmake ..
sudo -E make
sudo cp *.a /usr/local/lib/
