#include "mygl.h"
#include <la.h>
#include <QResizeEvent>
#include <iostream>


MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      m_geomQuad(this), m_camera(640, 480, glm::vec3(0, 0, 12), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)),
      m_surfaceShaders(), m_postprocessShaders(), m_postsurfaceShaders(),
      usePostSurfaceShaders(false),
      mp_progSurfaceCurrent(nullptr),
      mp_progPostprocessCurrent(nullptr),
      mp_progPostSurfaceCurrent(nullptr),
      mp_modelCurrent(nullptr), mp_instancedgridCurrent(nullptr),
      m_matcapTextures(), mp_matcapTexCurrent(nullptr),
      m_frameBuffer(-1),
      m_renderedTexture(-1),
      m_depthRenderBuffer(-1),
      m_secondaryframeBuffer(-1),
      m_secondaryrenderedTexture(-1),
      m_secondarydepthRenderBuffer(-1),
      m_depthTexture(-1), m_secondarydepthTexture(-1),
      m_time(0.f), m_pausetime(0.f), m_mousePosPrev(),
      m_seethroughIGrid(false), m_rotateModels(false)
{
    m_commonModelTransform = glm::mat4(); // Identity Matrix
    setFocusPolicy(Qt::StrongFocus);
}

MyGL::~MyGL()
{
    makeCurrent();

    glDeleteVertexArrays(1, &m_vao);
    m_geomQuad.destroy();
}

void MyGL::initializeGL()
{    
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();

    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &m_vao);

    createRenderBuffers();

    m_geomQuad.create();

    createShaders();
    createMeshes();
    createMatcapTextures();

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(m_vao);
}

