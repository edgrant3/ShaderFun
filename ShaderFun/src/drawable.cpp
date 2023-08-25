#include "drawable.h"
#include <la.h>

Drawable::Drawable(OpenGLContext* context)
    : bufIdx(), bufPos(), bufNor(), bufUV(), bufCol(),
      idxBound(false), posBound(false), norBound(false), uvBound(false), colBound(false),
      context(context)
{}

Drawable::~Drawable()
{destroy();}

void InstancedDrawable::destroy()
{
    Drawable::destroy();
    clearColorBuf();
    clearOffsetBuf();
}

void Drawable::destroy()
{
    context->glDeleteBuffers(1, &bufIdx);
    context->glDeleteBuffers(1, &bufPos);
    context->glDeleteBuffers(1, &bufNor);
    context->glDeleteBuffers(1, &bufUV);
    context->glDeleteBuffers(1, &bufCol);
    idxBound = posBound = norBound = uvBound = colBound = false;
}

GLenum Drawable::drawMode()
{
    // Since we want every three indices in bufIdx to be
    // read to draw our Drawable, we tell that the draw mode
    // of this Drawable is GL_TRIANGLES

    // If we wanted to draw a wireframe, we would return GL_LINES

    return GL_TRIANGLES;
}

int Drawable::elemCount()
{
    return count;
}

void Drawable::generateIdx()
{
    idxBound = true;
    // Create a VBO on our GPU and store its handle in bufIdx
    context->glGenBuffers(1, &bufIdx);
}

void Drawable::generatePos()
{
    posBound = true;
    // Create a VBO on our GPU and store its handle in bufPos
    context->glGenBuffers(1, &bufPos);
}

void Drawable::generateNor()
{
    norBound = true;
    // Create a VBO on our GPU and store its handle in bufNor
    context->glGenBuffers(1, &bufNor);
}

void Drawable::generateUV()
{
    uvBound = true;
    // Create a VBO on our GPU and store its handle in bufCol
    context->glGenBuffers(1, &bufUV);
}

void Drawable::generateCol()
{
    colBound = true;
    // Create a VBO on our GPU and store its handle in bufCol
    context->glGenBuffers(1, &bufCol);
}

bool Drawable::bindIdx()
{
    if(idxBound) {
        context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    }
    return idxBound;
}

bool Drawable::bindPos()
{
    if(posBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    }
    return posBound;
}

bool Drawable::bindNor()
{
    if(norBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    }
    return norBound;
}

bool Drawable::bindUV()
{
    if(uvBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
    }
    return uvBound;
}

GLuint Drawable::getbufUV()
{
    return bufUV;
}

bool Drawable::bindCol()
{
    if(colBound){
        context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    }
    return colBound;
}

InstancedDrawable::InstancedDrawable(OpenGLContext *context)
    : Drawable(context), m_numInstances(0), m_bufPosOffset(), m_offsetGenerated(false)
{}

InstancedDrawable::~InstancedDrawable(){destroy();}

int InstancedDrawable::instanceCount() const {
    return m_numInstances;
}

void InstancedDrawable::generateOffsetBuf() {
    m_offsetGenerated = true;
    context->glGenBuffers(1, &m_bufPosOffset);
}

bool InstancedDrawable::bindOffsetBuf() {
    if(m_offsetGenerated){
        context->glBindBuffer(GL_ARRAY_BUFFER, m_bufPosOffset);
    }
    return m_offsetGenerated;
}


void InstancedDrawable::clearOffsetBuf() {
    if(m_offsetGenerated) {
        context->glDeleteBuffers(1, &m_bufPosOffset);
        m_offsetGenerated = false;
    }
}
void InstancedDrawable::clearColorBuf() {
    if(colBound) {
        context->glDeleteBuffers(1, &bufCol);
        colBound = false;
    }
}
