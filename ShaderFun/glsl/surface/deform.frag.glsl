#version 330

uniform sampler2D u_Texture; // The texture to be read from by this shader
uniform int u_Time;

in vec3 fs_Pos;
in vec3 fs_Nor;

in vec3 fs_LightVec;

in vec3 fs_a;
in vec3 fs_b;
in vec3 fs_c;
in vec3 fs_d;

in vec2 fs_UV;

layout(location = 0) out vec3 out_Col;
layout(location = 1) out vec4 out_Nor;

void main()
{
    vec3 nor = (fs_Nor.xyz + vec3(1.0)) / vec3(2.0);
    out_Nor = vec4(nor, 0.0);
    // Calculate the diffuse term for Lambert shading
    // (this keeps the fragment color still based on view angle)
    float t = dot(normalize(fs_Nor), normalize(fs_LightVec));

    // Avoid negative lighting values
    t = clamp(t, 0, 1);

    // cycles through cosine color profile
    vec4 IridescentColor;
    IridescentColor.x = fs_a.x + fs_b.x * cos(2 * 3.14159 * ((t + 0.01 * u_Time)* fs_c.x + fs_d.x));
    IridescentColor.y = fs_a.y + fs_b.y * cos(2 * 3.14159 * ((t + 0.01 * u_Time) * fs_c.y + fs_d.y));
    IridescentColor.z = fs_a.z + fs_b.z * cos(2 * 3.14159 * ((t + 0.01 * u_Time) * fs_c.z + fs_d.z));

    //vec4 diffuseColor = texture(u_Texture, fs_UV);
    //out_Col = vec3(diffuseColor.rgb);
    out_Col = vec3(IridescentColor.rgb);
}
