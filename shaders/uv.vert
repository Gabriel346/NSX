#version 330

layout(location = 0) in vec2 in_uv;
//layout(location = 1) in vec3 position;

//out vec2 uv;

uniform mat4 modelViewProj;

void main()
{
 gl_PointSize = 6.0f;
 gl_Position = modelViewProj * vec4(in_uv, 0.0, 1.0);
}
