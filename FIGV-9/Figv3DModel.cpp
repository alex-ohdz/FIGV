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
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "Figv3DModel.h"
#include "FigvAuxiliaryFunctions.h"

// FIGV 12
Figv3DModel::Figv3DModel(std::string path, FigvMaterial* material,
 std::string texturePath, glm::mat4 transform) {
    
    loadModel(path);
    this->material = material;
    this->transform = transform;
    // FIGV 13
    this->albedo = new FigvTexture(texturePath);
}

void Figv3DModel::draw(FigvShader shader) {
    
    shader.set("mModel", transform);
    material->applyToShader(shader);
    // FIGV 14
    albedo->applyToShader(shader);
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].draw();
}

void Figv3DModel::loadModel(std::string path) {
    
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_GenSmoothNormals |
                                             aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        FigvLog("FigvModel", __LINE__, "Error: Assimp");
        FigvLog("FigvModel", __LINE__, importer.GetErrorString());
        return;
    }

    processNode(scene->mRootNode, scene);
}

void Figv3DModel::processNode(aiNode *node, const aiScene *scene) {
    
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

FigvMesh Figv3DModel::processMesh(aiMesh *mesh, const aiScene *scene) {
    
    std::vector<FigvVertex> vertices;
    std::vector<unsigned int> indices;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        FigvVertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        if(mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    return {vertices, indices};
}
