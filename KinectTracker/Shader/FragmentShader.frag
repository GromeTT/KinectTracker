#version 430

varying vec4 varColor;
varying vec2 varTex;
uniform bool useTexture;
uniform bool useSecondTexture;

layout ( binding = 0 ) uniform sampler2D tex0;
layout ( binding = 1 ) uniform sampler2D tex1;

void main( void )
{
    if ( useTexture )
    {
        vec4 texel0 = texture2D( tex0, varTex );
        vec4 texel1 = texture2D( tex1, varTex );
        if ( useSecondTexture )
        {
            vec4 tmp =  clamp ( texel0-texel1, 0.0, 1.0 ); // Calculate differences
//            tmp = step( vec4( 0.1, 0.1, 0.1, 0.1 ), tmp ); // Remove light dependend texels
//            gl_FragColor = clamp( texel0-tmp, 0.0, 1.0 );
            tmp.r = texel0.r - texel1.r;
            if ( tmp.r < 0 )
                tmp.r = 0;
            tmp.r = texel0.g - texel1.g;
            if ( tmp.g < 0 )
                tmp.g = 0;
            tmp.b = texel0.b - texel1.b;
            if ( tmp.b < 0 )
                tmp.b = 0;
            tmp.a = 1;

//            float threshold = 0.01;
//            if ( tmp.x < threshold )
//                tmp = vec4 ( 0, 0, 0, 1 );
//            if ( tmp.y < threshold )
//                tmp = vec4 ( 0, 0, 0, 1 );
//            if ( tmp.b < threshold )
//                tmp = vec4 ( 0, 0, 0, 1 );

//            threshold = 0;
//            if ( tmp.x > threshold )
//                tmp = vec4 ( 1, 1, 1, 1 );
//            if ( tmp.y > threshold )
//                tmp = vec4 ( 1, 1, 1, 1 );
//            if ( tmp.b > threshold )
//                tmp = vec4 ( 1, 1, 1, 1 );

//            if ( tmp == vec4( 1, 1, 1, 1) )
//                tmp = vec4 ( 0, 0, 0, 1 );
//            else
//                tmp = vec4 ( 1, 1, 1, 1 );



//            tmp = clamp( texel0 - tmp, 0, 1 );
            gl_FragColor = tmp;
        }
        else
        {
            gl_FragColor = texture2D( tex0, varTex );
        }
    }
    else
    {
        gl_FragColor = varColor;
    }
}
