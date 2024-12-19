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

#ifndef FigvMesh_h
#define FigvMesh_h

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

struct FigvVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class FigvMesh {
    
public:
    
    FigvMesh(std::vector<FigvVertex> vertices,
             std::vector<unsigned int> indices);

    void draw();

private:
    
    std::vector<FigvVertex> vertices;
    std::vector<unsigned int> indices;
    
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
};
#endif /* FigvMesh_h */
