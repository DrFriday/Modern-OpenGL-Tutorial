#version 120

// Attributes come from us
attribute vec3 position;
attribute vec2 texCoord;

void main() { gl_Position = vec4(position, 1.0); }
