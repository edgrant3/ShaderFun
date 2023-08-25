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


void main() {
    vec2 uvs = fs_UV * 15.f;
    float offset1 = random2(uvs).x;
    float offset2 = random2(uvs).y;

    float final = perlinNoise(vec2(uvs.x + 0.01*u_Time, uvs.y));
//    float final = perlinNoise(vec2(perlinNoise(coords+ 0.01*u_Time), perlinNoise(coords+ 0.01*u_Time)));
    final = 0.5 * (1 + final);
    color = vec3(final);
}