void MyGL::resizeGL(int w, int h)
{
    mp_progSurfaceCurrent->setViewProjMatrix(m_camera.getView(), m_camera.getProj());

    for(std::shared_ptr<PostProcessShader> p : m_postprocessShaders)
    {
        p->setDimensions(glm::ivec2(w * this->devicePixelRatio(), h * this->devicePixelRatio()));
    }
    for(std::shared_ptr<PostSurfaceShader> p : m_postsurfaceShaders)
    {
        p->setDimensions(glm::ivec2(w * this->devicePixelRatio(), h * this->devicePixelRatio()));
    }

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function update() is called, paintGL is called implicitly.
void MyGL::paintGL()
{

    if (m_rotateModels) {
        float rad = (float)m_pausetime / 2.f;
        m_commonModelTransform = glm::rotate(glm::mat4(), rad, glm::vec3(0.0f, 1.0f, 0.0f));
        m_pausetime++;
    }
    mp_progSurfaceCurrent->setCameraPos(m_camera.eye);
    render3DScene();

    if (usePostSurfaceShaders && !mp_modelCurrent->isInstanced()) {
        renderPostSurfacePass();
    }

    performPostprocessRenderPass();

    mp_progSurfaceCurrent->setTime(m_time);
    mp_progPostprocessCurrent->setTime(m_time);
    mp_progPostSurfaceCurrent->setTime(m_time);
    m_time++;

}

void MyGL::render3DScene()
{
    // Render the 3D scene to our frame buffer

    // Render to our framebuffer rather than the viewport
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glViewport(0,0,this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDepthMask(GL_TRUE);
    // Set the surface shader's transformation matrices
    mp_progSurfaceCurrent->setViewProjMatrix(m_camera.getView(), m_camera.getProj());
    mp_progSurfaceCurrent->setModelMatrix(m_commonModelTransform);

    // if model is instanced model, use drawInstanced()
    if (mp_modelCurrent->isInstanced()) {
        mp_progSurfaceCurrent->drawInstanced(*mp_modelCurrent);
        return;
    }

    // Draw Model
    // Draw the background texture first
    if (!usePostSurfaceShaders) {
        mp_modelCurrent->bindBGTexture();
        mp_progPostprocessNoOp->draw(m_geomQuad, 2);
    }
    bindAppropriateTexture();

    mp_progSurfaceCurrent->draw(*mp_modelCurrent, 0);
}

void MyGL::renderPostSurfacePass()
{

    glActiveTexture(GL_TEXTURE0);
    if (m_seethroughIGrid) {
        glBindTexture(GL_TEXTURE_2D, mp_modelCurrent->getBGtexture()->getTextureHandle());
    }
    else {
        glBindTexture(GL_TEXTURE_2D, m_renderedTexture);
    }

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);

    // Render to our framebuffer rather than the viewport
    glBindFramebuffer(GL_FRAMEBUFFER, m_secondaryframeBuffer);
    // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glViewport(0,0,this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mp_modelCurrent->bindBGTexture();
    mp_progPostprocessNoOp->draw(m_geomQuad, 2);

    mp_progPostSurfaceCurrent->setViewProjMatrix(m_camera.getView(), m_camera.getProj());
    mp_progPostSurfaceCurrent->setModelMatrix(glm::mat4());

//    glDepthMask(GL_FALSE); // disable depth buffer writing
    mp_progPostSurfaceCurrent->drawInstanced(*mp_instancedgridCurrent);
//    glDepthMask(GL_TRUE); // enable depth buffer writing
}

void MyGL::performPostprocessRenderPass()
{
    // Render the frame buffer as a texture on a screen-size quad

    // Tell OpenGL to render to the viewport's frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, this->defaultFramebufferObject());
    // Render on the whole framebuffer, complete from the lower left corner to the upper right
    glViewport(0,0,this->width() * this->devicePixelRatio(), this->height() * this->devicePixelRatio());
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Bind our texture in Texture Unit 0
    glActiveTexture(GL_TEXTURE0);
    usePostSurfaceShaders ? glBindTexture(GL_TEXTURE_2D, m_secondaryrenderedTexture):
                            glBindTexture(GL_TEXTURE_2D, m_renderedTexture);
    glActiveTexture(GL_TEXTURE1);
    usePostSurfaceShaders ? glBindTexture(GL_TEXTURE_2D, m_secondarydepthTexture):
                            glBindTexture(GL_TEXTURE_2D, m_depthTexture);

    mp_progPostprocessCurrent->draw(m_geomQuad, 0);
}

void MyGL::createRenderBuffers()
{
    double w = this->width() * this->devicePixelRatio();
    double h = this->height() * this->devicePixelRatio();

    // ----- RENDER TEXTURE -----
    glGenTextures(1, &m_renderedTexture);
    // Bind our texture so that all functions that deal with textures will interact with this one
    glBindTexture(GL_TEXTURE_2D, m_renderedTexture);
    // Give an empty image to OpenGL ( the last "0" )
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
    // Set the render settings for the texture we've just created.
    // Essentially zero filtering on the "texture" so it appears exactly as rendered
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // Clamp the colors at the edge of our texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // ----- DEPTH TEXTURE -----
    glGenTextures(1, &m_depthTexture);
    glBindTexture(GL_TEXTURE_2D, m_depthTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // ----- SECOND RENDER TEXTURE -----
    glGenTextures(1, &m_secondaryrenderedTexture);
    glBindTexture(GL_TEXTURE_2D, m_secondaryrenderedTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // ----- SECOND DEPTH TEXTURE -----
    glGenTextures(1, &m_secondarydepthTexture);
    glBindTexture(GL_TEXTURE_2D, m_secondarydepthTexture);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, w, h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


    // Initialize the frame buffers and render textures
    glGenFramebuffers(1, &m_frameBuffer);
    glGenFramebuffers(1, &m_secondaryframeBuffer);
    glGenRenderbuffers(1, &m_depthRenderBuffer);
    glGenRenderbuffers(1, &m_secondarydepthRenderBuffer);

    // ----- SECONDARY FB -----
    glBindFramebuffer(GL_FRAMEBUFFER, m_secondaryframeBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_secondaryrenderedTexture, 0);

    // Initialize our depth buffer
    glBindRenderbuffer(GL_RENDERBUFFER, m_secondarydepthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_secondarydepthRenderBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT , GL_TEXTURE_2D, m_secondarydepthTexture   , 0);

    GLenum secondarydrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, secondarydrawBuffers); // "1" is the size of drawBuffers

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Frame buffer did not initialize correctly..." << std::endl;
        printGLErrorLog();
    }

    // ----- FIRST FB -----
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    // Initialize our depth buffer
    glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBuffer);

    // Set m_renderedTexture as the color output of our frame buffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_renderedTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT , GL_TEXTURE_2D, m_depthTexture   , 0);

    // Sets the color output of the fragment shader to be stored in GL_COLOR_ATTACHMENT0, which we previously set to m_renderedTextures[i]
    GLenum drawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, drawBuffers); // "1" is the size of drawBuffers

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Frame buffer did not initialize correctly..." << std::endl;
        printGLErrorLog();
    }

}

