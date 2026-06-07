#!/bin/bash

cd build

cmake -DBUILD_TESTS=OFF -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .

cd ..
