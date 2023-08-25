#include "mesh.h"
#include <tinyobj/tiny_obj_loader.h>
#include <iostream>
#include <QFile>

Mesh::Mesh(OpenGLContext *context)
    : InstancedDrawable(context),
      m_lowerBound(glm::vec3(std::numeric_limits<float>::max())),
      m_upperBound(glm::vec3(0.f)),
      mp_texture(nullptr), mp_bgTexture(nullptr)
{}

Mesh::Mesh(OpenGLContext* context, glm::vec3 lower, glm::vec3 upper)
    : InstancedDrawable(context),
      m_lowerBound(lower), m_upperBound(upper),
      mp_texture(nullptr), mp_bgTexture(nullptr)
{}

Mesh::~Mesh()
{}

void Mesh::createVBOdata(VBOvectors &gl)
{
//    std::cout << "glGenBuffers: " << context-> << std::endl;

    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, gl.idx.size() * sizeof(GLuint), gl.idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, gl.pos.size() * sizeof(glm::vec4), gl.pos.data(), GL_STATIC_DRAW);

    generateNor();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    context->glBufferData(GL_ARRAY_BUFFER, gl.nor.size() * sizeof(glm::vec4), gl.nor.data(), GL_STATIC_DRAW);

    if (!gl.uvs.empty())
    {
        generateUV();
        context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
        context->glBufferData(GL_ARRAY_BUFFER, gl.uvs.size() * sizeof(glm::vec2), gl.uvs.data(), GL_STATIC_DRAW);
    }

    if (!gl.col.empty())
    {
        generateCol();
        context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
        context->glBufferData(GL_ARRAY_BUFFER, gl.col.size() * sizeof(glm::vec3), gl.col.data(), GL_STATIC_DRAW);
    }
}

void Mesh::createInstancedVBOdata(VBOvectors &gl)
{
    generateOffsetBuf();
    bindOffsetBuf();
    context->glBufferData(GL_ARRAY_BUFFER, gl.ioff.size() * sizeof(glm::vec3), gl.ioff.data(), GL_STATIC_DRAW);

    if (!gl.icol.empty())
    {
        generateCol();
        bindCol();
        context->glBufferData(GL_ARRAY_BUFFER, gl.icol.size() * sizeof(glm::vec3), gl.icol.data(), GL_STATIC_DRAW);
    }
}

void Mesh::createInstancedCubeGrid(const glm::vec3 res, const glm::vec3 l, const glm::vec3 h)
{
    // Are these vec4's for homogenous coordinate reasons?
    VBOvectors gl;

    createBoundCube(gl, {0.f, 0.f, 0.f}, {res.x, res.y, res.z});

    // find number of instances total
    glm::vec3 diff = h - l;
    glm::ivec3 count({std::ceil(diff.x/res.x),
                      std::ceil(diff.y/res.y),
                      std::ceil(diff.z/res.z)});

    m_numInstances = count.x * count.y * count.z;

    for (int x = 0; x < count.x; x++)
    {
        for (int y = 0; y < count.y; y++)
        {
            for (int z = 0; z < count.z; z++)
            {
                glm::vec3 amount = l + glm::vec3(x, y, z) * 1.f * res ;
                gl.ioff.push_back(amount);
                gl.icol.push_back({(float)x/count.x, (float)y/count.y, (float)z/count.z});
            }
        }
    }

    createVBOdata(gl);
    createInstancedVBOdata(gl);
}

