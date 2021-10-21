#version 330
layout (location = 0) in vec2 coords;

uniform mat4 trans;

void main() {
    gl_Position = trans * vec4(coords, 0.0, 1.0);
}