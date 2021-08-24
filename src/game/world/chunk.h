#pragma once

#include "../renderer/gameobject.h"
#include "../renderer/shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

class World;
class BlockType;

class Chunk : public GameObject {
public:
    Chunk(World *world, Shader *shader, int32_t chunkX, int32_t chunkZ);

    void SetBlock(uint32_t x, uint32_t y, uint32_t z, uint8_t block);
    void SetAllBlocks(uint8_t *buffer, size_t size);
    int GetBlock(uint32_t x, uint32_t y, uint32_t z);
    void RegenarteMesh();

    void Draw();

    static const uint32_t CHUNK_HEIGHT = 128;
    static const uint32_t CHUNK_WIDTH = 16;
    static const uint32_t CHUNK_LARGE = 16;

private:
    void AddFace(uint8_t index, int x, int y, int z, BlockType *blockType);

    bool ShouldRenderFace(int x, int y, int z, BlockType *blockType, int blockTypeNumber);

    uint32_t TBO;
    uint32_t SBO;

    uint8_t blocks[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_LARGE];

    int32_t chunkX;
    int32_t chunkZ;

    World *world;

    std::vector<float> *meshVertexPositions;
    std::vector<uint32_t> *meshIndices;
    std::vector<float> *meshTexCoords;
    std::vector<float> *meshShadingValues;
    uint32_t meshIndexCounter;

    bool needsUpdate = true;
};
