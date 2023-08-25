#pragma once

#include <openglcontext.h>
#include <la.h>

struct VBOvectors
{
    std::vector<GLuint>    idx;
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> nor;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> col;
    std::vector<glm::vec3> icol;
    std::vector<glm::vec3> ioff;
};

//This defines a class which can be rendered by our shader program.
//Make any geometry a subclass of ShaderProgram::Drawable in order to render it with the ShaderProgram class.
class Drawable
{
protected:
    int count;     // The number of indices stored in bufIdx.
    GLuint bufIdx; // A Vertex Buffer Object that we will use to store triangle indices (GLuints)
    GLuint bufPos; // A Vertex Buffer Object that we will use to store mesh vertices (vec4s)
    GLuint bufNor; // A Vertex Buffer Object that we will use to store mesh normals (vec4s)
    GLuint bufUV; // Can be used to pass per-vertex UV information to the shader
    GLuint bufCol;

    bool idxBound; // Set to TRUE by generateIdx(), returned by bindIdx().
    bool posBound;
    bool norBound;
    bool uvBound;
    bool colBound;

    OpenGLContext* context; // Since Qt's OpenGL support is done through classes like QOpenGLFunctions_3_2_Core,
                          // we need to pass our OpenGL context to the Drawable in order to call GL functions
                          // from within this class.

public:
    Drawable(OpenGLContext* context);
    virtual ~Drawable();
    virtual void create() = 0; // To be implemented by subclasses. Populates the VBOs of the Drawable.
    void destroy(); // Frees the VBOs of the Drawable.

    // Getter functions for various GL data
    virtual GLenum drawMode();
    int elemCount();

    // Call these functions when you want to call glGenBuffers on the buffers stored in the Drawable
    // These will properly set the values of idxBound etc. which need to be checked in ShaderProgram::draw()
    void generateIdx();
    void generatePos();
    void generateNor();
    void generateUV();
    void generateCol();

    bool bindIdx();
    bool bindPos();
    bool bindNor();
    bool bindUV();
    bool bindCol();

    GLuint getbufUV();
};


// A subclass of Drawable that enables the base code to render duplicates of
// the Terrain class's Cube member variable via OpenGL's instanced rendering.
// You will not have need for this class when completing the base requirements
// for Mini Minecraft, but you might consider using instanced rendering for
// some of the milestone 3 ideas.
class InstancedDrawable : public Drawable {
protected:
    int m_numInstances;
    GLuint m_bufPosOffset;

    bool m_offsetGenerated;

public:
    InstancedDrawable(OpenGLContext* mp_context);
    virtual ~InstancedDrawable();
    int instanceCount() const;
    void destroy();

    void generateOffsetBuf();
    bool bindOffsetBuf();
    void clearOffsetBuf();
    void clearColorBuf();

    virtual void createInstancedVBOdata(VBOvectors&) = 0;
};
