R"(
#version 460

layout (location = 0) in vec3 Position;

uniform float zIndex;

out vec3 vCoord;

void main() {
    vCoord = vec3(Position.xy, zIndex);
}
)"