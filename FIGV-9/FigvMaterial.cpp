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
#include "FigvMaterial.h"
#include <glm/gtc/type_ptr.hpp>

FigvMaterial::FigvMaterial() {}

float* FigvMaterial::getShininessfp() {
    return &shininess;
}

float* FigvMaterial::getKdfp() {
    return glm::value_ptr(Kd);
}

float* FigvMaterial::getKsfp() {
    return glm::value_ptr(Ks);
}

void FigvMaterial::applyToShader(FigvShader shader) {
    shader.set("Kd", Kd);
    shader.set("Ks", Ks);
    shader.set("shininess", shininess);
}
