#pragma once

#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class TextureManager;

//All shaders have model/projection and view matrix
class Shader {
public:
    Shader(std::string vs_filepath, std::string fs_filepath);

    void Use();

    void SetModelMatrix(glm::mat4 model);
    void SetViewMatrix(glm::mat4 view);
    void SetProjectionMatrix(glm::mat4 projection);

protected:
    uint32_t shaderProgram;

    uint32_t modelMatrixLocation;
    uint32_t viewMatrixLocation;
    uint32_t projectionMatrixLocation;
};

class ChunkShader : public Shader {
public:
    ChunkShader(TextureManager *textureManager, std::string vs_filepath, std::string fs_filepath);

    void Use();

private:
    TextureManager *textureManager;
};
