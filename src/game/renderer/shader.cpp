#include "shader.h"
#include "../utils/texturemanager.h"

#include <cstring>

Shader::Shader(std::string vs_filepath, std::string fs_filepath) {
    int success;
    char infoLog[512];

    FILE *vsFile = fopen(vs_filepath.c_str(), "rb");
    fseek(vsFile, 0, SEEK_END);
    size_t vsFileSize = ftell(vsFile);
    fseek(vsFile, 0, SEEK_SET);

    char *vsShaderSource = new char[vsFileSize + 1];
    memset(vsShaderSource, 0x00, vsFileSize + 1);
    fread(vsShaderSource, vsFileSize, 1, vsFile);
    fclose(vsFile);

    FILE *fsFile = fopen(fs_filepath.c_str(), "rb");
    fseek(fsFile, 0, SEEK_END);
    size_t fsFileSize = ftell(fsFile);
    fseek(fsFile, 0, SEEK_SET);

    char *fsShaderSource = new char[fsFileSize + 1];
    memset(fsShaderSource, 0x00, fsFileSize + 1);
    fread(fsShaderSource, fsFileSize, 1, fsFile);
    fclose(fsFile);

    uint32_t vsShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vsShader, 1, &vsShaderSource, NULL);
    glCompileShader(vsShader);

    glGetShaderiv(vsShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vsShader, 512, NULL, infoLog);
        printf("Error in vertex shader %s: %s", vs_filepath.c_str(), infoLog);
        exit(1);
    }
    delete[] vsShaderSource;

    uint32_t fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fsShader, 1, &fsShaderSource, NULL);
    glCompileShader(fsShader);

    glGetShaderiv(fsShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fsShader, 512, NULL, infoLog);
        printf("Error in fragment shader %s: %s", fs_filepath.c_str(), infoLog);
        exit(1);
    }
    delete[] fsShaderSource;

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vsShader);
    glAttachShader(shaderProgram, fsShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vsShader);
    glDeleteShader(fsShader);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error linking program: %s", infoLog);
        exit(1);
    }

    modelMatrixLocation      = glGetUniformLocation(shaderProgram, "modelMatrix");
    viewMatrixLocation       = glGetUniformLocation(shaderProgram, "viewMatrix");
    projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
}

void Shader::Use() {
    glUseProgram(shaderProgram);
}

void Shader::SetModelMatrix(glm::mat4 model) {
    Use();
    glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
    glUseProgram(0);
}

void Shader::SetViewMatrix(glm::mat4 view) {
    Use();
    glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUseProgram(0);
}

void Shader::SetProjectionMatrix(glm::mat4 projection) {
    Use();
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));
    glUseProgram(0);
}

ChunkShader::ChunkShader(TextureManager *textureManager, std::string vs_filepath, std::string fs_filepath) : Shader(vs_filepath, fs_filepath), textureManager(textureManager) {
    GLint samplerLoc = glGetUniformLocation(shaderProgram, "textureArraySampler");
    glUniform1f(samplerLoc, 0);
}

void ChunkShader::Use() {
    Shader::Use();
    glActiveTexture(GL_TEXTURE0);
    textureManager->Bind();
}
