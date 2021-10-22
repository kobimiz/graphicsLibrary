#include "geometry3d.h"

#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../internal/rectangle.h"

Geometry::Shader* Geometry::Cube::shaderProgram;
unsigned int Geometry::Cube::cubeVao;
unsigned int Geometry::Cube::cubeVbo;


#include "GLFW/glfw3.h"

namespace Geometry {
    void Cube::init() {

        // float cubeVertices[] = {
        //     -0.5f,  0.5f, -0.5f, // 1
        //      0.5f,  0.5f, -0.5f, // 2
        //      0.5f, -0.5f, -0.5f, // 3
        //     -0.5f, -0.5f, -0.5f, // 4

        //     -0.5f,  0.5f,  0.5f, // 5
        //      0.5f,  0.5f,  0.5f, // 6
        //      0.5f, -0.5f,  0.5f, // 7
        //     -0.5f, -0.5f,  0.5f, // 8

        //     1, 2, 3,
        //     1, 3, 4,
        //     2, 6, 7,
        //     2, 7, 3,
        //     1, 5, 8,
        //     1, 8, 4,
        //     1, 2, 6,
        //     1, 6, 5,
        //     4, 3, 7,
        //     4, 7, 8,
        //     5, 6, 7,
        //     5, 7, 8

        // };
        float cubeVertices[] = {

            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
            
            -0.5f,  0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            
             0.5f,  0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
             0.5f, -0.5f, -0.5f,
            
            -0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,
            
            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
            
            -0.5f,  0.5f, -0.5f,
             0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
            
            -0.5f, -0.5f, -0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            
            -0.5f,  0.5f,  0.5f,
             0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            
            -0.5f,  0.5f,  0.5f,
             0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f
        };

        glGenVertexArrays(1, &cubeVao);
        glGenBuffers(1, &cubeVbo);
        glBindVertexArray(cubeVao);
        glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        shaderProgram = new Shader("rectangle.vert", "rectangle.frag");
    }


    void Cube::destroy() {
        delete shaderProgram;
        glDeleteVertexArrays(1, &cubeVao);
        glDeleteBuffers(1, &cubeVbo);
    }

    void Cube::draw() {
        shaderProgram->use();
        glBindVertexArray(cubeVao);

        glm::mat4 mat = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime(), glm::vec3(0.1f, 0.7f, 0.2f));
        float color[] = { 0.43f, 0.5f, 0.7f };

        shaderProgram->setMat4("trans", glm::value_ptr(mat));
        shaderProgram->setVec3("color", color);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}; // namespace Geometry