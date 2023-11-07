R"(
#version 460

in float f_rho;

uniform vec3 Color;

out vec4 FragColor;

void main() {
    if(f_rho == -1) {
        FragColor = vec4(Color, 1.0);
        return;
    }

    FragColor = pow(f_rho, 2) * vec4(Color, 1.0) + vec4(0.25, 0.25, 0.25, 0.25);
}
)"