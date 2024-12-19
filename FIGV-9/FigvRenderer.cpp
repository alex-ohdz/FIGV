//
// FIGV (Fundamentos de Informática Gráfica y Visualización)
// Master en Desarrollo de Software, Universidad de Granada.
//
// Juan Carlos Torres Cantero
// ETSIIT, Depto. Lenguajes y Sistemas Informáticos, Universidad de Granada, jctorres@ugr.es
//
// Francisco de Asís Conde Rodríguez
// EPS, Depto. Informática, Universidad de Jaén, fconde@ujaen.es
//

#include <glad/glad.h>
#include "FigvRenderer.h"
#include "FigvAuxiliaryFunctions.h"
#include "FigvScene.h"
#include <glm/gtc/type_ptr.hpp>

FigvRenderer* FigvRenderer::instance = NULL;

FigvRenderer::FigvRenderer() {
    
    FigvLog("FigvRenderer", __LINE__, "Initializing the renderer");
    
    background = glm::vec4(0.45f, 0.55f, 0.60f, 1.00f);
    renderingMode = GL_FILL;
    pointSize = 4.0;
    
    shaderActive = 0;
    shaders.push_back(new FigvShader("./shaders/FigvNormalVertex.glsl",
                                     "./shaders/FigvNormalFragment.glsl"));
    shaders.push_back(new FigvShader("./shaders/FigvCartoonVertex.glsl",
                                     "./shaders/FigvCartoonFragment.glsl"));

    scaledNormal = false;
    
    // FIGV 18
    useTexture = true;
}

FigvRenderer::~FigvRenderer() {
    
    FigvLog("FigvRenderer", __LINE__, "Destroying the renderer");
}

FigvRenderer *FigvRenderer::getInstance() {
    if (!instance) { instance = new FigvRenderer(); }
    return instance;
}

void FigvRenderer::renderScene() {
    getInstance()->render();
}

void FigvRenderer::render() {

    glClearColor(background[0], background[1], background[2], background[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_MULTISAMPLE);
    
    glPolygonMode(GL_FRONT_AND_BACK, renderingMode);
    if (renderingMode == GL_POINT) {
        glPointSize(pointSize);
    }
    
    getInstance()->shaders[shaderActive]->use();
    
    switch (shaderActive) {
            
        case 0:
            getInstance()->shaders[shaderActive]->set("scaled", scaledNormal);
            break;
            
        case 1:
            FigvScene::applyLightSources(*getInstance()->shaders[shaderActive]);
            FigvScene::applyCameraPosition(*getInstance()->shaders[shaderActive]);
            getInstance()->shaders[shaderActive]->set("solidColor", cartoonSolidColor);
            getInstance()->shaders[shaderActive]->set("levels", cartoonLevels);
            getInstance()->shaders[shaderActive]->set("multiplier", cartoonMultiplier);
            getInstance()->shaders[shaderActive]->set("threshold", cartoonThreshold);
            // FIGV 19
            getInstance()->shaders[shaderActive]->set("useTexture", useTexture);
            break;
            
        default:
            break;
    }
    
    FigvScene::drawScene(*getInstance()->shaders[shaderActive]);
}

float* FigvRenderer::getBackgroundColor3fp() {
    return glm::value_ptr(background);
}

int* FigvRenderer::getRenderingModeip() {
    return &renderingMode;
}

float* FigvRenderer::getPointSizefp() {
    return &pointSize;
}

int* FigvRenderer::getShaderActiveip() {
    return &shaderActive;
}

bool* FigvRenderer::getScaledNormalbp() {
    return &scaledNormal;
}

bool* FigvRenderer::getCartoonSolidColorbp() {
    return &cartoonSolidColor;
}

int* FigvRenderer::getCartoonLevelsip() {
    return &cartoonLevels;
}

float* FigvRenderer::getCartoonMultiplierfp() {
    return &cartoonMultiplier;
}

float* FigvRenderer::getCartoonThresholdfp() {
    return &cartoonThreshold;
}

// FIGV 20
bool* FigvRenderer::getUseTexturebp() {
    return &useTexture;
}
