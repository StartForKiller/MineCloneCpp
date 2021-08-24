#pragma once

#include "window.h"
#include "renderer/gameobject.h"
#include "utils/texturemanager.h"
#include "renderer/camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class World;

class Game {
public:
    Game();
    ~Game();

    void ProcessInput();
    void Update();
    void Render();

    void Run();

    bool isRunning() const;

private:
    Window *window;

    std::vector<GameObject *>objects;

    TextureManager *textureManager;

    Camera *camera;
    World *world;
};
