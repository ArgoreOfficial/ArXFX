#version 430 core

struct Vertex
{
	vec4 pos;
	vec4 col;
};

layout(binding = 0, std430) buffer ssbo2 {
    Vertex vertexBuffer[];
};

layout(binding = 1, std430) buffer ssbo1 {
    mat4x4 viewProj;
};

out gl_PerVertex
{
    vec4 gl_Position;
};

out vec4 Color;

void main()
{
    Vertex vert = vertexBuffer[ gl_VertexID ];
    
    gl_Position = viewProj * vec4( vert.pos.xyz, 1.0 );
    Color = vert.col;
}