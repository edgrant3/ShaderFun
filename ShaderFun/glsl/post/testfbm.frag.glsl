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

float signedNoise2D(vec2 p)
{
    return 2 * (-0.5 + fract(sin(dot(p, vec2(139.2, 269.1))) * 45858.5453));
}
float noise2D(vec2 p)
{
    return fract(sin(dot(p, vec2(139.2, 269.1))) * 45858.5453);
}

float signedinterpNoise2D(float x, float y) {
    int intX = int(floor(x));
    float fractX = fract(x);
    fractX = fractX * fractX * (3 - 2 * fractX); //cubic interp var
    int intY = int(floor(y));
    float fractY = fract(y);
    fractY = fractY * fractY * (3 - 2 * fractY); //cubic interp var

    float v1 = signedNoise2D(vec2(intX, intY));
    float v2 = signedNoise2D(vec2(intX + 1, intY));
    float v3 = signedNoise2D(vec2(intX, intY + 1));
    float v4 = signedNoise2D(vec2(intX + 1, intY + 1));

    float i1 = mix(v1, v2, fractX);
    float i2 = mix(v3, v4, fractX);
    return mix(i1, i2, fractY);
}

float interpNoise2D(float x, float y) {
    int intX = int(floor(x));
    float fractX = fract(x);
    fractX = fractX * fractX * (3 - 2 * fractX); //cubic interp var
    int intY = int(floor(y));
    float fractY = fract(y);
    fractY = fractY * fractY * (3 - 2 * fractY); //cubic interp var

    float v1 = noise2D(vec2(intX, intY));
    float v2 = noise2D(vec2(intX + 1, intY));
    float v3 = noise2D(vec2(intX, intY + 1));
    float v4 = noise2D(vec2(intX + 1, intY + 1));

    float i1 = mix(v1, v2, fractX);
    float i2 = mix(v3, v4, fractX);
    return mix(i1, i2, fractY);
}


float fbmR(float x, float y) {
    float noiseSum = 0;

    int octaves = 4;
    float freq = 15.f;

    float amp = 0.5f;
    float persistence = 0.5f;

    for(int i = 1; i <= octaves; i++) {
        noiseSum += interpNoise2D(x * freq, y * freq) * amp;
        freq *= 2.f;
        amp *= persistence;
    }
    return noiseSum;
}

float fbmG(float x, float y) {
    float noiseSum = 0;

    int octaves = 8;
    float freq = 5.f;

    float amp = 0.5f;
    float persistence = 0.6f;

    for(int i = 1; i <= octaves; i++) {
        noiseSum += interpNoise2D(x * freq, y * freq) * amp;
        freq *= 2.f;
        amp *= persistence;
    }
    return noiseSum;
}

float fbmB(float x, float y) {
    float noiseSum = 0;

    int octaves = 8;
    float freq = 10.f;

    float amp = 0.5f;
    float persistence = 0.5f;

    for(int i = 1; i <= octaves; i++) {
        noiseSum += interpNoise2D(x * freq, y * freq) * amp;
        freq *= 2.f;
        amp *= persistence;
    }
    return noiseSum;
}


void main()
{

    float green = fbmG((fs_UV.x), (fs_UV.y + 0.001*u_Time));
    float red = fbmR((fs_UV.x)*2.1247, 2.1247*((fs_UV.y) + 0.001*u_Time));
    float blue = fbmB((fs_UV.x)*3.1415, 3.1415*((fs_UV.y) + 0.001*u_Time));

//    green = smoothstep(0.1, 0.9, 1-pow(clamp(abs(green), 0, 1), .25)); // white rivers
//    green = pow(abs(green), 4);

    red = 1 - 0.5 * pow(red, 0.3);
    blue = 0.25 * (1 - 0.5 * pow(blue, 0.5));
    green = smoothstep(0.75, 0.25, green);


    float final = mix(blue, red, clamp(green, 0.f, 1.f));

//    color = vec3(final, final, final);
//    color = vec3(red, green, blue);
//    color = vec3(red, red, red);
    color = vec3(green, green, green);
//    color = vec3(blue, blue, blue);
//    color = vec3(red, 0.f, blue);
}
