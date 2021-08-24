#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>

class TextureManager {
public:
    TextureManager(size_t textureWidth, size_t textureHeight, size_t maxTextures);

    void GenerateMipmap();
    size_t FindTexture(std::string name);
    void AddTexture(std::string name);
    void Bind();

private:
    size_t textureWidth;
    size_t textureHeight;
    size_t maxTextures;

    uint32_t TARR;

    std::map<size_t, std::string> textures;
};