void Mesh::createBoundCube(VBOvectors &gl, const glm::vec3& l, const glm::vec3& h, bool setColor, bool setBounds)
{
    if (setBounds) {
        m_lowerBound = l;
        m_upperBound = h;
    }

    std::unordered_map<int, glm::vec3> m;
    m[0] = l; m[1] = h;

    glm::ivec4 a; // ordering of l and h bounds for quadrangulating face
    glm::ivec4 b; // ordering of l and h bounds for quadrangulating face
    glm::ivec4 c; // ordering of l and h bounds for quadrangulating face

    glm::ivec4* x; // ptr to a, b, or c
    glm::ivec4* y; // ptr to a, b, or c
    glm::ivec4* z; // ptr to a, b, or c

    // vert order is CCW around face when viewed with normal pointing to viewer

    int v_idx = (gl.idx.size() > 0) ? gl.idx.back() : 0;

    // axis: normal to the face we'll define verts for
    // side: 0->lower face, 1->upper face

    for (int side = 0; side < 2; side++)
    {
        c = glm::vec4(side, side, side, side);
        switch(side)
        {
            case 0:
                a = {0, 1, 1, 0};
                b = {0, 0, 1, 1};
                break;

            case 1:
                b = {0, 1, 1, 0};
                a = {0, 0, 1, 1};
                break;
        }
        for (int axis = 0; axis < 3; axis++)
        {
            switch(axis)
            {
                case 0:
                    x = &c; y = &a; z = &b;
                    break;
                case 1:
                    x = &b; y = &c; z = &a;
                    break;
                case 2:
                    x = &a; y = &b; z = &c;
                    break;
            }

            // compute normal
            glm::vec4 n(0, 0, 0, 0);
            n[axis] = -1.f + 2.f * side;

            for (int i = 0; i < 4; i++)
            {
                gl.pos.push_back({ m[(*x)[i]].x ,
                                m[(*y)[i]].y ,
                                m[(*z)[i]].z,
                                1 });
                gl.nor.push_back(n);
                if (setColor) { gl.col.push_back({0.5, 0.5, 0.5}); }
            }

            // fan triangulate quad
            int step = 1;
            for (int t = 0; t < 2; t++)
            {
                gl.idx.push_back(v_idx);
                for (int i = 1; i < 3; i++)
                {
                    gl.idx.push_back((v_idx + step));
                    step++;
                }
                step--;
            }
            v_idx += 4;
        }
    }
    count = gl.idx.size();
}

