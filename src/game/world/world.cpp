#include "world.h"
#include "chunk.h"

#include <fstream>
#define NBT_IMPLEMENTATION
#define NBT_OWN_ZLIB <zlib.h>
#include "../utils/nbt.h"

World::World(TextureManager *textureManager, Shader *chunksShader) : textureManager(textureManager), chunksShader(chunksShader) {
    blockTypes.push_back(new BlockType(textureManager, "air", {}, new CubeModel()));

    LoadBlocks("resources/blocks.mcpy");

    for(int x = -4; x < 4; x++) {
        for(int z = -4; z < 4; z++) {
            Chunk *chunk = GenerateChunk(x, z);
            /*for(int lx = 0; lx < chunk->CHUNK_WIDTH; lx++) {
                for(int ly = 0; ly < chunk->CHUNK_HEIGHT; ly++) {
                    for(int lz = 0; lz < chunk->CHUNK_LARGE; lz++) {
                        if(ly < 1) chunk->SetBlock(lx, ly, lz, 1);
                    }
                }
            }*/
            LoadChunk(x, z);
            chunk->SetBlock(7, 85, 7, 51);
        }
    }
}

std::vector<std::string> split(std::string str, char pattern) {
    int posInit = 0;
    int posFound = 0;
    std::string splitted;
    std::vector<std::string> results;
    
    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        results.push_back(splitted);
    }
    
    return results;
}
std::string strip(const std::string &inpt)
{
    auto start_it = inpt.begin();
    auto end_it = inpt.rbegin();
    while (std::isspace(*start_it))
        ++start_it;
    while (std::isspace(*end_it))
        ++end_it;
    return std::string(start_it, end_it.base());
}

void World::LoadBlocks(std::string filepath) {
    std::ifstream file(filepath);

    for(std::string line; getline(file, line );) {
        if(line[0] == '\n' || line[0] == '#') continue;

        std::string num = split(line, ':')[0];
        std::string props = split(line, ':')[1];
        int number = atoi(num.c_str());

        std::string name = "Unknown";
        Model *model = new CubeModel();
        std::map<std::string, std::string> texture = {{"all", "unknown"}};
        bool firstTexture = true;

        for(auto& prop : split(props, ',')) {
            prop = strip(prop);
            std::vector<std::string> oProps = split(prop, ' ');

            if(oProps[0] == "sameas") {
                int sameasNumber = atoi(oProps[1].c_str());
                name = blockTypes[sameasNumber]->GetName();
                texture = blockTypes[sameasNumber]->GetBlockFaceTextures();
                model = blockTypes[sameasNumber]->GetModel();
            } else if(oProps[0] == "name") {
                name = "";
                for(int i = 1; i < oProps.size(); i++) {
                    name += oProps[i];
                }
                name = name.substr(1, name.size() - 2);
            } else if(oProps[0] == "model") {
                if(oProps[1] == "button") {
                    model = new ButtonModel();
                } else if(oProps[1] == "cactus") {
                    model = new CactusModel();
                } else if(oProps[1] == "crop") {
                    model = new CropModel();
                } else if(oProps[1] == "cube") {
                    ;
                } else if(oProps[1] == "door") {
                    model = new DoorModel();
                } else if(oProps[1] == "fire") {
                    model = new FireModel();
                } else if(oProps[1] == "flat") {
                    model = new FlatModel();
                } else if(oProps[1] == "glass") {
                    model = new GlassModel();
                } else if(oProps[1] == "ladder") {
                    model = new LadderModel();
                } else if(oProps[1] == "leaves") {
                    model = new LeavesModel();
                } else if(oProps[1] == "leaver") {
                    model = new LeavesModel();
                } else if(oProps[1] == "liquid") {
                    model = new LiquidModel();
                } else if(oProps[1] == "plant") {
                    model = new PlantModel();
                } else if(oProps[1] == "pressure_plate") {
                    model = new PressurePlateModel();
                } else if(oProps[1] == "sign") {
                    model = new SignModel();
                } else if(oProps[1] == "sign_post") {
                    model = new SignPostModel();
                } else if(oProps[1] == "slab") {
                    model = new SlabModel();
                } else if(oProps[1] == "snow") {
                    model = new SnowModel();
                } else if(oProps[1] == "soil") {
                    model = new SoilModel();
                } else if(oProps[1] == "stairs") {
                    model = new StairsModel();
                } else if(oProps[1] == "torch") {
                    model = new TorchModel();
                }
            } else if(!strncmp(oProps[0].c_str(), "texture", 7)) {
                std::string side = split(oProps[0], '.')[1];
                if(firstTexture) {
                    texture.clear();
                    firstTexture = false;
                }
                texture.insert(std::pair<std::string, std::string>(side, strip(oProps[1])));
            }
        }

        BlockType *blockType = new BlockType(textureManager, name, texture, model);

        if(number < blockTypes.size()) {
            blockTypes[number] = blockType;
        } else {
            blockTypes.push_back(blockType);
        }
    }
}

