#include "game.h"
#include "renderer/shader.h"
#include "world/chunk.h"
#include "world/world.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

Game::Game() {
    if(!glfwInit()) {
        //TODO: error handling
    }
    glfwSetErrorCallback(glfwErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = new Window("MineClone");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.3f, 0.3f, 0.3f, 1.0f);

    camera = new Camera(glm::vec3(0.0f, 75.0f, 0.0f));

    textureManager = new TextureManager(16, 16, 256);

    ChunkShader *testShader = new ChunkShader(textureManager, "resources/shaders/test_vs.glsl", "resources/shaders/test_fs.glsl");
    
    //Model/view/projection
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);

    testShader->SetModelMatrix(model);
    testShader->SetProjectionMatrix(projection);

    world = new World(textureManager, testShader);
    textureManager->GenerateMipmap();
}

Game::~Game() {
    glfwTerminate();
}

void Game::ProcessInput() {
    glfwPollEvents();

    camera->Update(window);
}

void Game::Update() {

    //Swap Buffers
}

void Game::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //World drawing: TODO: World as an object
    for(auto &object : world->chunks) {
        object.second->shader->SetViewMatrix(camera->GetViewMatrix());
        object.second->Draw();
    }

    //Normal objects drawing
    for(auto &object : objects) {
        object->shader->SetViewMatrix(camera->GetViewMatrix());
        object->Draw();
    }

    window->SwapBuffers();
}

bool Game::isRunning() const {
    return !window->ShouldClose();
}

constexpr double MS_PER_UPDATE = 1.0 / 60.0;
void Game::Run() {

    double previous = glfwGetTime();
    double lag = 0.0;
    while(isRunning()) {
        auto current = glfwGetTime();
        auto elapsed = current - previous;
        previous = current;
        lag += elapsed;

        //Input
        ProcessInput();

        //Update
        while(lag >= MS_PER_UPDATE) {
            lag -= MS_PER_UPDATE;

            Update();
        }

        //auto alpha = (float) lag / timestep;

        //Render
        Render();
    }
}
