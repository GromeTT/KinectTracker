#version 430

in vec3 vertex;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec4 color = { 0.0, 1.0, 0.0, 1.0};

varying vec4 varColor;

void main(void)
{
    varColor = color;
    gl_PointSize = 5;
    gl_Position = projectionMatrix * viewMatrix * vec4( vertex, 1 );
}
