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

#ifndef FigvMaterial_h
#define FigvMaterial_h

#include <glm/vec3.hpp>
#include "FigvShader.h"

struct FigvMaterial {
public:
    FigvMaterial();
    FigvMaterial(float shininess, glm::vec3 Kd, glm::vec3 Ks):
        shininess(shininess), Kd(Kd), Ks(Ks) {}
    
    float* getShininessfp();
    float* getKdfp();
    float* getKsfp();
    
    void applyToShader(FigvShader shader);
    
private:
    float shininess = 64.0f;
    glm::vec3 Kd = glm::vec3(1.0f, 0.75f, 0.25f);
    glm::vec3 Ks = glm::vec3(1.0f);
};

#endif /* FigvMaterial_h */
