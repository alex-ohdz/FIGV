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

#ifndef FigvEventManager_h
#define FigvEventManager_h

#include <GLFW/glfw3.h>
#include "FigvCamera.h"

class FigvEventManager {
    
public:
    
    static FigvEventManager *getInstance();
    CameraMode* getCameraMovementip();
    
    static void processMouseClics(GLFWwindow* window, int button, int action, int mods);
    static void processMouseScroll(double yDisplacement);
    static void processCursorPosition(double xPos, double yPos);
    
private:
    
    FigvEventManager();
    static FigvEventManager* instance;

    CameraMode cameraMovement=ORBIT;
    bool dragging=false;
    double lastX=0.0, lastY=0.0;

    void mouseClics(GLFWwindow* window, int button, int action, int mods);
    void mouseScroll(double yDisplacement);
    void cursorPosition(double xPos, double yPos);
};

#endif /* FigvEventManager_h */
