#version 150

uniform mat4 u_Model;
uniform mat3 u_ModelInvTr;
uniform mat4 u_View;
uniform mat4 u_Proj;

in vec4 vs_Pos;
in vec4 vs_Nor;
in vec2 vs_UV;

out vec2 fs_UV;

void main()
{
    // TODO Homework 4
    vec3 fs_Nor = normalize(u_ModelInvTr * vec3(vs_Nor));
    fs_Nor = mat3(u_View) * fs_Nor;

    fs_UV.x = (fs_Nor.x + 1) / 2;
    fs_UV.y = (fs_Nor.y + 1) / 2;

    vec4 modelposition = u_Model * vs_Pos;
    gl_Position = u_Proj * u_View * modelposition;
}
