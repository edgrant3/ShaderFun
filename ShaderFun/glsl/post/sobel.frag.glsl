#version 150

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;
uniform int u_Time;
uniform ivec2 u_Dimensions;

const float h_kernel[9] = float[9]( 3.0, 0.0, -3.0,
                                    10.0, 0.0, -10.0,
                                    3.0, 0.0, -3.0);

const float v_kernel[9] = float[9]( 3.0, 10.0, 3.0,
                                    0.0, 0.0, 0.0,
                                    -3.0, -10.0, -3.0);


void main()
{
    // TODO Homework 5
    color = vec3(0, 0, 0);

    vec3 hsum = vec3(0, 0, 0);
    vec3 vsum = vec3(0, 0, 0);

    for (int j = 0; j < 3; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            vec4 neighbor_col = texelFetch(u_RenderedTexture,
                                           ivec2(clamp(gl_FragCoord.x + i - 1, 0, u_Dimensions.x - 1),
                                                 clamp(gl_FragCoord.y + j - 1, 0, u_Dimensions.y - 1)), 0);
            float hk = h_kernel[i + 3 * j];
            float vk = v_kernel[i + 3 * j];

            hsum += hk * neighbor_col.rgb;
            vsum += vk * neighbor_col.rgb;
        }

    }
//    // if grayscale desired
//    vec3 hgray = vec3(0.21 * hsum.r + 0.72 * hsum.g + 0.07 * hsum.b);
//    vec3 vgray = vec3(0.21 * vsum.r + 0.72 * vsum.g + 0.07 * vsum.b);
//    color = vec3(sqrt(pow(hgray.x, 2) + pow(vgray.x, 2)),
//                 sqrt(pow(hgray.y, 2) + pow(vgray.y, 2)),
//                 sqrt(pow(hgray.z, 2) + pow(vgray.z, 2)));

    color = vec3(sqrt(pow(hsum.x, 2) + pow(vsum.x, 2)),
                 sqrt(pow(hsum.y, 2) + pow(vsum.y, 2)),
                 sqrt(pow(hsum.z, 2) + pow(vsum.z, 2)));


}
