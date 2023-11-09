R"(
#version 460

/* Possible:
    triangles,
    quads
*/
layout(quads, equal_spacing, ccw) in;

in vec3 tcCoord[];
out float rho;

uniform mat4 Projection;
uniform mat4 Modelview;
uniform float time;
uniform float n_cells;

uniform Normals {
    float matrix[9];
} Output;

void main() {
    // With quads
    float u = gl_TessCoord.x;
    vec3 p0 = mix(tcCoord[0], tcCoord[3], u);
    vec3 p1 = mix(tcCoord[1], tcCoord[2], u);

    float v = gl_TessCoord.y;
    vec3 p  = mix(p0, p1, v);
    
    // Heights
    int N = 3;
    float rx = (N-1) * (p.x + 1.0) * 0.5; rx = clamp(0, N-1, rx); // 0 - N-1
    float ry = (N-1) * (p.y + 1.0) * 0.5; ry = clamp(0, N-1, ry); // 0 - N-1

    int i0 = int(round(rx));
    int j0 = int(round(ry));
    float dr = 1.0 - sqrt(pow(i0-rx, 2) + pow(j0-ry, 2));

    float oz = 0.20 * Output.matrix[i0 + N*j0] * dr;
    rho = 0.5*(1.0 + oz / 0.15);
    time;

    gl_Position = Projection * Modelview * vec4(p.xy, p.z + oz, 1.0);
}
)"