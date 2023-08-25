#pragma once

#include "drawable.h"
#include <memory>
#include <texture.h>
#include <limits>

struct BoundingBox
{
    glm::vec3 min;
    glm::vec3 max;
};

class Mesh : public InstancedDrawable
{
public:
    Mesh(OpenGLContext*);
    Mesh(OpenGLContext*, glm::vec3 lower, glm::vec3 upper);
    virtual ~Mesh();
    virtual void create() override;

    void createVBOdata(VBOvectors &);

    void createBoundCube(VBOvectors &,
                         const glm::vec3& lower,
                         const glm::vec3& upper,
                         bool setColor = false,
                         bool setBounds = true);

    void createSingleShapeFromOBJ(const char* filename, VBOvectors &gl, const char *textureFile, const char *bgTextureFile);
    void createFromOBJ(const char *filename, const char* textureFile, const char* bgTextureFile);
    void createCube(const char* textureFile, const char* bgTextureFile);

    void createInstancedVBOdata(VBOvectors &) override;

    // Obsolete method left for reference only
    void createInstancedCubeGrid(const glm::vec3 res, const glm::vec3 l, const glm::vec3 h);

    void bindTexture() const;
    void loadTexture() const;
    void bindBGTexture() const;
    void loadBGTexture() const;

    bool isInstanced();

    BoundingBox getBoundingBox();

    Texture* getBGtexture() const;

protected:
    glm::vec3 m_lowerBound;
    glm::vec3 m_upperBound;
    std::unique_ptr<Texture> mp_texture;
    std::unique_ptr<Texture> mp_bgTexture;
};

enum class InstancedShape:int {
    CUBE, OBJ
};

class InstancedShapeGrid: public Mesh
{
public:
    InstancedShapeGrid(OpenGLContext*);
    InstancedShapeGrid(OpenGLContext*, glm::vec3 res, glm::vec3 lower, glm::vec3 upper, float spacing = 0.f);
    ~InstancedShapeGrid();

    void create() override;

    void updateInstancedData();
    void updateSingularData();

    glm::vec3 getResolution() const;
    glm::vec3 getSpacing() const;

    void setShape(InstancedShape, std::string filename);
    void setResolution(glm::vec3 newRes);
    void setSpacing(float newSpace);
    void setBounds(glm::vec3 lower, glm::vec3 upper);

private:
    InstancedShape shape;
    std::string OBJfilename;
    glm::vec3 res;
    float spacing;

    void scaleData2Res(VBOvectors &gl);

};

class InstancedCubeGrid: public Mesh
{
public:
    InstancedCubeGrid(OpenGLContext*);
    InstancedCubeGrid(OpenGLContext*, glm::vec3 res, glm::vec3 lower, glm::vec3 upper, float spacing = 0.f);
    ~InstancedCubeGrid();

    void create() override;
    void updateInstancedData();
    void updateSingularData();

    glm::vec3 getResolution() const;
    void setResolution(glm::vec3 newRes);
    void setSpacing(float newSpace);
    void setBounds(glm::vec3 lower, glm::vec3 upper);

private:
    glm::vec3 res;
    float spacing; // % additional spacing to apply between instances
};

