#version 150

uniform mat4 u_Model;
uniform mat3 u_ModelInvTr;
uniform mat4 u_View;
uniform mat4 u_Proj;

uniform vec3 u_CameraPos;

in vec4 vs_Pos;
in vec4 vs_Nor;

out vec3 fs_Nor;
out vec3 fs_a;
out vec3 fs_b;
out vec3 fs_c;
out vec3 fs_d;

out vec3 fs_LightVec;

//out vec3 fs_LightVec;

void main()
{
    // TODO Homework 4
    fs_Nor = normalize(u_ModelInvTr * vec3(vs_Nor));

    vec4 modelposition = u_Model * vs_Pos;

    fs_LightVec = vec3(u_CameraPos - modelposition.xyz);

//    custom palettes
    fs_a = vec3(0.678, 0.238, 0.847);
    fs_b = vec3(0.142, 0.974, 0.109);
    fs_c = vec3(1.978, 3.138, 3.732);
    fs_d = vec3(4.499, 1.388, 2.168);

//    fs_a = vec3(0.731, 1.098, 0.192);
//    fs_b = vec3(0.358, 1.090, 0.657);
//    fs_c = vec3(2.154, 0.720, 0.656);
//    fs_d = vec3(0.965, 2.265, 0.837);

//    fs_a = vec3(-0.360, -0.360, -0.360);
//    fs_b = vec3(1.230, 1.230, 1.230);
//    fs_c = vec3(0.420, 0.420, 0.420);
//    fs_d = vec3(-1.410, -1.447, -1.303);

    // rainbow palette
//    fs_a = vec3(0.500, 0.500, 0.500);
//    fs_b = vec3(0.750, 0.750, 0.750);
//    fs_c = vec3(1.000, 1.000, 1.000);
//    fs_d = vec3(0.000, 0.333, 0.667);

    gl_Position = u_Proj * u_View * modelposition;
}
