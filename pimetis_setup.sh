#!/bin/bash

git clone https://github.com/nlohmann/json
cd json
mkdir build && cd build
cmake ..
make
sudo make install

cd

git clone https://github.com/whoshuu/cpr.git
cd cpr
mkdir build && cd build
cmake ..
make
sudo make install