Chunk *World::GetChunk(int32_t chunkX, int32_t chunkZ) {
    uint64_t index = (((uint64_t)(uint32_t)chunkX) << 32) | (uint64_t)(uint32_t)chunkZ;

    auto it = chunks.find(index);
    if(it != chunks.end()) {
        return it->second;
    }

    return nullptr;
}

BlockType *World::GetBlockType(uint8_t type) {
    if(type >= blockTypes.size()) {
        return blockTypes[1];
    }
    return blockTypes[type];
}

Chunk *World::GenerateChunk(int32_t chunkX, int32_t chunkZ) {
    Chunk *chunk = new Chunk(this, chunksShader, chunkX, chunkZ);

    uint64_t index = (((uint64_t)(uint32_t)chunkX) << 32) | (uint64_t)(uint32_t)chunkZ;
    chunks.insert(std::pair<uint64_t, Chunk *>(index, chunk));

    return chunk;
}

std::string toBase36(int num) {
    const std::string chars = "0123456789abcdefghijklmnopqrstuvwxyz";
    std::string base36num = "";

    if(num < 0) return "-" + toBase36(-num);

    uint32_t charsLength = chars.length();

    while(num != 0) {
        uint8_t i = num % charsLength;
        num = num / charsLength;
        base36num = chars[i] + base36num;
    }

    return (base36num.length() > 0) ? base36num : "0";
}

static size_t reader_read(void* userdata, uint8_t* data, size_t size) {
  return fread(data, 1, size, (FILE *)userdata);
}

void World::LoadChunk(int32_t x, int32_t z) {
    Chunk *chunk = GetChunk(x, z);
    
    std::string posPath = "resources/save/" + toBase36((uint8_t)(x) % 64) + "/" + toBase36((uint8_t)(z) % 64) + "/c." + toBase36(x) + "." + toBase36(z) + ".dat";
    
    FILE *file = fopen(posPath.c_str(), "rb");
    if(!file) return;

    //printf("%s\n", posPath.c_str());

    nbt_reader_t reader;

    reader.read = reader_read;
    reader.userdata = file;

    nbt_tag_t *root = nbt_parse(reader, NBT_PARSE_FLAG_USE_GZIP);
    fclose(file);

    nbt_tag_t *blocks = nbt_tag_compound_get(nbt_tag_compound_get(root, "Level"), "Blocks");

    for(int x = 0; x < Chunk::CHUNK_WIDTH; x++) {
        for(int y = 0; y < Chunk::CHUNK_HEIGHT; y++) {
            for(int z = 0; z < Chunk::CHUNK_LARGE; z++) {
                chunk->SetBlock(x, y, z, blocks->tag_byte_array.value[x * Chunk::CHUNK_WIDTH * Chunk::CHUNK_HEIGHT + z * Chunk::CHUNK_HEIGHT + y]);
            }
        }
    }
}
