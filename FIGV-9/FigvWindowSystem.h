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

#ifndef FigvWindowSystem_h
#define FigvWindowSystem_h

#include <GLFW/glfw3.h>

class FigvWindowSystem {
    
public:
    
    FigvWindowSystem(int width, int height, const char* name);
    
    ~FigvWindowSystem();
    
    GLFWwindow* getAppWindow();

    bool getWindowShouldClose();
    
    void swapBuffers();

private:
    
    GLFWwindow* window;
};

#endif /* FigvWindowSystem_h */
