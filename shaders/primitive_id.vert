#version 330

layout(location = 0) in vec3 position;

uniform mat4 modelViewProj;

void main()
{
  gl_PointSize = 5.0f;
  gl_Position = modelViewProj * vec4(position, 1.0);
}
