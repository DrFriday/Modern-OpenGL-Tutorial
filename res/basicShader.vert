#version 120

// Attributes come from Shader.cpp, Assigned in Mesh.cpp
attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

// Passed to fragment shader
varying vec2 texCoord0;

varying vec3 normal0;

// Uniform variables are set by the CPU
uniform mat4 transform;

void main()
{
    // I can vary how much translation is happening by chaning the 1.0 in the point below.
    gl_Position = transform * vec4(position, 1.0);
    texCoord0 = texCoord;
    //  This trick starts to break down after having a non uniform scale
    normal0 = (transform * vec4(normal, 0.0)).xyz; // setting to 0.0, no translation on the normal, only rotated.
}
