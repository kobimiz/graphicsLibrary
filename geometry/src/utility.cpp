#define GLEW_STATIC
#include "glew.h"
#include "GLFW/glfw3.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include <iostream>

#include "geometry.h"

#include "glfwHandlers.h"

std::map<char, Geometry::Character> Geometry::Utility::characters;
unsigned int Geometry::Utility::textVao, Geometry::Utility::textVbo;
Geometry::Shader* Geometry::Utility::textShader;

namespace Geometry {

namespace Utility {
    void initFreeType() {
        FT_Library ft;
        FT_Face face;
        if(FT_Init_FreeType(&ft))
            std::cout << "Error initializing FreeType.\n";
        if(FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
            std::cout << "Error loading font.\n";
        if(FT_Set_Pixel_Sizes(face, 0, 48))
            std::cout << "Error setting pixel size.\n";

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
        for (unsigned char c = 0; c < 128; ++c) {
            /* load char image into the slot (erase previous one) */
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "Error loading glyph '" << c << "'.\n";
                continue;
            }

            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                face->glyph->advance.x
            };
            Utility::characters.insert({ c, character });
        }
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        // need to enable this for text rendering
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


        glGenVertexArrays(1, &Utility::textVao);
        glGenBuffers(1, &Utility::textVbo);
        glBindVertexArray(Utility::textVao);
        glBindBuffer(GL_ARRAY_BUFFER, Utility::textVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

	    Utility::textShader = new Shader("text.vert", "text.frag");
        glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Rectangle::screenWidth), 0.0f, static_cast<float>(Rectangle::screenHeight));
        Utility::textShader->use();
        projection = glm::transpose(projection);
        Utility::textShader->setMat4("projection", glm::value_ptr(projection));
    }

    void initGLEW(bool enableDebug) {
        if (glewInit() != GLEW_OK)
            std::cout << "Failed to initialize glew" << std::endl;

        if (!enableDebug) return;

        int flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
            glDebugMessageCallback(handlers::glDebugOutput, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }
    }

    void initGLFW() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }

    void setGLFWCallbacks(GLFWwindow* window) {
        glfwSetKeyCallback(window, handlers::key_callback);
        glfwSetCursorPosCallback(window, handlers::cursorPositionCallback);
        glfwSetMouseButtonCallback(window, handlers::mouseButtonCallback);
        glfwSetFramebufferSizeCallback(window, handlers::window_resize_callback);
        glfwSetCharCallback(window, handlers::character_callback);
    }

    void renderText(std::string text, float x, float y, float scale, glm::vec3 color) {
        // TODO consider changing this. flipping y axis to match rest of coord system
        y = Rectangle::screenHeight - y;
        Utility::textShader->use();
        Utility::textShader->setVec3("textColor", glm::value_ptr(color));
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(Utility::textVao);

        for (auto &&c : text) {
            Character ch = Utility::characters[c];

            float xpos = x + ch.bearing.x * scale;
            float ypos = y - (ch.size.y - ch.bearing.y) * scale;

            float w = ch.size.x * scale;
            float h = ch.size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },            
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.textureId);
            glBindBuffer(GL_ARRAY_BUFFER, Utility::textVbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); 
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
        }
    }
}

}; // namespace Geometry