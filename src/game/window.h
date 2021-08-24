#pragma once

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
    Window(const std::string& title);
    ~Window();
    void SwapBuffers();

    void MakeContextCurrent();
    bool ShouldClose();
    int GetKey(int key);
    void MouseCallback(double xpos, double ypos);

    double GetLastX() { return lastX; }
    double GetLastY() { return lastY; }
    void FinishedReadingPos() { lastX = currX; lastY = currY; }
    double GetCurrX() { return currX; }
    double GetCurrY() { return currY; }

private:
    GLFWwindow *window;

    double lastX;
    double lastY;
    double currX;
    double currY;
    bool updateLastPos = false;
    bool firstMouse = true;
};
