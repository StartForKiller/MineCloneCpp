#include "chunk.h"
#include "world.h"

#include <string>

Chunk::Chunk(World *world, Shader *shader, int32_t chunkX, int32_t chunkZ) : GameObject(), world(world), chunkX(chunkX), chunkZ(chunkZ) {
    Setup(NULL, 0, NULL, 0, shader);

    glGenBuffers(1, &TBO);
    glGenBuffers(1, &SBO);

    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, SBO);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 1 * sizeof(float), NULL);
    glEnableVertexAttribArray(2);
    
    meshVertexPositions = new std::vector<float>();
    meshIndices = new std::vector<uint32_t>();
    meshTexCoords = new std::vector<float>();
    meshShadingValues = new std::vector<float>();
    meshIndexCounter = 0;

    memset(blocks, 0x0, CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LARGE);
    //RegenarteMesh();
}

Chunk *lastChunk;
int32_t lastChunkX;
int32_t lastChunkZ;

int Chunk::GetBlock(uint32_t x, uint32_t y, uint32_t z) {
    if(y >= CHUNK_HEIGHT) return -1;
    if(x >= CHUNK_WIDTH || z >= CHUNK_LARGE) {
        int32_t newChunkX = this->chunkX;
        int32_t newChunkZ = this->chunkZ;
        int32_t newX = (x >= CHUNK_WIDTH) ? (((int32_t)x > 0) ? ((int32_t)x % CHUNK_WIDTH) : ((int32_t)CHUNK_WIDTH + (int32_t)x)) : (int32_t)x;
        int32_t newZ = (z >= CHUNK_LARGE) ? (((int32_t)z > 0) ? ((int32_t)z % CHUNK_LARGE) : ((int32_t)CHUNK_LARGE + (int32_t)z)) : (int32_t)z;
        if((int32_t)x < 0) {
            newChunkX--;
        } else if(x >= CHUNK_WIDTH) {
            newChunkX++;
        }
        if((int32_t)z < 0) {
            newChunkZ--;
        } else if(z >= CHUNK_LARGE) {
            newChunkZ++;
        }
        Chunk *newChunk;
        /*if(lastChunk && lastChunkX == newChunkX && lastChunkZ == newChunkZ) newChunk = lastChunk;
        else {*/
            newChunk = lastChunk = world->GetChunk(newChunkX, newChunkZ);
            /*lastChunkX = newChunkX;
            lastChunkZ = newChunkZ;
        }*/
        if(newChunk == nullptr) return -1;
        return newChunk->GetBlock(newX, y, newZ);
    }

    return blocks[x][y][z];
}

void Chunk::AddFace(uint8_t index, int x, int y, int z, BlockType *blockType) {
    //TODO block type

    float *blockVertexPositions = blockType->GetVertexPositions();

    for(int i = 0; i < 4; i++) {
        meshVertexPositions->emplace_back(blockVertexPositions[(12 * index) + i * 3 + 0] + x);
        meshVertexPositions->emplace_back(blockVertexPositions[(12 * index) + i * 3 + 1] + y);
        meshVertexPositions->emplace_back(blockVertexPositions[(12 * index) + i * 3 + 2] + z);
    }

    uint32_t indicesList[6] = {0, 1, 2, 0, 2, 3};
    for(int i = 0; i < 6; i++) {
        meshIndices->emplace_back(indicesList[i] + meshIndexCounter);
    }
    meshIndexCounter += 4;

    float *texCoords = blockType->GetTexCoords();
    for(int i = 0; i < 12; i++) {
        meshTexCoords->emplace_back(texCoords[(12 * index) + i]);
    }
    float *shadingValues = blockType->GetShadingValues();
    for(int i = 0; i < 4; i++) {
        meshShadingValues->emplace_back(shadingValues[(4 * index) + i]);
    }
}

bool Chunk::ShouldRenderFace(int x, int y, int z, BlockType *blockType, int blockTypeNumber) {
    int block = GetBlock(x, y, z);
    if(block <= 0) return true;
    if(world->GetBlockType(block)->IsTransparent()) {
        if(blockType->IsGlass() && block == blockTypeNumber) {
            return false;
        }
        return true;
    }

    return false;
}

void Chunk::RegenarteMesh() {
    meshVertexPositions->clear();
    meshIndices->clear();
    meshTexCoords->clear();
    meshShadingValues->clear();
    for(int32_t lx = 0; lx < CHUNK_WIDTH; lx++) {
        for(int32_t ly = 0; ly < CHUNK_HEIGHT; ly++) {
            for(int32_t lz = 0; lz < CHUNK_LARGE; lz++) {
                int blockNumber = blocks[lx][ly][lz];
                if(blockNumber == 0) continue;

                BlockType *blockType = world->GetBlockType(blockNumber);

                int32_t x = chunkX * CHUNK_WIDTH + lx;
                int32_t z = chunkZ * CHUNK_LARGE + lz;

                //Add other types than cubes
                if(blockType->IsCube()) {
                    if(ShouldRenderFace(lx + 1, ly, lz, blockType, blockNumber)) AddFace(0, x, ly, z, blockType);
                    if(ShouldRenderFace(lx - 1, ly, lz, blockType, blockNumber)) AddFace(1, x, ly, z, blockType);
                    if(ShouldRenderFace(lx, ly + 1, lz, blockType, blockNumber)) AddFace(2, x, ly, z, blockType);
                    if(ShouldRenderFace(lx, ly - 1, lz, blockType, blockNumber)) AddFace(3, x, ly, z, blockType);
                    if(ShouldRenderFace(lx, ly, lz + 1, blockType, blockNumber)) AddFace(4, x, ly, z, blockType);
                    if(ShouldRenderFace(lx, ly, lz - 1, blockType, blockNumber)) AddFace(5, x, ly, z, blockType);
                } else {
                    for(int i = 0; i < blockType->GetNumerOfFaces(); i++) {
                        AddFace(i, x, ly, z, blockType);
                    }
                }
            }
        }
    }
    meshVertexPositions->shrink_to_fit();
    meshIndices->shrink_to_fit();
    meshTexCoords->shrink_to_fit();
    meshShadingValues->shrink_to_fit();

    GameObject::SetData(&meshVertexPositions->front(), meshVertexPositions->size() * sizeof(float), &meshIndices->front(), meshIndices->size() * sizeof(uint32_t));

    glBindBuffer(GL_ARRAY_BUFFER, TBO);
    glBufferData(GL_ARRAY_BUFFER, meshTexCoords->size() * sizeof(float), &meshTexCoords->front(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, SBO);
    glBufferData(GL_ARRAY_BUFFER, meshShadingValues->size() * sizeof(float), &meshShadingValues->front(), GL_STATIC_DRAW);
}

void Chunk::SetBlock(uint32_t x, uint32_t y, uint32_t z, uint8_t block) {
    if(x >= CHUNK_WIDTH || y >= CHUNK_HEIGHT || z >= CHUNK_LARGE) return;
    
    blocks[x][y][z] = block;
    needsUpdate = true;
}

void Chunk::Draw() {
    if(needsUpdate) {
        RegenarteMesh();
        needsUpdate = false;
    }

    GameObject::Draw();
}


void Chunk::SetAllBlocks(uint8_t *buffer, size_t size) {
    memcpy(blocks, buffer, ((CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LARGE) < size) ? (CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_LARGE) : size);
}
