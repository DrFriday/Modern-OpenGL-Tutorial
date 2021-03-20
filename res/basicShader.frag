#version 120

varying vec2 texCoord0;
varying vec3 normal0;

// uniform is updated by the CPU, CPU write, GPU read
uniform sampler2D diffuse;

void main()
{
    // vec4(1.0, 0.0, 0.0, 1.0);
    // light direction is negative becasue it simulates the light reflecting off of a surface. Approx.
    // TODO: Move light direction to a uniform so I can specify
    gl_FragColor = texture2D(diffuse, texCoord0) * clamp(dot(-vec3(0, 0, 1) /* light direction */, normal0), 0.0, 1.0);
}
