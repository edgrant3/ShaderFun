#version 150

uniform mat4 u_Model;
uniform mat3 u_ModelInvTr;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform int u_Time;

uniform vec3 u_CameraPos;

in vec4 vs_Pos;
in vec4 vs_Nor;

out vec3 fs_Pos;
out vec3 fs_Nor;

out vec3 fs_a;
out vec3 fs_b;
out vec3 fs_c;
out vec3 fs_d;

out vec3 fs_LightVec;

in vec2 vs_UV;
out vec2 fs_UV;

// noise junk
float mod289(float x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 mod289(vec4 x){return x - floor(x * (1.0 / 289.0)) * 289.0;}
vec4 perm(vec4 x){return mod289(((x * 34.0) + 1.0) * x);}

float noise(vec3 p) {
    vec3 a = floor(p);
    vec3 d = p - a;
    d = d * d * (3.0 - 2.0 * d);

    vec4 b = a.xxyy + vec4(0.0, 1.0, 0.0, 1.0);
    vec4 k1 = perm(b.xyxy);
    vec4 k2 = perm(k1.xyxy + b.zzww);

    vec4 c = k2 + a.zzzz;
    vec4 k3 = perm(c);
    vec4 k4 = perm(c + 1.0);

    vec4 o1 = fract(k3 * (1.0 / 41.0));
    vec4 o2 = fract(k4 * (1.0 / 41.0));

    vec4 o3 = o2 * d.z + o1 * (1.0 - d.z);
    vec2 o4 = o3.yw * d.x + o3.xz * (1.0 - d.x);

    return o4.y * d.y + o4.x * (1.0 - d.y);
}

void main()
{
    fs_UV = vs_UV;

    fs_Nor = normalize(u_ModelInvTr * vec3(vs_Nor));

    vec4 modelposition = u_Model * vs_Pos;

    // The following treats Mario as if he were bound within
    // a cylinder which we can stretch and squish while maintaining
    // constant volume (animation technique)
    float c_scale = 0.1;
    float c = 1.1 + c_scale * cos(2 * 3.14159 * 0.025 * u_Time);
    modelposition.x *= c;
    modelposition.z *= c;
    modelposition.y /= pow(c, 2);

    // rainbow gradient
    fs_a = vec3(0.500, 0.500, 0.500);
    fs_b = vec3(0.750, 0.750, 0.750);
    fs_c = vec3(1.000, 1.000, 1.000);
    fs_d = vec3(0.000, 0.333, 0.667);

    // compute unique noise term to add for each cooridnate (wobbly effect)
    float modelnoisex = 0.65 * (noise(vec3(modelposition + u_Time * 0.1))-0.5);
    float modelnoisey = 0.65 * (noise(vec3(modelposition*2 + u_Time * 0.1))-0.5);
    float modelnoisez = 0.65 *(noise(vec3(modelposition*3 + u_Time * 0.1))-0.5);

    // apply noise terms via LERP
    modelposition.x = mix(modelposition.x, modelposition.x + modelnoisex, 0.25);
    modelposition.y = mix(modelposition.y, modelposition.y + modelnoisey, 0.25);
    modelposition.z = mix(modelposition.z, modelposition.z + modelnoisez, 0.25);

    fs_LightVec = vec3(u_CameraPos - modelposition.xyz);

    fs_Pos = vec3(modelposition);

    gl_Position = u_Proj * u_View * modelposition;
}