void Mesh::createCube(const char *textureFile, const char *bgTextureFile)
{
    // Code that sets up texture data on the GPU
    mp_texture = std::unique_ptr<Texture>(new Texture(context));
    mp_texture->create(textureFile);

    mp_bgTexture = std::unique_ptr<Texture>(new Texture(context));
    mp_bgTexture->create(bgTextureFile);

    m_lowerBound = {-1, -1, -1};
    m_upperBound = { 1,  1,  1};

    // vert order (normal view)
    //     - bottom left  (-1, -1)
    //     - bottom right ( 1, -1)
    //     - upper right  ( 1,  1)
    //     - upper left   (-1,  1)
    std::vector<glm::vec4> pos {glm::vec4(-1, 1, -1, 1), //(upper face) (x,z axes)
                                glm::vec4(1, 1, -1, 1),
                                glm::vec4(1, 1, 1, 1),
                                glm::vec4(-1, 1, 1, 1),

                                glm::vec4(1, -1, -1, 1), //(right face) (y,z axes)
                                glm::vec4(1, 1, -1, 1),
                                glm::vec4(1, 1, 1, 1),
                                glm::vec4(1, -1, 1, 1),

                                glm::vec4(1, 1, 1, 1), //(back face) (-x,y axes)
                                glm::vec4(-1, 1, 1, 1),
                                glm::vec4(-1, -1, 1, 1),
                                glm::vec4(1, -1, 1, 1),

                                glm::vec4(-1, -1, 1, 1), //(left face) (y,-z axes)
                                glm::vec4(-1, 1, 1, 1),
                                glm::vec4(-1, 1, -1, 1),
                                glm::vec4(-1, -1, -1, 1),

                                glm::vec4(-1, -1, -1, 1), //(front face) (x,y axes)
                                glm::vec4(1, -1, -1, 1),
                                glm::vec4(1, 1, -1, 1),
                                glm::vec4(-1, 1, -1, 1),

                                glm::vec4(-1, -1, 1, 1), //(bottom face) (x,-z axes)
                                glm::vec4(1, -1, 1, 1),
                                glm::vec4(1, -1, -1, 1),
                                glm::vec4(-1, -1, -1, 1)};

    std::vector<glm::vec4> nor {glm::vec4(0, 1, 0, 0), //(upper face) (+y)
                                glm::vec4(0, 1, 0, 0),
                                glm::vec4(0, 1, 0, 0),
                                glm::vec4(0, 1, 0, 0),

                                glm::vec4(1, 0, 0, 0), //(right face) (+x)
                                glm::vec4(1, 0, 0, 0),
                                glm::vec4(1, 0, 0, 0),
                                glm::vec4(1, 0, 0, 0),

                                glm::vec4(0, 0, 1, 0), //(back face) (z)
                                glm::vec4(0, 0, 1, 0),
                                glm::vec4(0, 0, 1, 0),
                                glm::vec4(0, 0, 1, 0),

                                glm::vec4(-1, 0, 0, 0), //(left face) (-x)
                                glm::vec4(-1, 0, 0, 0),
                                glm::vec4(-1, 0, 0, 0),
                                glm::vec4(-1, 0, 0, 0),

                                glm::vec4(0, 0, -1, 0), //(front face) (-z)
                                glm::vec4(0, 0, -1, 0),
                                glm::vec4(0, 0, -1, 0),
                                glm::vec4(0, 0, -1, 0),

                                glm::vec4(0, -1, 0, 0), //(bottom face) (-y)
                                glm::vec4(0, -1, 0, 0),
                                glm::vec4(0, -1, 0, 0),
                                glm::vec4(0, -1, 0, 0)};

    std::vector<glm::vec2> uvs {glm::vec2(0, 0),
                                glm::vec2(1, 0),
                                glm::vec2(1, 1),
                                glm::vec2(0, 1),

                                glm::vec2(0, 0),
                                glm::vec2(1, 0),
                                glm::vec2(1, 1),
                                glm::vec2(0, 1),

                                glm::vec2(0, 0),
                                glm::vec2(1, 0),
                                glm::vec2(1, 1),
                                glm::vec2(0, 1),

                                glm::vec2(0, 0),
                                glm::vec2(1, 0),
                                glm::vec2(1, 1),
                                glm::vec2(0, 1),

                                glm::vec2(0, 0),
                                glm::vec2(1, 0),
                                glm::vec2(1, 1),
                                glm::vec2(0, 1),

                                glm::vec2(0, 0),
                                glm::vec2(1, 0),
                                glm::vec2(1, 1),
                                glm::vec2(0, 1)};

    std::vector<GLuint> idx {0, 1, 2, 0, 2, 3,
                             4, 5, 6, 4, 6, 7,
                             8, 9, 10, 8, 10, 11,
                             12, 13, 14, 12, 14, 15,
                             16, 17, 18, 16, 18, 19,
                             20, 21, 22, 20, 22, 23};

    count = 36; // TODO: Set "count" to the number of indices in your index VBO

    generateIdx();
    context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateUV();
    context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
    context->glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), uvs.data(), GL_STATIC_DRAW);
}

void Mesh::create()
{
    // Does nothing, as we have two separate VBO data
    // creation functions: createFromOBJ, which creates
    // our mesh VBOs from OBJ file data, and createCube,
    // which you will implement.
}

void Mesh::bindTexture() const
{
    if (mp_texture != nullptr) {
        mp_texture->bind(0);
    }
}

void Mesh::loadTexture() const
{
    mp_texture->load(0);
}

void Mesh::bindBGTexture() const
{
    mp_bgTexture->bind(2);
}

Texture* Mesh::getBGtexture() const
{
    return mp_bgTexture.get();
}

void Mesh::loadBGTexture() const
{
    mp_bgTexture->load(2);
}

