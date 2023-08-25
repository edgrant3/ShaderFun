#include "postsurfaceshader.h"
#include <iostream>


PostSurfaceShader::PostSurfaceShader(OpenGLContext *context)
    : ShaderProgram(context),
      attrPos(-1), attrNor(-1), attrUV(-1), attrCol(-1), attrPosOffset(-1),
      unifModel(-1), unifModelInvTr(-1), unifView(-1), unifProj(-1),
      unifDimensions(-1), unifInstanceRes(-1), unifDepthSampler2D(-1)
{}

PostSurfaceShader::~PostSurfaceShader()
{}

void PostSurfaceShader::setupMemberVars()
{
    attrPos       = context->glGetAttribLocation(prog, "vs_Pos");
    attrNor       = context->glGetAttribLocation(prog, "vs_Nor");
    attrUV        = context->glGetAttribLocation(prog, "vs_UV");
    attrCol       = context->glGetAttribLocation(prog, "vs_Col");
    if(attrCol == -1) attrCol = context->glGetAttribLocation(prog, "vs_ColInstanced");
    attrPosOffset = context->glGetAttribLocation(prog, "vs_OffsetInstanced");


    unifModel      = context->glGetUniformLocation(prog, "u_Model");
    unifModelInvTr = context->glGetUniformLocation(prog, "u_ModelInvTr");
    unifView       = context->glGetUniformLocation(prog, "u_View");
    unifProj       = context->glGetUniformLocation(prog, "u_Proj");

    unifCameraPos = context->glGetUniformLocation(prog, "u_CameraPos");

    unifSampler2D  = context->glGetUniformLocation(prog, "u_RenderedTexture");
    unifDepthSampler2D  = context->glGetUniformLocation(prog, "u_DepthTexture");
    unifDimensions = context->glGetUniformLocation(prog, "u_Dimensions");

    unifTime = context->glGetUniformLocation(prog, "u_Time");
    unifInstanceRes = context->glGetUniformLocation(prog, "u_Res");

    unifDrawLambert = context->glGetUniformLocation(prog, "u_ShadeLambert");

    context->printGLErrorLog();
}

void PostSurfaceShader::setShadeLambert(int s)
{
    useMe();
    if (unifDrawLambert != -1)
    {
        context->glUniform1i(unifDrawLambert, s);
    }
}

//This function, as its name implies, uses the passed in GL widget
void PostSurfaceShader::draw(Drawable &d, int textureSlot = 0)
{
    useMe();

    if(unifSampler2D != -1)
    {
        context->glUniform1i(unifSampler2D, /*GL_TEXTURE*/textureSlot);
    }

    // Each of the following blocks checks that:
    //   * This shader has this attribute, and
    //   * This Drawable has a vertex buffer for this attribute.
    // If so, it binds the appropriate buffers to each attribute.

    if (attrPos != -1 && d.bindPos()) {
        context->glEnableVertexAttribArray(attrPos);
        context->glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 0, NULL);
    }

    if (attrNor != -1 && d.bindNor()) {
        context->glEnableVertexAttribArray(attrNor);
        context->glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, 0, NULL);
    }

    if (attrUV != -1 && d.bindUV()) {
        context->glEnableVertexAttribArray(attrUV);
        context->glVertexAttribPointer(attrUV, 2, GL_FLOAT, false, 0, NULL);
        context->glVertexAttribDivisor(attrUV, 0);
    }

    if (attrCol != -1 && d.bindCol()) {
        context->glEnableVertexAttribArray(attrCol);
        context->glVertexAttribPointer(attrCol, 3, GL_FLOAT, false, 0, NULL);
        context->glVertexAttribDivisor(attrCol, 0);
    }

    // Bind the index buffer and then draw shapes from it.
    // This invokes the shader program, which accesses the vertex buffers.
    d.bindIdx();
    context->glDrawElements(d.drawMode(), d.elemCount(), GL_UNSIGNED_INT, 0);

    if (attrPos != -1) context->glDisableVertexAttribArray(attrPos);
    if (attrNor != -1) context->glDisableVertexAttribArray(attrNor);
    if (attrUV != -1) context->glDisableVertexAttribArray(attrUV);

    context->printGLErrorLog();
}

// TODO: implement setCameraPos
void PostSurfaceShader::setCameraPos(const glm::vec3 &position)
{
    useMe(); // daddy

    if (unifCameraPos != -1) {
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniform3fv(unifCameraPos,
                        // How many vectors to pass
                           1,
                        // Pointer to the first element of the matrix
                           &position[0]);

    }

}

