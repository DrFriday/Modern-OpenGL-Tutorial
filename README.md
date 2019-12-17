# Modern OpenGL Tutorial

This is a tutorial runthrough for OpenGL form this [video series](https://github.com/glfw/glfw)

## How to build

    mkdir build

    cd build

    cmake ..

    // Use generated build system

## Lessons learned

Link both SDL2main and SDL2 to get things working.

Put shaders after the display is initialized, or else you'll get an error.
