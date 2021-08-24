#pragma once

#include "../models/models.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>

class TextureManager;

class BlockType {
public:
    BlockType(TextureManager *textureManager, std::string name, std::map<std::string, std::string> blockFaceTextures, Model *model); //TODO: model

    std::string GetName() { return name; }
    std::map<std::string, std::string> GetBlockFaceTextures() { return blockFaceTextures; }
    Model *GetModel() { return model; }

    void SetBlockFace(uint8_t index, size_t textureIndex);
    float *GetVertexPositions() { return model->GetVertexPositions(); };
    float *GetTexCoords() { return texCoords; };
    float *GetShadingValues() { return model->GetShadingValues(); };
    size_t GetNumerOfFaces() { return model->GetNumberOfFaces(); }
    bool IsCube() { return model->IsCube(); }
    bool IsTransparent() { return model->IsTransparent(); }
    bool IsGlass() { return model->IsGlass(); }

private:
    TextureManager *textureManager;
    std::string name;
    std::map<std::string, std::string> blockFaceTextures;
    Model *model;

    float texCoords[12 * 8];
};
