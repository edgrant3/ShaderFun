#version 330

//This is a fragment shader. If you've opened this file first, please open and read lambert.vert.glsl before reading on.
//Unlike the vertex shader, the fragment shader actually does compute the shading of geometry.
//For every pixel in your program's output screen, the fragment shader is run for every bit of geometry that particular pixel overlaps.
//By implicitly interpolating the position data passed into the fragment shader by the vertex shader, the fragment shader
//can compute what color to apply to its pixel based on things like vertex position, light position, and vertex color.

//uniform sampler2D u_RenderedTexture; // The texture to be read from by this shader
//uniform sampler2D u_DepthTexture;
//uniform ivec2 u_Dimensions;

//These are the interpolated values out of the rasterizer, so you can't know
//their specific values without knowing the vertices that contributed to them
in vec4 fs_Nor;
in vec4 fs_LightVec;
in vec4 fs_Col;
in float fs_delete;

layout(location = 0) out vec3 out_Col;//This is the final output color that you will see on your screen for the pixel that is currently being processed.

const float near = 0.2f;
const float far  = 1000.f;

const vec4 RED = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 GREEN = vec4(0.0, 1.0, 0.0, 1.0);
const vec4 BLUE = vec4(0.0, 0.0, 1.0, 1.0);

uniform bool u_ShadeLambert;

void main()
{
    if (fs_delete >= 0.9) { discard; }

//    vec2 coords = gl_FragCoord.xy / vec2(u_Dimensions);
//    float depth = texture(u_DepthTexture, coords).r;
    vec4 diffuseColor = fs_Col;

    if (u_ShadeLambert)
    {
        // Calculate the diffuse term for Lambert shading
        float diffuseTerm = dot(normalize(fs_Nor), normalize(fs_LightVec));
        // Avoid negative lighting values
        diffuseTerm = clamp(diffuseTerm, 0, 1);

        float ambientTerm = 0.2;

        float lightIntensity = diffuseTerm + ambientTerm;   //Add a small float value to the color multiplier
                                                            //to simulate ambient lighting. This ensures that faces that are not
                                                            //lit by our point light are not completely black.


        out_Col = vec3(diffuseColor.rgb * lightIntensity);
    }
    else
    {
        out_Col = diffuseColor.rgb;
    }

}
