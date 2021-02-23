#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;
layout(location = 3) in vec2 in_uv;

//out struct frag_data {
//	vec3 position;
//	vec3 normal;
//};

out vec4 vColor;
out vec3 vNormal;
out vec2 line_pos;
out vec2 uv;
flat out vec2 line_start;

uniform mat4 modelViewProj;
uniform mat4 modelInverseTranspose;
uniform vec2 viewport_size;
//uniform mat4 ViewInverse;

void main()
{
  gl_PointSize = 5.5f;
  gl_Position = modelViewProj * vec4(position, 1.0);
  vNormal = vec3(modelInverseTranspose * vec4(normal, 1.0));
  vColor = vec4(normal, 1.0);
  line_pos = line_start = viewport_size * 0.5 * (gl_Position.xy / gl_Position.w);

  uv = in_uv;

  //gl_Position = modelViewProj * vec4(in_uv, 0.0, 1.0);

}
