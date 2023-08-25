#version 150

in vec2 fs_UV;

out vec3 color;

//uniform sampler2D u_RenderedTexture;
uniform sampler2D u_DepthTexture;

const float near = 0.1f;
const float far  = 1000.f;

const vec3 RED = vec3(1.f, 0.f, 0.f);
const vec3 GREEN = vec3(0.f, 1.f, 0.f);
const vec3 BLUE = vec3(0.f, 0.f, 1.f);

float LinearizeDepth(float d)
{
    float z = d * 2.0 - 1.0; // NDC
    return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    float depth = texture2D(u_DepthTexture, fs_UV).r;
//    depth = (LinearizeDepth(depth) - near) / (far - near);

//    float ndc   = depth * 2.f - 1.f;
//    float linDepth = (2.f * near * far) / (far + near - ndc * (far - near));
//    float frustlinDepth = (linDepth - near) / (far - near);

    color = vec3(depth);
}
