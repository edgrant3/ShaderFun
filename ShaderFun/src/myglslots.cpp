#include "mygl.h"
#include <iostream>

void MyGL::slot_setCurrentSurfaceShaderProgram(int s)
{
    std::cout << "Surface Shader #" << s << std::endl;
    mp_progSurfaceCurrent = m_surfaceShaders[s].get();
}

void MyGL::slot_setCurrentPostprocessShaderProgram(int s)
{
    std::cout << "Post-Process Shader #" << s << std::endl;
    mp_progPostprocessCurrent = m_postprocessShaders[s].get();
}

void MyGL::slot_setCurrentPostSurfaceShaderProgram(int s)
{
    std::cout << "Post-Surface Shader #" << s << std::endl;
    usePostSurfaceShaders = (s != 0);
    mp_progPostSurfaceCurrent = m_postsurfaceShaders[1].get();
    if (!m_instancedgrids.empty()) {
        mp_instancedgridCurrent = m_instancedgrids[glm::max(0, s -1)].get();
    }
}

void MyGL::slot_setCurrentModel(int m)
{
    mp_modelCurrent = (m_models[m]).get();

    if (mp_modelCurrent->isInstanced()) {
        std::cout << "\nSelected Mesh is Instanced" << std::endl;
        std::cout << "and has " << mp_modelCurrent->instanceCount() << " instances" << std::endl;
    }
    else {

        std::cout << "\nSelected Mesh is NOT Instanced" << std::endl;
        for (auto &igrid : m_instancedgrids) {
            if (igrid != nullptr) {
                BoundingBox bb = mp_modelCurrent->getBoundingBox();
                float xzMin = glm::min(bb.min.x, bb.min.z);
                float xzMax = glm::max(bb.max.x, bb.max.z);
                bb.min = {xzMin, bb.min.y, xzMin};
                bb.max ={xzMax, bb.max.y, xzMax};
                glm::vec3 pDiff = glm::vec3(0.1) * (bb.max - bb.min);
                igrid->setBounds(bb.min - pDiff, bb.max + pDiff);
                igrid->updateInstancedData();
            }
        }
    }

}

void MyGL::slot_setCurrentMatcapTexture(int t)
{
    mp_matcapTexCurrent = (m_matcapTextures[t]).get();
    mp_matcapTexCurrent->load(0);
}

void MyGL::slot_setInstancedGridRes(double res)
{
    for (auto &igrid : m_instancedgrids) {
        igrid->setResolution(glm::vec3(res));
        igrid->create();
    }
}

void MyGL::slot_setInstancedGridSpacing(int spacePercent)
{
    for (auto &igrid : m_instancedgrids) {

        float spaceDecimal = (float)spacePercent / 100.0;
        igrid->setSpacing(spaceDecimal);
        igrid->updateInstancedData();
    }
}

void MyGL::slot_makeIGridSeethrough(int s)
{
    m_seethroughIGrid = s;
}

void MyGL::slot_shadeIGridLambert(int s)
{
    std::cout << "Toggling InstancedGrid Shading b/w FLat and Lambert" << std::endl;
    for (auto& pss : m_postsurfaceShaders) {
        pss->setShadeLambert(s);
    }
}

void MyGL::slot_setModelRotationFLag(int s)
{
    m_rotateModels = s;
}


