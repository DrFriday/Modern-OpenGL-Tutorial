# Modern OpenGL Tutorial

This is a tutorial runthrough for OpenGL form this [video series](https://www.youtube.com/playlist?list=PLEETnX-uPtBXT9T-hD0Bj31DSnwio-ywh).

## Build Status

| Windows & Linux |
|-----------------|
| [![Build Status](https://travis-ci.com/DrFriday/Modern-OpenGL-Tutorial.svg?branch=master)](https://travis-ci.com/DrFriday/Modern-OpenGL-Tutorial)|


## How to build

    mkdir build

    cd build

    cmake ..

    // Use generated build system

## Lessons learned

Link both SDL2main and SDL2 to get things working.

Put shaders after the display is initialized, or else you'll get an error.
