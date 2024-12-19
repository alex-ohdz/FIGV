#include <stdio.h>
 #include <glad/glad.h>
 #include "FigvTexture.h"
 // 2
 #define STB_IMAGE_IMPLEMENTATION
 #include "stb_image.h"
 #include "FigvAuxiliaryFunctions.h"
 FigvTexture::FigvTexture(std::string path) {
    // 3
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, 
                                    &nrComponents, 0);
    // 4
    if (data) {
        // 5
        glGenTextures(1, &textureID);
        // 6
        GLenum format = GL_RGBA;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;
        // 7
        glBindTexture(GL_TEXTURE_2D, textureID);
        // 8
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, 
                     GL_UNSIGNED_BYTE, data);
        // 9
        glGenerateMipmap(GL_TEXTURE_2D);
        // 10
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                        GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
        FigvLog("FigvTexture", __LINE__, "Texture failed to load at: " + 
                std::string(path));
    }
    // 11
    stbi_image_free(data);
 }
 void FigvTexture::applyToShader(FigvShader shader) {
    // 12
    shader.set("texSampler", 0);
    // 13
    glActiveTexture(GL_TEXTURE0);
    // 14
    glBindTexture(GL_TEXTURE_2D, textureID);
 }