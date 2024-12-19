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

#ifndef FigvCamera_h
#define FigvCamera_h

#include <glm/glm.hpp>
enum CameraMode {
    ORBIT,
    PAN,
    DOLLY,
    TRACK,
    ZOOM
};
class FigvCamera {
    
public:

    FigvCamera();

    void orbit(float movementX, float movementY);
    void pan(float movementX, float movementY);
    void dolly(float distance);
    void track(float deltaX, float deltaY);
    void zoom(float deltaFov);
    glm::mat4 getViewProjectionMatrix();
    glm::vec3 getPosition();

    
    void setMode(CameraMode mode){ modeC=mode;}
    void setAspect(int width, int height);

private:
    
    glm::vec3 position;
    glm::vec3 lookAt;
    float aspect;
    float fovX;
    float zNear;
    float zFar;

    glm::vec3 vU;
    glm::vec3 vV;
    glm::vec3 vN;

    CameraMode modeC;

    void calculateVectors();
};
#endif /* FigvCamera_h */