void Mesh::createSingleShapeFromOBJ(const char* filename, VBOvectors &gl, const char *textureFile, const char *bgTextureFile)
{
    std::vector<tinyobj::shape_t> shapes; std::vector<tinyobj::material_t> materials;
    std::string errors = tinyobj::QLoadObj(shapes, materials, filename);

    std::cout << errors << std::endl;
    assert(errors.size() == 0);

    count = 0;
    tinyobj::shape_t shape = shapes[0];

    //Read the information from the vector of shape_ts
    std::vector<float> &positions = shape.mesh.positions;
    std::vector<float> &normals = shape.mesh.normals;
    std::vector<float> &uvs = shape.mesh.texcoords;
    std::vector<unsigned int> &indices = shape.mesh.indices;
    count = indices.size();


    bool normalsExist = normals.size() > 0;
    bool uvsExist = uvs.size() > 0;

    for(unsigned int ui : indices)
    {
        gl.idx.push_back(ui);
    }
    for(int x = 0; x < positions.size(); x += 3)
    {
        for (int t = 0; t < 3; t++) {
            m_lowerBound[t] = glm::min(m_lowerBound[t], positions[x + t]);
            m_upperBound[t] = glm::max(m_upperBound[t], positions[x + t]);
        }

        gl.pos.push_back(glm::vec4(positions[x], positions[x + 1], positions[x + 2], 1.f));
        if(normalsExist)
        {
            gl.nor.push_back(glm::vec4(normals[x], normals[x + 1], normals[x + 2], 1.f));
        }
    }

    if(uvsExist)
    {
        for(int x = 0; x < uvs.size(); x += 2)
        {
            gl.uvs.push_back(glm::vec2(uvs[x], uvs[x + 1]));
        }
    }

    if (textureFile != nullptr) {
        mp_texture = std::unique_ptr<Texture>(new Texture(context));
        mp_texture->create(textureFile);
    }
    if (bgTextureFile != nullptr) {
        mp_bgTexture = std::unique_ptr<Texture>(new Texture(context));
        mp_bgTexture->create(bgTextureFile);
    }
}

void Mesh::createFromOBJ(const char* filename, const char *textureFile, const char *bgTextureFile)
{
    std::vector<tinyobj::shape_t> shapes; std::vector<tinyobj::material_t> materials;
    std::cout << "shapes size: " << shapes.size() << ", mats size: " << materials.size() << std::endl;
    std::string errors = tinyobj::QLoadObj(shapes, materials, filename);
    std::cout << errors << std::endl;
    if(errors.size() == 0)
    {
        count = 0;
        //Read the information from the vector of shape_ts
        for(unsigned int i = 0; i < shapes.size(); i++)
        {
            std::vector<float> &positions = shapes[i].mesh.positions;
            std::vector<float> &normals = shapes[i].mesh.normals;
            std::vector<float> &uvs = shapes[i].mesh.texcoords;
            std::vector<unsigned int> &indices = shapes[i].mesh.indices;

            bool normalsExist = normals.size() > 0;
            bool uvsExist = uvs.size() > 0;


            std::vector<GLuint> glIndices;
            for(unsigned int ui : indices)
            {
                glIndices.push_back(ui);
            }
            std::vector<glm::vec4> glPos;
            std::vector<glm::vec4> glNor;
            std::vector<glm::vec2> glUV;
            std::vector<glm::vec3> glCol;

            for(int x = 0; x < positions.size(); x += 3)
            {
                for (int t = 0; t < 3; t++) {
                    m_lowerBound[t] = glm::min(m_lowerBound[t], positions[x + t]);
                    m_upperBound[t] = glm::max(m_upperBound[t], positions[x + t]);
                }

                glPos.push_back(glm::vec4(positions[x], positions[x + 1], positions[x + 2], 1.f));
                if(normalsExist)
                {
                    glNor.push_back(glm::vec4(normals[x], normals[x + 1], normals[x + 2], 1.f));
                }

            }

            if(uvsExist)
            {
                for(int x = 0; x < uvs.size(); x += 2)
                {
                    glUV.push_back(glm::vec2(uvs[x], uvs[x + 1]));
                }
            }
            else {
                for (int x = 0; x < positions.size(); x += 3)
                {
                    glCol.push_back({125.0, 125.0, 125.0});
                }
            }

            count += indices.size();

            if (!normalsExist) {
                for (auto &idx : glIndices) {

                }
            }

            generateIdx();
            context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
            context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, glIndices.size() * sizeof(GLuint), glIndices.data(), GL_STATIC_DRAW);

            generatePos();
            context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
            context->glBufferData(GL_ARRAY_BUFFER, glPos.size() * sizeof(glm::vec4), glPos.data(), GL_STATIC_DRAW);

            if(normalsExist)
            {
                generateNor();
                context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
                context->glBufferData(GL_ARRAY_BUFFER, glNor.size() * sizeof(glm::vec4), glNor.data(), GL_STATIC_DRAW);
            }

            if(uvsExist)
            {
                generateUV();
                context->glBindBuffer(GL_ARRAY_BUFFER, bufUV);
                context->glBufferData(GL_ARRAY_BUFFER, glUV.size() * sizeof(glm::vec2), glUV.data(), GL_STATIC_DRAW);
            }
            else
            {
                generateCol();
                context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
                context->glBufferData(GL_ARRAY_BUFFER, glCol.size() * sizeof(glm::vec3), glCol.data(), GL_STATIC_DRAW);
            }


        }
    }
    else
    {
        //An error loading the OBJ occurred!
        std::cout << errors << std::endl;
    }

    if (textureFile != nullptr) {
        mp_texture = std::unique_ptr<Texture>(new Texture(context));
        mp_texture->create(textureFile);
    }
    if (bgTextureFile != nullptr) {
        mp_bgTexture = std::unique_ptr<Texture>(new Texture(context));
        mp_bgTexture->create(bgTextureFile);
    }
}