void PostSurfaceShader::setModelMatrix(const glm::mat4 &model)
{
    useMe();

    if (unifModel != -1) {
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniformMatrix4fv(unifModel,
                        // How many matrices to pass
                           1,
                        // Transpose the matrix? OpenGL uses column-major, so no.
                           GL_FALSE,
                        // Pointer to the first element of the matrix
                           &model[0][0]);

    }

    if (unifModelInvTr != -1) {
        glm::mat3 modelinvtr = glm::inverse(glm::transpose(glm::mat3(model)));
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniformMatrix3fv(unifModelInvTr,
                        // How many matrices to pass
                           1,
                        // Transpose the matrix? OpenGL uses column-major, so no.
                           GL_FALSE,
                        // Pointer to the first element of the matrix
                           &modelinvtr[0][0]);
    }
}

void PostSurfaceShader::setViewProjMatrix(const glm::mat4 &v, const glm::mat4 &p)
{
    // Tell OpenGL to use this shader program for subsequent function calls
    useMe();

    if(unifView != -1) {
    // Pass a 4x4 matrix into a uniform variable in our shader
                    // Handle to the matrix variable on the GPU
    context->glUniformMatrix4fv(unifView,
                    // How many matrices to pass
                       1,
                    // Transpose the matrix? OpenGL uses column-major, so no.
                       GL_FALSE,
                    // Pointer to the first element of the matrix
                       &v[0][0]);
    }

    if(unifProj != -1) {
    // Pass a 4x4 matrix into a uniform variable in our shader
                    // Handle to the matrix variable on the GPU
    context->glUniformMatrix4fv(unifProj,
                    // How many matrices to pass
                       1,
                    // Transpose the matrix? OpenGL uses column-major, so no.
                       GL_FALSE,
                    // Pointer to the first element of the matrix
                       &p[0][0]);
    }
}

void PostSurfaceShader::setInstanceResolution(const glm::vec3 &res)
{
    useMe();

    if (unifInstanceRes != -1) {
        // Pass a 4x4 matrix into a uniform variable in our shader
                        // Handle to the matrix variable on the GPU
        context->glUniform3fv(unifInstanceRes,
                        // How many vectors to pass
                           1,
                        // Pointer to the first element of the matrix
                           &res[0]);

    }
}

void PostSurfaceShader::drawInstanced(InstancedDrawable &d)
{
    useMe();

    if(d.elemCount() < 0) {
        throw std::out_of_range("Attempting to draw a drawable with m_count of " + std::to_string(d.elemCount()) + "!");
    }

    if(unifSampler2D != -1)
    {
        context->glUniform1i(unifSampler2D, /*GL_TEXTURE*/0);
    }

    if(unifDepthSampler2D != -1)
    {
        context->glUniform1i(unifDepthSampler2D, /*GL_TEXTURE*/1);
    }

    // Each of the following blocks checks that:
    //   * This shader has this attribute, and
    //   * This Drawable has a vertex buffer for this attribute.
    // If so, it binds the appropriate buffers to each attribute.

    // Remember, by calling bindPos(), we call
    // glBindBuffer on the Drawable's VBO for vertex position,
    // meaning that glVertexAttribPointer associates vs_Pos
    // (referred to by attrPos) with that VBO
    if (attrPos != -1 && d.bindPos()) {
        context->glEnableVertexAttribArray(attrPos);
        context->glVertexAttribPointer(attrPos, 4, GL_FLOAT, false, 0, NULL);
        context->glVertexAttribDivisor(attrPos, 0);
    }

    if (attrNor != -1 && d.bindNor()) {
        context->glEnableVertexAttribArray(attrNor);
        context->glVertexAttribPointer(attrNor, 4, GL_FLOAT, false, 0, NULL);
        context->glVertexAttribDivisor(attrNor, 0);
    }

    if (attrCol != -1 && d.bindCol()) {
        context->glEnableVertexAttribArray(attrCol);
        context->glVertexAttribPointer(attrCol, 3, GL_FLOAT, false, 0, NULL);
        context->glVertexAttribDivisor(attrCol, 1);
    }

    if (attrPosOffset != -1 && d.bindOffsetBuf()) {
        context->glEnableVertexAttribArray(attrPosOffset);
        context->glVertexAttribPointer(attrPosOffset, 3, GL_FLOAT, false, 0, NULL);
        context->glVertexAttribDivisor(attrPosOffset, 1);
    }

    // Bind the index buffer and then draw shapes from it.
    // This invokes the shader program, which accesses the vertex buffers.
    d.bindIdx();
    context->glDrawElementsInstanced(d.drawMode(), d.elemCount(), GL_UNSIGNED_INT, 0, d.instanceCount());
    context->printGLErrorLog();

    if (attrPos != -1) context->glDisableVertexAttribArray(attrPos);
    if (attrNor != -1) context->glDisableVertexAttribArray(attrNor);
    if (attrCol != -1) context->glDisableVertexAttribArray(attrCol);
    if (attrPosOffset != -1) context->glDisableVertexAttribArray(attrPosOffset);

}

void PostSurfaceShader::setDimensions(glm::ivec2 dims)
{
    useMe();

    if(unifDimensions != -1)
    {
        context->glUniform2i(unifDimensions, dims.x, dims.y);
    }
}
