#!/bin/bash

apt install libwayland-dev libxkbcommon-dev xorg-dev
wget "https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip"
unzip glfw-3.4.zip
rm -f glfw-3.4.zip
cd glfw-3.4
cmake -S . -B build
cd build
make




