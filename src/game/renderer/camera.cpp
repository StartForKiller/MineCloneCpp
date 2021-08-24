#include "camera.h"
#include "../window.h"

Camera::Camera(glm::vec3 position) : position(position) {
    viewMat = glm::lookAt(position, position + cameraFront, cameraUp);
}

void Camera::UpdateRotation(Window *window) {
    float xoffset = window->GetCurrX() - window->GetLastX();
    float yoffset = window->GetLastY() - window->GetCurrY();
    window->FinishedReadingPos();

    float sesitivity = 0.2f;
    xoffset *= sesitivity;
    yoffset *= sesitivity;

    yaw += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f) pitch = 89.0f;
    else if(pitch < -89.0f) pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}

void Camera::UpdatePosition(Window *window) {
    float cameraSpeed = 0.05f;
    if(window->GetKey(GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cameraSpeed *= 2.0f;
    }
    if(window->GetKey(GLFW_KEY_W) == GLFW_PRESS) {
        position += cameraSpeed * cameraFront;
    }
    if(window->GetKey(GLFW_KEY_S) == GLFW_PRESS) {
        position -= cameraSpeed * cameraFront;
    }
    if(window->GetKey(GLFW_KEY_A) == GLFW_PRESS) {
        position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(window->GetKey(GLFW_KEY_D) == GLFW_PRESS) {
        position += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(window->GetKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
        position += cameraUp * cameraSpeed;
    }
    if(window->GetKey(GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        position -= cameraUp * cameraSpeed;
    }
}

void Camera::Update(Window *window) {
    UpdateRotation(window);
    UpdatePosition(window);

    viewMat = glm::lookAt(position, position + cameraFront, cameraUp);
}
