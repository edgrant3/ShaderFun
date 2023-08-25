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

float noise2D(vec2 p)
{
    return fract(sin(dot(p, vec2(139.2, 269.1))) * 45858.5453);
}

float interpNoise2D(float x, float y) {
    int intX = int(floor(x));
    float fractX = fract(x);
    fractX = fractX * fractX * (3 - 2 * fractX);
    int intY = int(floor(y));
    float fractY = fract(y);
    fractY = fractY * fractY * (3 - 2 * fractY);

    float v1 = noise2D(vec2(intX, intY));
    float v2 = noise2D(vec2(intX + 1, intY));
    float v3 = noise2D(vec2(intX, intY + 1));
    float v4 = noise2D(vec2(intX + 1, intY + 1));

    float i1 = mix(v1, v2, fractX);
    float i2 = mix(v3, v4, fractX);
    return mix(i1, i2, fractY);
}


float fbm(float x, float y) {
    float total = 0;
    float persistence = 0.5f;
    int octaves = 8;
    float freq = 10.f;
    float amp = 0.5f;
    for(int i = 1; i <= octaves; i++) {
        total += interpNoise2D(x * freq,
                               y * freq) * amp;

        freq *= 2.f;
        amp *= persistence;
    }
    return total;
}


void main()
{
    float grey = fbm(fs_UV.x, fs_UV.y + 0.001*u_Time);
    grey = pow(1 - grey, 4.f);
    color = vec3(grey, grey, grey);
}
