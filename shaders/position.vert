#version 330

layout(location = 0) in vec3 position;

uniform mat4 modelViewProj;
uniform float point_size = 4.0f; //Some drivers do not implement uniform initializers correctly.
uniform float line_size = 4.0f;

void main()
{
  gl_PointSize = point_size;
  gl_Position = modelViewProj * vec4(position, 1.0);
}
