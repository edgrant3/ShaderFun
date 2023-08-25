#version 150

uniform ivec2 u_Dimensions;
uniform int u_Time;

in vec2 fs_UV;

out vec3 color;

uniform sampler2D u_RenderedTexture;

vec2 random2( vec2 p ) {
    return fract(sin(vec2(dot(p, vec2(127.1, 311.7)),
                 dot(p, vec2(269.5,183.3))))
                 * 43758.5653);
}

float falloff (vec2 p, vec2 corner) {
        float t = distance(p, corner); // Linear
        t = t*t*t*(t*(t*6 - 15) + 10); // Quintic, 6t5 - 15t4 + 10t3
        return 1 - t; // Want more weight the closer we are
}

float surflet(vec2 P, vec2 gridPoint) {
    // Compute falloff function by converting linear distance to a polynomial
    float distX = abs(P.x - gridPoint.x);
    float distY = abs(P.y - gridPoint.y);
    float tX = 1 - 6 * pow(distX, 5.f) + 15 * pow(distX, 4.f) - 10 * pow(distX, 3.f);
    float tY = 1 - 6 * pow(distY, 5.f) + 15 * pow(distY, 4.f) - 10 * pow(distY, 3.f);
    // Get the random vector for the grid point
    vec2 gradient = 2.f * random2(gridPoint) - vec2(1.f);
    // Get the vector from the grid point to P
    vec2 diff = P - gridPoint;
    // Get the value of our height field by dotting grid->P with our gradient
    float height = dot(diff, gradient);
    // Scale our height field (i.e. reduce it) by our polynomial falloff function
    return height * tX * tY;
}


float perlinNoise(vec2 uv) {
        float surfletSum = 0.f;
        // Iterate over the four integer corners surrounding uv
        for(int dx = 0; dx <= 1; ++dx) {
                for(int dy = 0; dy <= 1; ++dy) {
                        surfletSum += surflet(uv, floor(uv) + vec2(dx, dy));
                }
        }
        return surfletSum;
}

float noise2D(vec2 p)
{
    return fract(sin(dot(p, vec2(139.2, 269.1))) * 45858.5453);
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

float interpPerlin2D(float x, float y) {
    int intX = int(floor(x));
    float fractX = fract(x);
    fractX = fractX * fractX * (3 - 2 * fractX); //cubic interp var
    int intY = int(floor(y));
    float fractY = fract(y);
    fractY = fractY * fractY * (3 - 2 * fractY); //cubic interp var

    float v1 = 0.5 * (1 + perlinNoise(vec2(intX, intY)));
    float v2 = 0.5 * (1 + perlinNoise(vec2(intX + 1, intY)));
    float v3 = 0.5 * (1 + perlinNoise(vec2(intX, intY + 1)));
    float v4 = 0.5 * (1 + perlinNoise(vec2(intX + 1, intY + 1)));

    float i1 = mix(v1, v2, fractX);
    float i2 = mix(v3, v4, fractX);
    return mix(i1, i2, fractY);
}


float fbmPerlin(float x, float y) {
    float noiseSum = 0;

    int octaves = 7;
    float freq = 2*15.f;

    float amp = 0.125f;
    float persistence = 0.5f;

    for(int i = 1; i <= octaves; i++) {
        noiseSum += 0.5*(1+interpPerlin2D(x * freq, y * freq)) * amp;
        freq *= 2.f;
        amp *= persistence;
    }
    return noiseSum;
}


void main() {
    float dx = fs_UV.x + 0.001 * u_Time;
    float dy = fs_UV.y;

    float final = perlinNoise(20.f*vec2(dx, dy));

//    final = pow(final, 1.5);

    //final = 0.5 * (1 + final); // remap from [-1,1] to [0,1]

    final = 0.75 * final; // reduce amplitude to 0.5 prior to FBM

    //final += fbmPerlin(dx, dy);

    final = pow(final, 1.5);

//    final = pow(final, 5);
//    final = smoothstep(0.05, 0.75, final);

//    final = smoothstep(0.05, 0.75, final);
    if (final > 0.51) {
        final = 1.f;
    } else {
        final = 0.f;
    }
    color = vec3(final);
}
