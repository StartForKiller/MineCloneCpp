#include "gameobject.h"

void GameObject::Setup(float *verticesArray, size_t floatArraySize, uint32_t *indexArray, size_t indexArraySize, Shader *shader)
{
    this->shader = shader;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    SetData(verticesArray, floatArraySize, indexArray, indexArraySize);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
}

void GameObject::SetData(float *verticesArray, size_t floatArraySize, uint32_t *indexArray, size_t indexArraySize) {
    this->verticesArray = verticesArray;
    this->floatArraySize = floatArraySize;
    this->indexArray = indexArray;
    this->indexArraySize = indexArraySize;

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, floatArraySize, verticesArray, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexArraySize, indexArray, GL_STATIC_DRAW);
}

void GameObject::Draw() {
    if(indexArraySize == 0) {
        return;
    }

    shader->Use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, indexArraySize / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}
