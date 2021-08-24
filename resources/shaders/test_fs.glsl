#version 330 core
out vec4 FragColor;

in vec3 localPosition;
in vec3 interpolatedTexCoords;
in float interpolatedShadingValue;

uniform sampler2DArray textureArraySampler;

void main() {
    vec4 textureColour = texture(textureArraySampler, interpolatedTexCoords);
    FragColor = textureColour * interpolatedShadingValue;

    if(textureColour.a == 0.0) discard;
}