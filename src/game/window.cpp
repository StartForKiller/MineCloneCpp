#include "window.h"

Window::Window(const std::string& title) {
    window = glfwCreateWindow(1280, 720, title.c_str(), NULL, NULL);
    MakeContextCurrent();

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer( window, this );
    glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xpos, double ypos) {
        static_cast<Window *>(glfwGetWindowUserPointer(window))->MouseCallback(xpos, ypos);
    });
}

Window::~Window() {
    glfwDestroyWindow(window);
}

void Window::MakeContextCurrent() {
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    glewInit();
}

bool Window::ShouldClose() {
    return (glfwWindowShouldClose(window) == 0 ? false : true) || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
}

void Window::SwapBuffers() {
    glfwSwapBuffers(window);
}

int Window::GetKey(int key) {
    return glfwGetKey(window, key);
}

void Window::MouseCallback(double xpos, double ypos) {
    if(firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    currX = xpos;
    currY = ypos;
}
