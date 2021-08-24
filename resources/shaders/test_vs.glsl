#version 330 core
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec3 texCoords;
layout (location = 2) in float shadingValue;

out vec3 localPosition;
out vec3 interpolatedTexCoords;
out float interpolatedShadingValue;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
    localPosition = vertexPosition;
    interpolatedTexCoords = texCoords;
    interpolatedShadingValue = shadingValue;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPosition, 1.0);
}