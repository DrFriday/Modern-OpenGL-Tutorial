#version 120

// Attributes come from us
attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 u_transform;

void main()
{
  //                                       , Sets how much translation will take
  //                                       effect
  gl_Position = u_transform * vec4(position, 1.0);
  texCoord0 = texCoord;
}