bool Mesh::isInstanced()
{
    return m_numInstances > 0;
}

BoundingBox Mesh::getBoundingBox()
{
    BoundingBox BB;
    BB.min = m_lowerBound;
    BB.max = m_upperBound;
    return BB;
}

// --------------------------------------- INSTANCED SHAPE GRID

InstancedShapeGrid::InstancedShapeGrid(OpenGLContext *context)
    : InstancedShapeGrid(context, {0.1, 0.1, 0.1}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f})

{}

InstancedShapeGrid::InstancedShapeGrid(OpenGLContext *context, glm::vec3 res, glm::vec3 lower, glm::vec3 upper, float spacing)
    : Mesh(context, lower, upper), shape(InstancedShape::CUBE), OBJfilename(""), res(res), spacing(spacing)
{
    std::cout << "\nMaking InstancedShapeGrid with..." << std::endl;
    std::cout << "resolution: (" << res.x << ", " << res.y << ", " << res.z << ")" << std::endl;
    std::cout << "low bound : (" << lower.x << ", " << lower.y << ", " << lower.z << ")" << std::endl;
    std::cout << "high bound: (" << upper.x << ", " << upper.y << ", " << upper.z << ")\n" << std::endl;
}

InstancedShapeGrid::~InstancedShapeGrid() {}

void InstancedShapeGrid::create()
{
    updateSingularData();
    updateInstancedData();
}

void InstancedShapeGrid::setShape(InstancedShape s, std::string filename)
{
    shape = s;
    OBJfilename = filename;
}

void InstancedShapeGrid::scaleData2Res(VBOvectors &gl)
{
    glm::vec3 min = glm::vec3(std::numeric_limits<float>::max());
    glm::vec3 max = glm::vec3(std::numeric_limits<float>::min());

    for (int i = 0; i < 2; i++)
    {
        for (auto &p : gl.pos)
        {
            switch(i)
            {
            case 0:
                for (int t = 0; t < 3; t++)
                {
                    min[t] = glm::min(min[t], p[t]);
                    max[t] = glm::max(max[t], p[t]);
                } break;

            case 1:
                p = glm::vec4(res * (glm::vec3(p.x, p.y, p.z) - min) / (max - min), 1.0);
                break;
            }
        }
    }
}

void InstancedShapeGrid::updateSingularData()
{
    VBOvectors gl;

    switch (shape)
    {
        case InstancedShape::OBJ:
            if (OBJfilename != "") {
                createSingleShapeFromOBJ(OBJfilename.c_str(), gl, nullptr, nullptr);
                scaleData2Res(gl);
            }
            else {
                std::cout << "OBJ filepath is undefined! made CubeGrid instead!!!" << std::endl;
                createBoundCube(gl, {0.f, 0.f, 0.f}, {res.x, res.y, res.z}, false, false);
            }
            break;

        default:
            createBoundCube(gl, {0.f, 0.f, 0.f}, {res.x, res.y, res.z}, false, false);
    }
    createVBOdata(gl);
}

