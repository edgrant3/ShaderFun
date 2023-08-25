#version 150

uniform ivec2 u_Dimensions;
uniform int u_Time;

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;


// Generate random vec2 based on vec2 input
// (likely for generating vernoi points or displacements)
vec2 random2(vec2 p)
{
    return fract(sin(vec2(dot(p, vec2(127.1, 311.7)),
                          dot(p, vec2(269.5,183.3))))
                          * 43758.5453);
}

// Generate random vec3 based on vec2 input (likely for color)
vec3 random3(vec2 p)
{
    return fract(sin(vec3(dot(p, vec2(137.1, 312.7)),
                          dot(p, vec2(212.6, 256.8)),
                          dot(p, vec2(262.5, 184.3))))
                          * 45858.5453);
}

// Trying to emulate IQ's moving vornoi function here: https://www.shadertoy.com/view/MslGD8
vec3 voronoi(vec2 p) {
    vec2 pInt = floor(p);
    vec2 pFract = fract(p);
    vec2 min_point = p;
    float minDist = 100.0; // Minimum distance initialized to max.
    for(int y = -1; y <= 1; ++y) {
        for(int x = -1; x <= 1; ++x) {
            vec2 neighbor = vec2(float(x), float(y)); // Direction in which neighbor cell lies
            vec2 point = random2(pInt + neighbor); // Get the Voronoi centerpoint for the neighboring cell

            // moves point location so the voronoi cells change over time
            vec2 diff = neighbor - pFract + 0.5 * (1 + sin(0.025 * u_Time + 6.2831 * point));

            //vec2 diff = neighbor + point - pFract; // Distance between fragment coord and neighbor’s Voronoi point
            float dist = length(diff);
            if (dist < minDist)
            {
                minDist = dist;
                min_point = p + diff;
            }
        }
    }
    // return a vec3 packet containing minimun distance,
    // as well as the x and y coordinates of the closest vornoi point
    return vec3(minDist, min_point.x, min_point.y);
}


void main()
{
    // use sin wave to change number of vornoi cells over time (average of 100 cells)
    float dynamic_factor = 50 + .5*20 * sin(0.1 * 0.0025 * u_Time);
    vec3 worl = voronoi(dynamic_factor * fs_UV);
    vec2 worl_uv = worl.yz / dynamic_factor;

    // clamp sampling coordinates to texture size
    // (prevents grabbing black pixels outside of image)
    worl_uv.x = clamp(worl_uv.x * u_Dimensions.x, 0, u_Dimensions.x - 1);
    worl_uv.y = clamp(worl_uv.y * u_Dimensions.y, 0, u_Dimensions.y - 1);

    // trying chromatic abberation below

    // creates a noisy float value with which to displace the x-coord or each channel
    // (makes uniform-width noisy-looking chromatic abberation
    float chromatic = random2(fs_UV * u_Time).x;
    // adjust amount of CA over time (custom periodic function holds the non-abberated color for longer)
    float chromatic_intensity = 15 * (1 + sin(-1.1 * 3.14159/4 * (1 + cos(0.025 * u_Time))));

    // clamp these vals to texture dims as well
    float chrom_uv_r = clamp(worl_uv.x + chromatic_intensity * chromatic, 0, u_Dimensions.x - 1);
    float chrom_uv_b = clamp(worl_uv.x - chromatic_intensity * chromatic, 0, u_Dimensions.x - 1);

    // perform the rbg channel separation
    vec4 base_color_r = texelFetch(u_RenderedTexture, ivec2(chrom_uv_r, worl_uv.y), 0);
    vec4 base_color_g = texelFetch(u_RenderedTexture, ivec2(worl_uv.x, worl_uv.y), 0);
    vec4 base_color_b = texelFetch(u_RenderedTexture, ivec2(chrom_uv_b, worl_uv.y), 0);

    color = vec3(base_color_r.r, base_color_g.g, base_color_b.b);
}
