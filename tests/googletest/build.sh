#!/bin/bash

mkdir build
cd build
cmake .. -DCMAKE_CXX_STANDARD=17
make
make install

