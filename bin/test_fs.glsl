#version 430 core

in vec3 Color;

out vec4 o_Albedo;

void main()
{
    o_Albedo = vec4( Color, 1.0 );
}