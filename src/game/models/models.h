#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Model {
public:
    virtual float *GetVertexPositions() = 0;
    virtual float *GetTexCoords() = 0;
    virtual float *GetShadingValues() = 0;
    virtual size_t GetNumberOfFaces() = 0;
    virtual bool IsCube() = 0;
    virtual bool IsTransparent() = 0;
    virtual bool IsGlass() = 0;
};

class ButtonModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class CactusModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class CropModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 8;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class CubeModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return true; }
    bool IsTransparent() { return false; }
    bool IsGlass() { return false; }
};

class DoorModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return true; }
    bool IsTransparent() { return false; }
    bool IsGlass() { return false; }
};

class FireModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 4;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class FlatModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 2;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class GlassModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return true; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return true; }
};

class LadderModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 4;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class LeavesModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return true; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class LeverModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class LiquidModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return true; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return true; }
};

class PlantModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 4;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class PressurePlateModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 2;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class SignModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 4;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class SignPostModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 4;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class SlabModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class SnowModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 2;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class SoilModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class StairsModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};

class TorchModel: public Model {
public:
    float *GetVertexPositions();
    float *GetTexCoords();
    float *GetShadingValues();
    size_t GetNumberOfFaces() {
        return 6;
    }
    bool IsCube() { return false; }
    bool IsTransparent() { return true; }
    bool IsGlass() { return false; }
};
