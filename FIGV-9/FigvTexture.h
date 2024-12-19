 #pragma once
 #ifndef FigvTexture_h
 #define FigvTexture_h
 #include <string>
 #include "FigvShader.h"
 struct FigvTexture {
 public:
 FigvTexture(std::string path);
 void applyToShader(FigvShader shader);
 private:
 // 1
 unsigned int textureID;
 };
 #endif /* FigvTexture_h */