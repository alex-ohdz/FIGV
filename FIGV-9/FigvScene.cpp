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

#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "FigvScene.h"
#include "FigvAuxiliaryFunctions.h"
#include "Figv3DModel.h"

FigvScene* FigvScene::instance = nullptr;

FigvScene::FigvScene() {
    
    FigvLog("FigvScene", __LINE__, "Initializing the scene");
    
    camera = new FigvCamera();
    models = std::vector<Figv3DModel>();
    
    glm::mat4 R;
    // FIGV 15
    R = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f),glm::vec3(0.0, 1.0, 0.0));
    models.push_back(Figv3DModel("./spot/spot_trg.obj", new FigvMaterial(64.0, glm::vec3(1.0, 0.75, 0.75),glm::vec3(1.0)),"./spot/spot_texture.png",R));
   
    R = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0, 1.0, 0.0));
    models.push_back(Figv3DModel("./bob/bob_trg.obj",new FigvMaterial(),"./bob/bob_diffuse.png",R));
    models.push_back(Figv3DModel("./blub/blub_trg.obj", new FigvMaterial(256.0,glm::vec3(0.4, 0.6, 1.0), glm::vec3(1.0)), "./blub/blub_texture.png",glm::mat4(1.0)));

    R = glm::rotate(glm::mat4(1.0f), glm::radians(180.0f),glm::vec3(0.0, 1.0, 0.0));
    models.push_back(Figv3DModel("./spot/spot_trg_2.obj", new FigvMaterial(64.0,glm::vec3(1.0, 0.75, 0.75), glm::vec3(1.0)), "./spot/spot_texture.png", R));
    models.push_back(Figv3DModel("./blub/blub_trg_2.obj", new FigvMaterial(256.0,glm::vec3(0.4, 0.6, 1.0),glm::vec3(1.0)), "./blub/blub_texture.png", glm::mat4(1.0)));
    
    lightSource = new FigvLightSource();
}

FigvScene::~FigvScene() = default;

FigvScene* FigvScene::getInstance() {
    
    if (!instance) { instance = new FigvScene(); }
    return instance;
}

void FigvScene::orbitCamera(float movementX, float movementY) {
    
    getInstance()->camera->orbit(movementX, movementY);
}

void FigvScene::panCamera(float movementX, float movementY) {
    
    getInstance()->camera->pan(movementX, movementY);
}

void FigvScene::dollyCamera(float distance) {
    
    getInstance()->camera->dolly(distance);
}

void FigvScene::trackCamera(float deltaX,float deltaY) {
    
    getInstance()->camera->track(deltaX,deltaY);
}

void FigvScene::zoomCamera(float deltaFov) {
    
    getInstance()->camera->zoom(deltaFov);
}

void FigvScene::applyCameraPosition(FigvShader shader) {
    
    shader.set("cameraPosition", getInstance()->camera->getPosition());
}

void FigvScene::drawScene(FigvShader shader) {
    
    glm::mat4 viewProj = getInstance()->camera->getViewProjectionMatrix();
    shader.set("mViewProjection", viewProj);
    
    getInstance()->models[FigvScene::getInstance()->modelSelected].draw(shader);
}

void FigvScene::setFrameSize(int width, int height) {
    
    getInstance()->camera->setAspect(width, height);
}

void cargarModelos(const std::string& path, float scale){
    namespace fs=std::filesystem;

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            std::string modelPath = entry.path().string()+ "/source/";
            std::string objFile, textureFile;

            for (const auto& file : fs::directory_iterator(modelPath))
            {
                std::string filePath = file.path().string();
                if (filePath.size()>=4 && filePath.substr(filePath.size()-4) == ".obj")
                {
                    objFile=filePath;
                }else if (filePath.size() >= 4 && (filePath.substr(filePath.size() - 4) == ".png" || filePath.substr(filePath.size() - 4) == ".jpg"))
                {
                    textureFile=filePath;
                }
                
                
            }
            
            //Si objeto y textura existen , se anade el modelo
            if(!objFile.empty() && !textureFile.empty()){
                glm::mat4 R = glm::scale(glm::mat4(1.0f),glm::vec3(scale));
                models.push_back(Figv3DModel(objFile,new FigvMaterial(128.0f,glm::vec3(1.0f),glm::vec3(1.0f)),textureFile,R));
                std::count<<"Modelo cargado:" << objFile << "con textura:" << textureFile << std::endl;
            }
        } 
    } 
}

int FigvScene::getModelSelected() const {
    return modelSelected;
}

void FigvScene::setModelSelected(int index) {
    if (index >= 0 && index < models.size()) { // Verifica que el índice sea válido
        modelSelected = index;
    }
}

void scalaModelos(float scale){
    if(modelSelected >=0 && modelSelected < models.size()){
        // Escala la transformación del modelo seleccionado
        models[modelSelected].setTransformation(glm::scale(models[modelSelected].getTransformation(), glm::vec3(scale)));
    }
}

float* FigvScene::getIa3fp() {
    
    return glm::value_ptr(Ia);
}

FigvLightSource* FigvScene::getLightSource() {
    
    return lightSource;
}

int* FigvScene::getUseModelingLightip() {
    
    return (int*)&useModelingLight;
}

void FigvScene::applyLightSources(FigvShader shader) {
    
    shader.set("Ia", getInstance()->Ia);
    
    getInstance()->lightSource->applyIntensityToShader(shader);
    if (getInstance()->useModelingLight) {
        shader.set("lightPosition", getInstance()->camera->getPosition());
    } else {
        getInstance()->lightSource->applyPositionToShader(shader);
    }
}

int* FigvScene::getModelSelectedip() {
    
    return &modelSelected;
}
