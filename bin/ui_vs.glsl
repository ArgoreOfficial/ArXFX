#version 430 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;

struct ScreenData
{
    mat4x4 proj;
    int width;
    int height;
};

struct PrimitiveData
{
	mat4x4 model;
	int pixelPos[2];
	int pixelSize[2];
};

layout(binding = 0, std430) buffer ssbo1 {
    ScreenData screenData;
};

layout(binding = 1, std430) buffer ssbo2 {
    PrimitiveData primData;
};

out gl_PerVertex
{
    vec4 gl_Position;
};

out vec3 Color;
out vec2 PixelPos;
out vec2 PixelSize;

void main()
{
    vec3 pos = aPosition;

    Color = aColor;
    PixelPos = vec2( primData.pixelPos[0], primData.pixelPos[1] );
    PixelSize = vec2( primData.pixelSize[0], primData.pixelSize[1] );

    gl_Position = screenData.proj * primData.model *  vec4( pos, 1.0 );
}