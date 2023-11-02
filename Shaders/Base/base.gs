R""(#version 460 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in vec3 color[];
out vec3 fColor;

void main() {    
    vec4 position = gl_in[0].gl_Position;
    vec2 ux = 0.1 * vec2(position.xy);

    fColor = color[0];
    gl_Position = position + vec4(-ux, 0.0, 0.0);
    EmitVertex();   

    gl_Position = position + vec4(+ux, 0.0, 0.0);
    fColor = vec3(1.0, 1.0, 1.0);
    EmitVertex();

    EndPrimitive();
}

)""