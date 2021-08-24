#include "texturemanager.h"
#define STB_IMAGE_IMPLEMENTATION
extern "C" {
    #include "stb_image.h"
}

#include <cstring>

TextureManager::TextureManager(size_t textureWidth, size_t textureHeight, size_t maxTextures) :
textureWidth(textureWidth), textureHeight(textureHeight), maxTextures(maxTextures)
{
    glGenTextures(1, &TARR);
    glBindTexture(GL_TEXTURE_2D_ARRAY, TARR);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, textureWidth, textureHeight, maxTextures, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    stbi_set_flip_vertically_on_load(true);
}

void TextureManager::GenerateMipmap() {
    glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

void TextureManager::Bind() {
    glBindTexture(GL_TEXTURE_2D_ARRAY, TARR);
}

size_t TextureManager::FindTexture(std::string name) {
    for (auto it = textures.begin(); it != textures.end(); ++it) {
        if (it->second == name) {
            return it->first;
        }
    }

    return -1;
}

void TextureManager::AddTexture(std::string name) {
    textures.insert(std::pair<size_t, std::string>(textures.size(), name));

    int width, height, nrChannels;
    uint8_t *data = stbi_load(("resources/textures/" + name + ".png").c_str(), &width, &height, &nrChannels, 4);
    
    if(data == nullptr) {
        printf("Image %s not found\n", ("resources/textures/" + name + ".png").c_str());
        exit(1);
    }
    
    uint8_t *dataAligned = (uint8_t *)malloc(textureWidth * textureHeight * 4);
    memset(dataAligned, 0x00, textureWidth * textureHeight * 4);
    memcpy(dataAligned, data, width * height * 4);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D_ARRAY, TARR);

    size_t index = FindTexture(name);

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, index, textureWidth, textureHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, dataAligned);
}
