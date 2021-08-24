#include "blocktype.h"
#include "../utils/texturemanager.h"

#include <cstring>
#include <vector>
#include <algorithm>

BlockType::BlockType(TextureManager *textureManager, std::string name, std::map<std::string, std::string> blockFaceTextures, Model *model) : textureManager(textureManager), name(name), blockFaceTextures(blockFaceTextures), model(model) {
    memcpy(this->texCoords, model->GetTexCoords(), 12 * sizeof(float) * model->GetNumberOfFaces());

    for(auto &blockFaceTexture : blockFaceTextures) {
        textureManager->AddTexture(blockFaceTexture.second);
        size_t textureIndex = textureManager->FindTexture(blockFaceTexture.second);

        if(blockFaceTexture.first == "all") {
            SetBlockFace(0, textureIndex);
            SetBlockFace(1, textureIndex);
            SetBlockFace(2, textureIndex);
            SetBlockFace(3, textureIndex);
            SetBlockFace(4, textureIndex);
            SetBlockFace(5, textureIndex);
            SetBlockFace(6, textureIndex);
            SetBlockFace(7, textureIndex);
        } else if(blockFaceTexture.first == "sides") {
            SetBlockFace(0, textureIndex);
            SetBlockFace(1, textureIndex);
            SetBlockFace(4, textureIndex);
            SetBlockFace(5, textureIndex);
        } else if(blockFaceTexture.first == "x") {
            SetBlockFace(0, textureIndex);
            SetBlockFace(1, textureIndex);
        } else if(blockFaceTexture.first == "y") {
            SetBlockFace(2, textureIndex);
            SetBlockFace(3, textureIndex);
        } else if(blockFaceTexture.first == "z") {
            SetBlockFace(4, textureIndex);
            SetBlockFace(5, textureIndex);
        } else {
            std::vector<std::string> faces = {"right", "left", "top", "bottom", "front", "back"};
            std::vector<std::string>::iterator itr = std::find(faces.begin(), faces.end(), blockFaceTexture.first);
            SetBlockFace(std::distance(faces.begin(), itr), textureIndex);
        }
    }
}

void BlockType::SetBlockFace(uint8_t index, size_t textureIndex) {
    if(index >= model->GetNumberOfFaces()) return; //TODO: Error handling
    for(int i = 0; i < 4; i++) {
        texCoords[(12 * index) + (3 * i) + 2] = textureIndex;
    }
}
