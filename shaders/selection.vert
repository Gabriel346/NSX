#version 420

layout(location = 0) in vec3 position;
//layout(location = 1) in vec3 color;
layout(location = 1) in float v_id;
//layout(location = 2) in int e_id;
//layout(location = 3) in int p_id;
//layout(location = 4) in int p_id;

out vec4 vColor;
flat out float vertex_id;

uniform mat4 modelViewProj;

void main()
{
  gl_PointSize = 28.0f;
  vertex_id = v_id;
  gl_Position = modelViewProj * vec4(position, 1.0);
  //vColor = vec4(color, 1.0);
}
