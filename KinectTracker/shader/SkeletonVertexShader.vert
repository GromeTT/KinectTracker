#version 430

in vec3 vertex;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec4 varColor;

void main(void)
{
    varColor = vec4( 1, 0, 0, 1 );
    gl_PointSize = 5;
    gl_Position = projectionMatrix * viewMatrix * vec4( vertex, 1 );
}
