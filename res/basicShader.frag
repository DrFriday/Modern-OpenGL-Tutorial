#version 120

varying vec2 texCoord0;

// uniform is updated by the CPU, CPU write, GPU read
uniform sampler2D diffuse;

void main()
{
    gl_FragColor = texture2D(diffuse, texCoord0);// vec4(1.0, 0.0, 0.0, 1.0);
}