void MyGL::createShaders()
{
    // Surface shaders
    std::shared_ptr<SurfaceShader> lambert = std::make_shared<SurfaceShader>(this);
    lambert->create(":/glsl/surface/lambert.vert.glsl", ":/glsl/surface/lambert.frag.glsl");
    m_surfaceShaders.push_back(lambert);

    std::shared_ptr<SurfaceShader> blinnPhong = std::make_shared<SurfaceShader>(this);
    blinnPhong->create(":/glsl/surface/blinnPhong.vert.glsl", ":/glsl/surface/blinnPhong.frag.glsl");
    m_surfaceShaders.push_back(blinnPhong);

    std::shared_ptr<SurfaceShader> matcap = std::make_shared<SurfaceShader>(this);
    matcap->create(":/glsl/surface/matcap.vert.glsl", ":/glsl/surface/matcap.frag.glsl");
    m_surfaceShaders.push_back(matcap);

    std::shared_ptr<SurfaceShader> gradient = std::make_shared<SurfaceShader>(this);
    gradient->create(":/glsl/surface/gradient.vert.glsl", ":/glsl/surface/gradient.frag.glsl");
    m_surfaceShaders.push_back(gradient);

    std::shared_ptr<SurfaceShader> deform = std::make_shared<SurfaceShader>(this);
    deform->create(":/glsl/surface/deform.vert.glsl", ":/glsl/surface/deform.frag.glsl");
    m_surfaceShaders.push_back(deform);

    std::shared_ptr<SurfaceShader> instanced = std::make_shared<SurfaceShader>(this);
    instanced->create(":/glsl/surface/instanced.vert.glsl", ":/glsl/surface/instanced.frag.glsl");
    m_surfaceShaders.push_back(instanced);

    slot_setCurrentSurfaceShaderProgram(0);

    // Post-process shaders
    std::shared_ptr<PostProcessShader> noOp = std::make_shared<PostProcessShader>(this);
    noOp->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/noOp.frag.glsl");
    m_postprocessShaders.push_back(noOp);

    std::shared_ptr<PostProcessShader> greyscale = std::make_shared<PostProcessShader>(this);
    greyscale->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/greyscale.frag.glsl");
    m_postprocessShaders.push_back(greyscale);

    std::shared_ptr<PostProcessShader> gaussian = std::make_shared<PostProcessShader>(this);
    gaussian->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/gaussian.frag.glsl");
    m_postprocessShaders.push_back(gaussian);

    std::shared_ptr<PostProcessShader> sobel = std::make_shared<PostProcessShader>(this);
    sobel->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/sobel.frag.glsl");
    m_postprocessShaders.push_back(sobel);

    std::shared_ptr<PostProcessShader> bloom = std::make_shared<PostProcessShader>(this);
    bloom->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/bloom.frag.glsl");
    m_postprocessShaders.push_back(bloom);

    std::shared_ptr<PostProcessShader> worley = std::make_shared<PostProcessShader>(this);
    worley->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/worleywarp.frag.glsl");
    m_postprocessShaders.push_back(worley);

    std::shared_ptr<PostProcessShader> fastworley = std::make_shared<PostProcessShader>(this);
    fastworley->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/fastworley.frag.glsl");
    m_postprocessShaders.push_back(fastworley);

    std::shared_ptr<PostProcessShader> depth = std::make_shared<PostProcessShader>(this);
    depth->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/depth.frag.glsl");
    m_postprocessShaders.push_back(depth);

    std::shared_ptr<PostProcessShader> fbm = std::make_shared<PostProcessShader>(this);
    fbm->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/fbm.frag.glsl");
    m_postprocessShaders.push_back(fbm);

    std::shared_ptr<PostProcessShader> testfbm = std::make_shared<PostProcessShader>(this);
    testfbm->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/testfbm.frag.glsl");
    m_postprocessShaders.push_back(testfbm);

    std::shared_ptr<PostProcessShader> perlin = std::make_shared<PostProcessShader>(this);
    perlin->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/perlin.frag.glsl");
    m_postprocessShaders.push_back(perlin);

    std::shared_ptr<PostProcessShader> perlinfbm = std::make_shared<PostProcessShader>(this);
    perlinfbm->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/perlinfbm.frag.glsl");
    m_postprocessShaders.push_back(perlinfbm);

    slot_setCurrentPostprocessShaderProgram(0);
    mp_progPostprocessNoOp = m_postprocessShaders[0].get();

    // Post-Surface Shaders (in between post-and surface and still require a vertex shader component for rendering instanced cubes)
    std::shared_ptr<PostSurfaceShader> none = std::make_shared<PostSurfaceShader>(this);
    none->create(":/glsl/post/passthrough.vert.glsl", ":/glsl/post/noOp.frag.glsl");
    m_postsurfaceShaders.push_back(none);

    std::shared_ptr<PostSurfaceShader> igrid = std::make_shared<PostSurfaceShader>(this);
    igrid->create(":/glsl/postsurface/instancedcubes.vert.glsl", ":/glsl/postsurface/instancedcubes.frag.glsl");
    m_postsurfaceShaders.push_back(igrid);

    slot_setCurrentPostSurfaceShaderProgram(0);

}

