#version 150
// ^ Change this to version 130 if you have compatibility issues

#define PI 3.14159265358979311599796346854
#define HALFPI 1.57079632679

uniform mat4 u_Model;       // The matrix that defines the transformation of the
                            // object we're rendering. In this assignment,
                            // this will be the result of traversing your scene graph.

uniform mat3 u_ModelInvTr;  // The inverse transpose of the model matrix.
                            // This allows us to transform the object's normals properly
                            // if the object has been non-uniformly scaled.

uniform mat4 u_View;        // The matrix that defines the camera's transformation.
uniform mat4 u_Proj;        // The matrix that defines the camera's projection.

uniform sampler2D u_NormalTexture;
uniform sampler2D u_DepthTexture;
uniform sampler2D u_RenderedTexture;

uniform ivec2 u_Dimensions;
uniform vec3 u_Res;
uniform bool u_UseTexCol;
uniform bool u_UseGaussianFilter;
uniform bool u_UseNormalCulling;

uniform vec3 u_CameraPos;

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

const float kernel[25] = float[25](
0.00366300366300366, 0.01465201465201465, 0.02564102564102564, 0.01465201465201465, 0.00366300366300366,
0.01465201465201465, 0.05860805860805861, 0.09523809523809523, 0.05860805860805861, 0.01465201465201465,
0.02564102564102564, 0.09523809523809523, 0.15018315018315018, 0.09523809523809523, 0.02564102564102564,
0.01465201465201465, 0.05860805860805861, 0.09523809523809523, 0.05860805860805861, 0.014652014652014652,
0.00366300366300366, 0.01465201465201465, 0.02564102564102564, 0.01465201465201465, 0.003663003663003663 );

vec2 pxDist = vec2(1.0) / vec2(u_Dimensions);

vec2 toPx(vec2 screencoords)
{
    return floor(screencoords * u_Dimensions) + vec2(0.5f);
}

vec2 toScreenCoords(vec2 px)
{
    return px / u_Dimensions;
}

vec3 GaussianFilter(vec2 screencoords)
{
    // Gaussian Kernel Filtering of color using depth
    vec3  color = vec3(0.0);
    float sum = 0.0;
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 5; i++)
        {
            if (i == 2 && j == 2) { continue; }

            float k = kernel[i + 5 * j];
            vec2 coords = vec2(screencoords.x + float(i - 2) * pxDist.x,
                               screencoords.y + float(j - 2) * pxDist.y);

            float neighborDepth = texture2D(u_DepthTexture, coords).r;
            if (neighborDepth < 0.9975f)
            {
                vec3  neighborCol = texture2D(u_RenderedTexture, coords).rgb;
                color    += neighborCol   * k;
                sum += k;
            }
        }
    }
    if (sum > 0.0) {
        color    /= sum;
    }
    return color;
}


void main()
{
    // defaults
    fs_delete = 0.0;
    fs_Col = vec4(vs_ColInstanced, 1.0);
    fs_Nor = normalize(vec4(u_ModelInvTr * vec3(vs_Nor), 0));

    vec4 offsetpositionWorld = u_Model * (vec4(vs_OffsetInstanced, 1.0));
    vec4 offsetposition = u_Proj * u_View * offsetpositionWorld;
    vec2 screencoords = ((offsetposition.xy / offsetposition.w) + vec2(1.0)) / vec2(2.0);

    vec4 texNor = texture2D(u_NormalTexture, screencoords);
    if (texNor.a == 1.0) {
        fs_delete = 1.0;
        return;
    }

    vec3 remappedNor = texNor.rgb * vec3(2.0) - vec3(1.0);
    vec3 camDir = normalize(u_CameraPos - offsetpositionWorld.xyz);
    float norDotCam = abs(dot(remappedNor, camDir));

    float norCullVal = 0.075;
    if (u_UseNormalCulling && norDotCam < norCullVal) {
        vec2 screenNor = normalize(vec2(u_Proj * u_View * vec4(remappedNor, 0.0)));
        if (texture2D(u_NormalTexture, screencoords + vec2(5.0)*pxDist * screenNor).a == 1.0) {
            fs_delete = 1.0;
            return;
//            fs_Col = RED;
        }
    }


    float depth = (offsetposition.z / offsetposition.w + 1.0) / 2.0;
    float texdepth = texture2D(u_DepthTexture, screencoords).r;

    if (depth < 0.9995 * texdepth) {
        fs_delete = 1.0;
        return;
    }

    if (u_UseTexCol)
    {
        if (u_UseGaussianFilter)
        {
            vec3 color = GaussianFilter(screencoords);
            fs_Col = vec4(color, 1.f);
        }
        else
        {
            fs_Col = texture2D(u_RenderedTexture, screencoords);
        }
    }


//    // check textrure normal status
//    vec4 texNor = texture2D(u_NormalTexture, screencoords);
//    fs_Col = texNor;
//    if (texNor.a == 1.0) { fs_Col = vec4(0.0, 0.0, 0.0, 1.0); }
//    fs_delete = 0.0;
//    modelposition  = u_Model * (vs_Pos + vec4(vs_OffsetInstanced, 0.0));

    vec4 modelposition  = u_Model * (vs_Pos + vec4(vs_OffsetInstanced, 0.0));
    fs_LightVec = (inverse(u_View) * vec4(0.0,0.0,0.0,1.0)) - modelposition;  // Compute the direction in which the light source lies
    gl_Position = u_Proj * u_View * modelposition;// gl_Position is a built-in variable of OpenGL which is
                                                  // used to render the final positions of the geometry's vertices
}

//    if (texture2D(u_DepthTexture, vec2(0.0)).r > 0.9999f) { fs_Col = GREEN; }
//    if (u_Dimensions.x > 200.f) { fs_Col = GREEN; }
//    if (screencoords.x > 0.5 && screencoords.y > 0.75) { fs_Col = RED; }

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
