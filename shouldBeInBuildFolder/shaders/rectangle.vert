#version 330
layout (location = 0) in vec3 aPos;

uniform mat4 trans;

void main(){
    gl_Position = trans * vec4(aPos.x, aPos.y, aPos.z, 1.0);
}