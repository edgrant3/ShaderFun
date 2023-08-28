#version 330

uniform sampler2D u_Texture; // The texture to be read from by this shader

in vec2 fs_UV;
in vec3 fs_Nor;

layout(location = 0) out vec3 out_Col;
layout(location = 1) out vec4 out_Nor;

void main()
{
    vec3 nor = (fs_Nor.xyz + vec3(1.0)) / vec3(2.0);
    out_Nor = vec4(nor, 0.0);

    vec4 diffuseColor = texture(u_Texture, fs_UV);
    out_Col = vec3(diffuseColor.rgb);

}
