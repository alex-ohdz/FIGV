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
#include <glm/gtc/type_ptr.hpp>
#include "FigvLightSource.h"

FigvLightSource::FigvLightSource() {}

float* FigvLightSource::getId3fp() {
    return glm::value_ptr(Id);
}

float* FigvLightSource::getIs3fp() {
    return glm::value_ptr(Is);
}

glm::vec3 FigvLightSource::getPositionv() {
    return position;
}

float* FigvLightSource::getPosition3fp() {
    return glm::value_ptr(position);
}

void FigvLightSource::applyPositionToShader(FigvShader shader) {
    shader.set("lightPosition", position);
}

void FigvLightSource::applyIntensityToShader(FigvShader shader) {
    shader.set("Id", Id);
    shader.set("Is", Is);
}
