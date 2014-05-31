#version 430

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 textCo;
layout (location = 3) in float pointSize;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec4 varColor;
varying vec2 varTex;

void main( void )
{
    varTex          = textCo;
    varColor        = color;
    gl_PointSize    = pointSize;
    gl_Position     = projectionMatrix * viewMatrix * modelMatrix * vec4( vertex,  1 );
}