void InstancedShapeGrid::updateInstancedData()
{
    VBOvectors gl;

    // find number of instances total
    glm::vec3 occupiedSpace = res * glm::vec3(1.f + spacing);
    glm::vec3 diff = m_upperBound - m_lowerBound;
    glm::ivec3 gridDims({std::ceil(diff.x/occupiedSpace.x),
                         std::ceil(diff.y/occupiedSpace.y),
                         std::ceil(diff.z/occupiedSpace.z)});

    m_numInstances = gridDims.x * gridDims.y * gridDims.z;

    for (int x = 0; x < gridDims.x; x++)
    {
        for (int y = 0; y < gridDims.y; y++)
        {
            for (int z = 0; z < gridDims.z; z++)
            {
                glm::vec3 amount = m_lowerBound + glm::vec3(x, y, z) * (1.f + spacing) * res ;
                gl.ioff.push_back(amount);
                gl.icol.push_back({(float)x/gridDims.x, (float)y/gridDims.y, (float)z/gridDims.z});
            }
        }
    }
    createInstancedVBOdata(gl);
}

glm::vec3 InstancedShapeGrid::getResolution() const
{
    return res;
}

void InstancedShapeGrid::setResolution(glm::vec3 newRes)
{
    res = newRes;
}

void InstancedShapeGrid::setSpacing(float newSpace)
{
    spacing = newSpace;
}

void InstancedShapeGrid::setBounds(glm::vec3 lower, glm::vec3 upper)
{
    m_lowerBound = lower;
    m_upperBound = upper;
}

// --------------------------------------- OLD
InstancedCubeGrid::InstancedCubeGrid(OpenGLContext *context)
    : InstancedCubeGrid(context, {0.1, 0.1, 0.1}, {0.f, 0.f, 0.f}, {1.f, 1.f, 1.f})

{}

InstancedCubeGrid::InstancedCubeGrid(OpenGLContext *context, glm::vec3 res, glm::vec3 lower, glm::vec3 upper, float spacing)
    : Mesh(context, lower, upper), res(res), spacing(spacing)
{
    std::cout << "\nMaking InstancedCubeGrid with..." << std::endl;
    std::cout << "resolution: (" << res.x << ", " << res.y << ", " << res.z << ")" << std::endl;
    std::cout << "low bound : (" << lower.x << ", " << lower.y << ", " << lower.z << ")" << std::endl;
    std::cout << "high bound: (" << upper.x << ", " << upper.y << ", " << upper.z << ")\n" << std::endl;
}

InstancedCubeGrid::~InstancedCubeGrid()
{}

void InstancedCubeGrid::create()
{
    updateSingularData();
    updateInstancedData();
}

void InstancedCubeGrid::updateSingularData()
{
    VBOvectors gl;
    createBoundCube(gl, {0.f, 0.f, 0.f}, {res.x, res.y, res.z}, false, false);
    createVBOdata(gl);
}

void InstancedCubeGrid::updateInstancedData()
{
    VBOvectors gl;

    // find number of instances total
    glm::vec3 occupiedSpace = res * glm::vec3(1.f + spacing);
    glm::vec3 diff = m_upperBound - m_lowerBound;
    glm::ivec3 gridDims({std::ceil(diff.x/occupiedSpace.x),
                         std::ceil(diff.y/occupiedSpace.y),
                         std::ceil(diff.z/occupiedSpace.z)});

    m_numInstances = gridDims.x * gridDims.y * gridDims.z;

    for (int x = 0; x < gridDims.x; x++)
    {
        for (int y = 0; y < gridDims.y; y++)
        {
            for (int z = 0; z < gridDims.z; z++)
            {
                glm::vec3 amount = m_lowerBound + glm::vec3(x, y, z) * (1.f + spacing) * res ;
                gl.ioff.push_back(amount);
                gl.icol.push_back({(float)x/gridDims.x, (float)y/gridDims.y, (float)z/gridDims.z});
            }
        }
    }
    createInstancedVBOdata(gl);
}

glm::vec3 InstancedCubeGrid::getResolution() const
{
    return res;
}

void InstancedCubeGrid::setResolution(glm::vec3 newRes)
{
    res = newRes;
}

void InstancedCubeGrid::setSpacing(float newSpace)
{
    spacing = newSpace;
}

void InstancedCubeGrid::setBounds(glm::vec3 lower, glm::vec3 upper)
{
    m_lowerBound = lower;
    m_upperBound = upper;
}
