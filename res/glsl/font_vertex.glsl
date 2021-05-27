#version 330 core

layout (location = 0) in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection;
uniform float uTime;

void main() {
    vec2 offset = vec2(cos(uTime)*20, sin(uTime)*20);
    gl_Position = projection * vec4(vertex.xy + offset, 0.0, 1.0);
    TexCoords = vertex.zw;
}
