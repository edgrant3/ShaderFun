#pragma once

#include "shaderprogram.h"

class SurfaceShader : public ShaderProgram
{
public:

    int attrPos; // A handle for the "in" vec4 representing vertex position in the vertex shader
    int attrNor; // A handle for the "in" vec4 representing vertex normal in the vertex shader
    int attrUV; // A handle for the "in" vec2 representing the UV coordinates in the vertex shader
    int attrCol; // A handle for the "in" vec4 representing vertex color in the vertex shader
    int attrPosOffset; // A handle for a vec3 used only in the instanced rendering shader

    int unifModel; // A handle for the "uniform" mat4 representing model matrix in the vertex shader
    int unifModelInvTr; // A handle for the "uniform" mat4 representing inverse transpose of the model matrix in the vertex shader
    int unifView; // A handle for the "uniform" mat4 representing the view matrix in the vertex shader
    int unifProj; // A handle for the "uniform" mat4 representing the projection matrix in the vertex shader

    int unifCameraPos; // A handle for the "uniform" vec3 representing camera's position in world space

public:
    SurfaceShader(OpenGLContext* context);
    virtual ~SurfaceShader();

    // Sets up shader-specific handles
    virtual void setupMemberVars() override;
    // Draw the given object to our screen using this ShaderProgram's shaders
    virtual void draw(Drawable &d, int textureSlot) override;

    // Pass the given camera position to this shader on the GPU
    void setCameraPos(const glm::vec3 &position);

    // Pass the given model matrix to this shader on the GPU
    void setModelMatrix(const glm::mat4 &model);
    // Pass the given Projection * View matrix to this shader on the GPU
    void setViewProjMatrix(const glm::mat4 &v, const glm::mat4 &p);

    // Draw the given object to our screen multiple times using instanced rendering
    void drawInstanced(InstancedDrawable &d);
};