void MyGL::createMeshes()
{
    std::shared_ptr<Mesh> wahoo = std::make_shared<Mesh>(this);
    wahoo->createFromOBJ(":/objs/wahoo.obj", ":/textures/wahoo.bmp", ":/textures/mario_movie.jpg");
    wahoo->loadTexture();
    wahoo->loadBGTexture();
    m_models.push_back(wahoo);

    std::shared_ptr<Mesh> cow = std::make_shared<Mesh>(this);
    cow->createFromOBJ(":/objs/cow.obj", ":/textures/uvTest.jpg", ":/textures/winxp.jpg");
    cow->loadTexture();
    cow->loadBGTexture();
    m_models.push_back(cow);

    std::shared_ptr<Mesh> minecraft = std::make_shared<Mesh>(this);
    minecraft->createFromOBJ(":/objs/Grass_block.obj", ":/textures/All_blocks.png", ":/textures/jungle.jpg");
    minecraft->loadTexture();
    minecraft->loadBGTexture();
    m_models.push_back(minecraft);

    std::shared_ptr<Mesh> sammy = std::make_shared<Mesh>(this);
    sammy->createFromOBJ(":/objs/Sammy.obj", ":/textures/Sammy.JPEG", ":/textures/winxp.jpg");
    sammy->loadTexture();
    sammy->loadBGTexture();
    m_models.push_back(sammy);

    std::shared_ptr<Mesh> cube = std::make_shared<Mesh>(this);
    cube->createCube(":/textures/fractal.jpg", ":/textures/mengersponge.jpg");
    cube->loadTexture();
    cube->loadBGTexture();
    m_models.push_back(cube);

    slot_setCurrentModel(0);

    // Create & add InstancedCubeGrid to vector for display with "instanced" SurfaceShader
    glm::vec3 resolution({0.15f, 0.15f, 0.15f});
    BoundingBox bb = mp_modelCurrent->getBoundingBox();
    float xzMin = glm::min(bb.min.x, bb.min.z);
    float xzMax = glm::max(bb.max.x, bb.max.z);
    glm::vec3 lowerBound(glm::vec3(xzMin, bb.min.y, xzMin));
    glm::vec3 upperBound(glm::vec3(xzMax, bb.max.y, xzMax));

    std::shared_ptr<InstancedShapeGrid> icubes = std::make_shared<InstancedShapeGrid>(this, resolution, lowerBound, upperBound);
    icubes->create();
    m_models.push_back(icubes);
    m_instancedgrids.push_back(icubes);

    std::shared_ptr<InstancedShapeGrid> ispheres = std::make_shared<InstancedShapeGrid>(this, resolution, lowerBound, upperBound);
    ispheres->setShape(InstancedShape::OBJ, ":/objs/icosphere.obj");
    ispheres->create();
    m_models.push_back(ispheres);
    m_instancedgrids.push_back(ispheres);

    std::shared_ptr<InstancedShapeGrid> imonkey = std::make_shared<InstancedShapeGrid>(this, resolution, lowerBound, upperBound);
    imonkey->setShape(InstancedShape::OBJ, ":/objs/monkey.obj");
    imonkey->create();
    m_models.push_back(imonkey);
    m_instancedgrids.push_back(imonkey);

    mp_instancedgridCurrent = m_instancedgrids[0].get();

    for (auto &psshader : m_postsurfaceShaders) {
        psshader->setInstanceResolution(resolution);
    }
}

