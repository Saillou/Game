R"(
#version 460

layout(triangles) in;
/* 
Input possible:                 depending on glDrawXx(enum):
    points                          GL_POINTS 
    lines                           GL_LINES                | GL_LINE_STRIP 
    lines_adjacency                 GL_LINES_ADJACENCY      | GL_LINE_STRIP_ADJACENCY 
    triangles                       GL_TRIANGLES            | GL_TRIANGLE_STRIP             |  GL_TRIANGLE_FAN
    triangles_adjacency             GL_TRIANGLES_ADJACENCY  | GL_TRIANGLE_STRIP_ADJACENCY 
*/

layout(triangle_strip, max_vertices = 3) out;

in float rho[];
out float f_rho;

void main() {
    f_rho = 1;

    gl_Position     = gl_in[0].gl_Position; f_rho = rho[0]; EmitVertex();
    gl_Position     = gl_in[1].gl_Position; f_rho = rho[1]; EmitVertex(); 
    gl_Position     = gl_in[2].gl_Position; f_rho = rho[2]; EmitVertex();
    EndPrimitive();
}
)"