#include "glew.h"
#include "../internal/rubiksCube.h"
#include "../internal/shader.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "window.h"

Geometry::Shader* RubiksCube::rubiksCubeShader;
unsigned int RubiksCube::texture;

RubiksCube::RubiksCube(GLFWwindow* w) : w(w) {
    // TODO consider ebo, 12 vertices per face, 6 faces
    float texCoords[12*6];

    // color- white. prototype for other face
    float facePrototype[] = {
         0.0f,  0.5f,
         0.33f, 0.5f,
         0.33f, 1.0f,

         0.0f,  1.0f,
         0.33f, 0.5f,
         0.33f, 1.0f
    };
    for (size_t i = 0; i < 6; i++) {
        faceColors[i] = RC_WHITE;
        std::memcpy(&texCoords[12*i], facePrototype, sizeof(facePrototype));
    }
    glGenBuffers(1, &texCoordsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
}

RubiksCube::~RubiksCube() {
    glDeleteBuffers(1, &texCoordsBuffer);
}

void RubiksCube::fillSquareCoords(float* toFill, int width, int height, int x, int y) {
    toFill[0] = (float)x / width;
    toFill[1] = (float)y / height;

    toFill[2] = (float)(x+1) / width;
    toFill[3] = (float)(y) / height;

    toFill[4] = (float)(x+1) / width;
    toFill[5] = (float)(y+1) / height;

    toFill[6] = (float)x / width;
    toFill[7] = (float)y / height;

    toFill[8] = (float)(x) / width;
    toFill[9] = (float)(y+1) / height;

    toFill[10] = (float)(x+1) / width;
    toFill[11] = (float)(y+1) / height;
}

int RubiksCube::getFaceOffset(int face) {
    switch (face)
    {
    case RC_FRONT:
        return 0;
    case RC_RIGHT:
        return 12;
    case RC_UP:
        return 24;
    case RC_LEFT:
        return 36;
    case RC_DOWN:
        return 48;
    case RC_BACK:
        return 60;
    }
    return -1;
}

void RubiksCube::colorFace(int face, int color) {
    // TODO consider throwing error
    if (face > 5 || face < 0) return;

    if (faceColors[face] != color) {
        float data[12];
        int colorX = color % 3;
        int colorY = color / 3;
        fillSquareCoords(data, 3, 2, colorX, colorY);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, getFaceOffset(face) * sizeof(float), sizeof(data), data);
        faceColors[face] = color;
    }
}


void RubiksCube::init() {
    rubiksCubeShader = new Geometry::Shader("texture.vert", "texture.frag");

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    unsigned char data[] = {
        239, 26, 22,   // red
        5, 171, 121,   // green
        47, 82, 186,   // blue
        255, 255, 255, // white
        254, 123, 43 , // orange
        252, 242, 48,  // yellow
    };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 3, 2, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void RubiksCube::destroy() {
    delete rubiksCubeShader;
}

void RubiksCube::draw() {
    rubiksCubeShader->use();

    glBindVertexArray(Cube::cubeVao);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 mat = glm::mat4(1.0f);
    GuiElements::Window* win = (GuiElements::Window*)glfwGetWindowUserPointer(this->w);

    mat = glm::rotate(mat, win->rotationXMag, glm::vec3(0.0f, 1.0f, 0.0f));
    mat = glm::rotate(mat, win->rotationYMag, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 projection;
    // projection = glm::perspective(glm::radians(45.0f), 1000.0f / 800.0f, 0.1f, 100.0f);
    projection = glm::mat4(1.0f);
    // projection = glm::rotate(mat, 3.14f, glm::vec3(0.3f, 0.3f, 0.3f));

    // rubiksCubeShader->setMat4("trans", glm::value_ptr(mat));
    double alpha = glfwGetTime() / 6.0;
    float trans[] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, sin(alpha), 0.0f, 0.0f,
        0.0f, 0.0f, cos(alpha), 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
    };
    rubiksCubeShader->setMat4("trans", trans);
    rubiksCubeShader->setMat4("projection", glm::value_ptr(projection));
    rubiksCubeShader->setInt("tex", 0);

    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordsBuffer);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}