void MyGL::createMatcapTextures()
{
    std::shared_ptr<Texture> zbrush = std::make_shared<Texture>(this);
    zbrush->create(":/textures/matcaps/00ZBrush_RedWax.png");
    m_matcapTextures.push_back(zbrush);

    std::shared_ptr<Texture> redPlastic = std::make_shared<Texture>(this);
    redPlastic->create(":/textures/matcaps/JG_Red.png");
    m_matcapTextures.push_back(redPlastic);

    std::shared_ptr<Texture> chrome = std::make_shared<Texture>(this);
    chrome->create(":/textures/matcaps/silver.jpg");
    m_matcapTextures.push_back(chrome);

    std::shared_ptr<Texture> pearl = std::make_shared<Texture>(this);
    pearl->create(":/textures/matcaps/pearl.jpg");
    m_matcapTextures.push_back(pearl);

    std::shared_ptr<Texture> orangeGreen = std::make_shared<Texture>(this);
    orangeGreen->create(":/textures/matcaps/JGSpecial_01.png");
    m_matcapTextures.push_back(orangeGreen);

    std::shared_ptr<Texture> blurple = std::make_shared<Texture>(this);
    blurple->create(":/textures/matcaps/Shiny_Fire_1c.png");
    m_matcapTextures.push_back(blurple);

    std::shared_ptr<Texture> outline = std::make_shared<Texture>(this);
    outline->create(":/textures/matcaps/Outline.png");
    m_matcapTextures.push_back(outline);

    std::shared_ptr<Texture> normals = std::make_shared<Texture>(this);
    normals->create(":/textures/matcaps/normals.jpg");
    m_matcapTextures.push_back(normals);

    // If this vector of textures were to be altered
    // while the program was running, storing a pointer
    // to an element within it would be bad news, since
    // the elements inside would not be guaranteed to be
    // in the same memory as before.
    // However, this vector's contents are only ever modified
    // in this function, which is called exactly once in the
    // program's lifetime.

    slot_setCurrentMatcapTexture(0);
}

void MyGL::bindAppropriateTexture()
{
    // Matcap
    if(mp_progSurfaceCurrent == m_surfaceShaders[2].get())
    {
        mp_matcapTexCurrent->bind(0);
    }
    // Default case, use the texture provided by the model to be rendered
    else
    {
        mp_modelCurrent->bindTexture();
    }
}
