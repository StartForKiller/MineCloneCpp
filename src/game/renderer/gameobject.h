#pragma once

#include "shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class GameObject {
public:
    void Setup(float *verticesArray, size_t floatArraySize, uint32_t *indexArray, size_t indexArraySize, Shader *shader);
    void SetData(float *verticesArray, size_t floatArraySize, uint32_t *indexArray, size_t indexArraySize);

    void Draw();

    Shader *shader;

protected:
    uint32_t VBO;
    uint32_t EBO;
    uint32_t VAO;

    float *verticesArray;
    size_t floatArraySize;
    uint32_t *indexArray;
    size_t indexArraySize;
};
