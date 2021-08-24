#pragma once

#include "../renderer/gameobject.h"
#include "../renderer/shader.h"
#include "blocktype.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <map>

class TextureManager;
class Chunk;

class World {
public:
    World(TextureManager *textureManager, Shader *chunksShader);
    void LoadBlocks(std::string filepath);

    Chunk *GetChunk(int32_t chunkX, int32_t chunkZ);

    BlockType *GetBlockType(uint8_t type);

    Chunk *GenerateChunk(int32_t chunkX, int32_t chunkZ);
    void LoadChunk(int32_t x, int32_t z);

    std::map<uint64_t, Chunk *> chunks;

private:
    std::vector<BlockType *> blockTypes;

    TextureManager *textureManager;
    Shader* chunksShader;
};
