#version 150
// ^ Change this to version 130 if you have compatibility issues

//This is a vertex shader. While it is called a "shader" due to outdated conventions, this file
//is used to apply matrix transformations to the arrays of vertex data passed to it.
//Since this code is run on your GPU, each vertex is transformed simultaneously.
//If it were run on your CPU, each vertex would have to be processed in a FOR loop, one at a time.
//This simultaneous transformation allows your program to run much faster, especially when rendering
//geometry with millions of vertices.

uniform mat4 u_Model;       // The matrix that defines the transformation of the
                            // object we're rendering. In this assignment,
                            // this will be the result of traversing your scene graph.

uniform mat3 u_ModelInvTr;  // The inverse transpose of the model matrix.
                            // This allows us to transform the object's normals properly
                            // if the object has been non-uniformly scaled.

uniform mat4 u_View;        // The matrix that defines the camera's transformation.
uniform mat4 u_Proj;        // The matrix that defines the camera's projection.

uniform sampler2D u_DepthTexture;
uniform sampler2D u_RenderedTexture;
uniform ivec2 u_Dimensions;
uniform vec3 u_Res;

in vec4 vs_Pos;             // The array of vertex positions passed to the shader
in vec4 vs_Nor;             // The array of vertex normals passed to the shader

in vec3 vs_ColInstanced;
in vec3 vs_OffsetInstanced;

out vec4 fs_Nor;            // The array of normals that has been transformed by u_ModelInvTr. This is implicitly passed to the fragment shader.
out vec4 fs_LightVec;       // The direction in which our virtual light lies, relative to each vertex. This is implicitly passed to the fragment shader.
out vec4 fs_Col;
out float fs_delete;

const vec4 RED = vec4(1.0, 0.0, 0.0, 1.0);
const vec4 GREEN = vec4(0.0, 1.0, 0.0, 1.0);
const vec4 BLUE = vec4(0.0, 0.0, 1.0, 1.0);

const vec4 MAGENTA = vec4(1.0, 0.0, 1.0, 1.0);
const vec4 YELLOW = vec4(1.0, 1.0, 0.0, 1.0);
const vec4 CYAN = vec4(0.0, 1.0, 1.0, 1.0);

void main()
{

//    fs_Col = vec4(vs_ColInstanced, 1);
//    vec2 pxDist = vec2(1.0) / vec2(u_Dimensions);

    fs_Nor = normalize(vec4(u_ModelInvTr * vec3(vs_Nor), 0)); // Pass the vertex normals to the fragment shader for interpolation.
                                                             // Transform the geometry's normals by the inverse transpose of the
                                                             // model matrix. This is necessary to ensure the normals remain
                                                             // perpendicular to the surface after the surface is transformed by
                                                             // the model matrix.

//    vec4 camPos = u_View * vec4(0.0, 0.0, 0.0, 1.0);
//    vec3 depthVec = length(u_Res) * (vec3(camPos) - vs_OffsetInstanced);

    vec4 modelposition;
    vec4 offsetposition;

    offsetposition = u_Proj * u_View * u_Model * (vec4(vs_OffsetInstanced, 1.0));

//    vec4 offsetplusResPosition = u_Proj * u_View * u_Model * (vec4(vs_OffsetInstanced + depthVec, 1.0));
//    float resDepth = (offsetplusResPosition.z / offsetplusResPosition.w + 1.0) / 2.0;

    vec2 screencoords = ((offsetposition.xy / offsetposition.w) + vec2(1.0)) / vec2(2.0);
    float depth = (offsetposition.z / offsetposition.w + 1.0) / 2.0;

    float texdepth = texture2D(u_DepthTexture, screencoords).r;

//    float resDiff = abs(depth - resDepth);

//    if (texdepth < 0.985) {
//        if (depth < 0.985) {
//            fs_Col = MAGENTA;
//        }
//        else {
//            fs_Col = RED;
//        }

//    }
//    else if (depth < 0.985) {
//        fs_Col = BLUE;
//    }

    if (depth >= 0.9995 * texdepth) { //(depth - texdepth >= -0.05 * resDiff) {
        modelposition  = u_Model * (vs_Pos + vec4(vs_OffsetInstanced, 0.0));
        fs_Col = texture2D(u_RenderedTexture, screencoords);
        fs_delete = 0.0;
    }
    else {
        modelposition = u_Model * (vs_Pos);
        fs_delete = 1.0;
    }

    fs_LightVec = (inverse(u_View) * vec4(0.0,0.0,0.0,1.0)) - modelposition;  // Compute the direction in which the light source lies
    gl_Position = u_Proj * u_View * modelposition;// gl_Position is a built-in variable of OpenGL which is
                                                  // used to render the final positions of the geometry's vertices
}
