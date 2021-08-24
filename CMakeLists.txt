cmake_minimum_required(VERSION 3.1)

macro(configure_files srcDir destDir)
    message(STATUS "Configuring directory ${destDir}")
    make_directory(${destDir})

    file(GLOB templateFiles RELATIVE ${srcDir} ${srcDir}/*)
    foreach(templateFile ${templateFiles})
        set(srcTemplatePath ${srcDir}/${templateFile})
        if(NOT IS_DIRECTORY ${srcTemplatePath})
            message(STATUS "Configuring file ${templateFile}")
            configure_file(
                    ${srcTemplatePath}
                    ${destDir}/${templateFile}
                    COPYONLY)
        else()
            configure_files(${srcTemplatePath} ${destDir}/${templateFile})
        endif(NOT IS_DIRECTORY ${srcTemplatePath})
    endforeach(templateFile)
endmacro(configure_files)

project(MineClone VERSION 0.1 DESCRIPTION "Minecraft Clone in C++" LANGUAGES CXX)

cmake_policy(SET CMP0072 NEW)

find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(MineClone src/main.cpp src/game/game.cpp src/game/window.cpp src/game/renderer/gameobject.cpp src/game/renderer/shader.cpp src/game/renderer/camera.cpp src/game/world/chunk.cpp src/game/world/world.cpp src/game/world/blocktype.cpp src/game/utils/texturemanager.cpp src/game/models/models.cpp)

set(CMAKE_BUILD_TYPE Debug)

target_link_libraries(MineClone glfw OpenGL::GL GLEW::GLEW ZLIB::ZLIB)

target_compile_features(MineClone PUBLIC cxx_std_17)


configure_files(${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_BINARY_DIR}/resources)
