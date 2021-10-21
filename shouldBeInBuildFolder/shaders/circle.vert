#version 420
layout(location = 0) in vec2 coords;

uniform mat4 trans;

void main() {
    gl_Position = trans * vec4(coords, 0.0f, 1.0f);
}