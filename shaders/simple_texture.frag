#version 330

in vec2 uv;
uniform sampler2D texture_sampler;
out vec4 fColor;

void main()
{
    fColor = texture(texture_sampler, uv);
}
