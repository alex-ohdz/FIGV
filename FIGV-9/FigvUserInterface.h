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

#ifndef FigvUserInterface_h
#define FigvUserInterface_h

#include <GLFW/glfw3.h>

class FigvUserInterface {
    
public:

    explicit FigvUserInterface(GLFWwindow* associatedWindow);
    ~FigvUserInterface();

    void preRenderActions();
    void afterRenderActions();
    void prepareInterfaceObjects();

private:
    
    GLFWwindow* associatedWindow;
    const char* glsl_version;
    
    bool darkMode;

    void preparePalettes();
};

#endif /* FigvUserInterface_h */
