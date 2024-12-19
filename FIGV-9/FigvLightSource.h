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

#ifndef FigvLightSource_h
#define FigvLightSource_h

#include <glm/vec3.hpp>
#include "FigvShader.h"

struct FigvLightSource {
public:
    
    FigvLightSource();
    FigvLightSource(glm::vec3 Id, glm::vec3 Is) : Id(Id), Is(Is) {}
    
    float* getId3fp();
    float* getIs3fp();
    
    glm::vec3 getPositionv();
    float* getPosition3fp();
    
    void applyPositionToShader(FigvShader shader);
    void applyIntensityToShader(FigvShader shader);

private:
    glm::vec3 position = glm::vec3(4.0, 8.0, 12.0);
    glm::vec3 Id = glm::vec3(0.8f);
    glm::vec3 Is = glm::vec3(1.0f);
};

#endif /* FigvLightSource_h */
