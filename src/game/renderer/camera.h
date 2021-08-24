#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Window;

class Camera {
public:
    Camera(glm::vec3 position);

    glm::vec3 GetPosition() {
        return position;
    }
    void SetPosition(glm::vec3 pos) {
        position = pos;
    }
    glm::mat4 GetViewMatrix() {
        return viewMat;
    }

    void Update(Window *window);

private:
    void UpdateRotation(Window *window);
    void UpdatePosition(Window *window);

    glm::vec3 position;
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = 0.0f;
    float pitch = 0.0f;

    glm::mat4 viewMat;
};
