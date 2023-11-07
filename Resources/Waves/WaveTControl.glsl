R"(
#version 460

layout(vertices = 4) out;

in vec3 vCoord[]; 
out vec3 tcCoord[];

uniform float TessLevelInner;
uniform float TessLevelOuter;

void main() {
    tcCoord[gl_InvocationID] = vCoord[gl_InvocationID];

    if (gl_InvocationID == 0) {
        gl_TessLevelInner[0] = TessLevelInner;
        gl_TessLevelInner[1] = TessLevelInner;

        gl_TessLevelOuter[0] = TessLevelOuter;
        gl_TessLevelOuter[1] = TessLevelOuter;
        gl_TessLevelOuter[2] = TessLevelOuter;
        gl_TessLevelOuter[3] = TessLevelOuter;
    }
}
)"