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

#pragma once

#ifndef FigvScene_h
#define FigvScene_h

#include "FigvShader.h"
#include "FigvCamera.h"
#include "Figv3DModel.h"
#include "FigvLightSource.h"

class FigvScene {
    
public:

    ~FigvScene();

    static FigvScene* getInstance();

    static void orbitCamera(float movementX, float movementY);
    static void panCamera(float movementX, float movementY);
    static void dollyCamera(float distance);
    static void trackCamera(float deltaX,float deltaY);
    static void zoomCamera(float deltaFov);
    static void applyCameraPosition(FigvShader shader);

    static void drawScene(FigvShader shader);
    static void setFrameSize(int width, int height);


    float* getIa3fp();
    FigvLightSource* getLightSource();
    int* getUseModelingLightip();
    static void applyLightSources(FigvShader shader);

    
private:
    
    FigvScene();

    static FigvScene *instance;

    FigvCamera* camera;

    std::vector<Figv3DModel> models;
    int modelSelected = 0;

    glm::vec3 Ia = glm::vec3(0.2f);

    bool useModelingLight = true;
    FigvLightSource* lightSource;
};

#endif /* FigvScene_h */
