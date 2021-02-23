#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 in_uv;

out vec4 vColor;
out vec2 uv;

uniform mat4 modelViewProj;

void main()
{
  gl_Position = modelViewProj * vec4(position, 1.0);
  uv = in_uv;
}
