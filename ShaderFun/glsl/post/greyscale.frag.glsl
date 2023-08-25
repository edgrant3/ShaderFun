#version 150

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;

void main()
{
    // TODO Homework 5

    // Material base color (before shading)
    vec4 base_color = texture2D(u_RenderedTexture, fs_UV);

    float gray = 0.21 * base_color.r + 0.72 * base_color.g + 0.07 * base_color.b;
    color = vec3(gray, gray, gray);

    vec2 center = vec2(0.5, 0.5);
    float dist = distance(fs_UV, center);

    float vignette = mix(1, 0, (2 * dist / sqrt(2)));

    color *= vignette;
}
