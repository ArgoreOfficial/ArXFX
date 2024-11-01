#version 430 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

struct ScreenData
{
    int width;
    int height;
};

layout(binding = 0, std430) buffer ssbo2 {
    ScreenData screenData;
};

out gl_PerVertex
{
    vec4 gl_Position;
};

out vec3 Color;

void main()
{
    vec3 pos = aPosition;

    float aspect = float( screenData.width ) / float( screenData.height );
    pos.x /= aspect;
    Color = aColor;

    gl_Position = vec4( pos, 1.0 );
}