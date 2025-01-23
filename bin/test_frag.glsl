#version 430 core

in vec4 Color;

out vec4 o_Albedo;

void main()
{
    o_Albedo = Color;
}