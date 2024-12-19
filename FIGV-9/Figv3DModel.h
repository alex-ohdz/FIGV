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

#ifndef Figv3DModel_h
#define Figv3DModel_h

#include <string>
#include <vector>
#include <assimp/scene.h>
#include "FigvMesh.h"
#include "FigvMaterial.h"
// FIGV 9
#include "FigvTexture.h"
class Figv3DModel {
    
public:

    // FIGV 11
    Figv3DModel(std::string path, FigvMaterial* material,
 std::string texturePath, glm::mat4 transform);
    void draw(FigvShader shader);

private:
    
    std::vector<FigvMesh> meshes;
    
    FigvMaterial* material;
    // FIGV 10
    FigvTexture* albedo;
    glm::mat4 transform;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    FigvMesh processMesh(aiMesh *mesh, const aiScene *scene);
};

#endif /* Figv3DModel_h */
