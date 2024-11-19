#version 430 core

in vec3 Color;
in vec2 PixelPos;
in vec2 PixelSize;

out vec4 o_Albedo;

void main()
{
    float x = gl_FragCoord.x;
    float y = 480.0 - gl_FragCoord.y;

    int distFromLeft = int(x) - int( PixelPos.x ) + 1;
    int distFromTop  = int(y) - int( PixelPos.y ) + 1;
    int distFromRight  = int(PixelPos.x) + int(PixelSize.x) - int(x);
    int distFromBottom = int(PixelPos.y) + int(PixelSize.y) - int(y);

    if ( distFromRight <= 1 || distFromBottom <= 1 )
    {
        // bottom and right
        float f = 255.0 / 255.0;
        o_Albedo = vec4( f,f,f, 1.0 );
    }
    else if ( distFromLeft <= 1 || distFromTop <= 1 ) 
    {
        // top and left
        float f = 128.0 / 255.0;
        o_Albedo = vec4( f,f,f, 1.0 );
    }
    else
    {
        // fill
        float f = 192.0 / 255.0;
        o_Albedo = vec4( f,f,f, 1.0 );
    }

}