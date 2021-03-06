#ifndef GLFWHANDLERS_H
#define GLFWHANDLERS_H

#include "GLFW/glfw3.h"
#include "element.h"
#include "input.h"
#include "checkbox.h"
#include "window.h"

namespace handlers {
    GLFWcursor* standardCursor;
    GLFWcursor* handCursor;
    bool isClicked;

    struct PosCallbackArgs {
        double xpos;
        double ypos;
        GLFWwindow* window;
        bool* found;
    };
    struct MouseButtonCallbackArgs {
        double xpos;
        double ypos;
        bool* clicked;
    };
    
    void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
        bool found = false;
        GuiElements::Window* w = (GuiElements::Window*)glfwGetWindowUserPointer(window);
        PosCallbackArgs args = {
            xpos, ypos, window, &found
        };
        w->body->forEachChild([](GuiElements::Element* element, void* args){
            PosCallbackArgs* argsTyped = (PosCallbackArgs*)args;

            if(element->rect.isInRange(argsTyped->xpos, argsTyped->ypos)) {
                if(element != GuiElements::Element::mouseIsIn) {
                    element->rect.mouseIn();
                    if(GuiElements::Element::mouseIsIn != nullptr)
                        GuiElements::Element::mouseIsIn->rect.mouseOut();
                    GuiElements::Element::mouseIsIn = element;
                }
                *argsTyped->found = true;
                glfwSetCursor(argsTyped->window, handCursor);
            }
        }, &args);

        if(!found) {
            // TODO: set normal cursor here and pointer above
            //glfwSetCursor(window, GLFWCursor);
            if(GuiElements::Element::mouseIsIn != nullptr)
                GuiElements::Element::mouseIsIn->rect.mouseOut();
            GuiElements::Element::mouseIsIn = nullptr;
            glfwSetCursor(window, standardCursor);
        }


        // camera
        if (isClicked) {
            w->lastX = w->currX;
            w->lastY = w->currY;

            w->currX = xpos;
            w->currY = ypos;

            // try to figure out when mouse reset happend
            if (std::abs(w->currX - w->lastX) <= 200.0f && std::abs(w->currY - w->lastY) <= 200.0f) {
                float accelerationFactor = 1.4f;
                w->prevRotationXMag = w->rotationXMag;
                w->prevRotationYMag = w->rotationYMag;
                w->rotationXMag += (w->currX - w->lastX) / 800.0f * accelerationFactor;
                w->rotationYMag += (w->currY - w->lastY) / 1000.0f * accelerationFactor;
            }
        }
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, 1);
            glfwTerminate();
            exit(0);
        } else if (action == GLFW_PRESS || action == GLFW_REPEAT) // and not release
            if (GuiElements::Input::active != nullptr)
                if (key == GLFW_KEY_BACKSPACE && !GuiElements::Input::active->text.str.empty())
                    GuiElements::Input::active->popChar();
    }

    void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        double xpos, ypos; // TODO: consider making int, to save casting
        glfwGetCursorPos(window, &xpos, &ypos);
        GuiElements::Window* w = (GuiElements::Window*)glfwGetWindowUserPointer(window);
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            // TODO add a "body" element that has its own click listner that loses focus from inputs instead of this
            bool clicked = false;
            MouseButtonCallbackArgs args = {
                xpos, ypos, &clicked
            };
            w->body->forEachChild([](GuiElements::Element* element, void* args){
                MouseButtonCallbackArgs* argsTyped = (MouseButtonCallbackArgs*)args;
                if(element->rect.isInRange(argsTyped->xpos, argsTyped->ypos)) {
                    element->click(nullptr);
                    // TODO think of a better way to detect if click was on an input
                    try {
                        GuiElements::Input* i = (GuiElements::Input*) element;
                        *argsTyped->clicked = true;
                    } catch(const std::exception& e) {}
                }
            }, &args);
            if (!clicked)
                if (GuiElements::Input::active != nullptr)
                    GuiElements::Input::active->loseFocus();

            // for camera
            isClicked = true;
        } else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
            isClicked = false;
            w->currX = 0.0f;
            w->currY = 0.0f;
            w->lastX = 0.0f;
            w->lastY = 0.0f;
        }
    }
    void window_resize_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        // TODO fix clicking on inputs and hovering when resizing window
    }
    void character_callback(GLFWwindow* window, unsigned int codepoint) {
        if (GuiElements::Input::active != nullptr)
            GuiElements::Input::active->pushChar((char) codepoint);
    }

    void APIENTRY glDebugOutput(GLenum source, 
                                GLenum type, 
                                unsigned int id, 
                                GLenum severity, 
                                GLsizei length, 
                                const char *message, 
                                const void *userParam)
    {
        // ignore non-significant error/warning codes
        if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return; 

        std::cout << "---------------" << std::endl;
        std::cout << "Debug message (" << id << "): " <<  message << std::endl;

        switch (source)
        {
            case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
            case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
            case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
            case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
            case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
            case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
        } std::cout << std::endl;

        switch (type)
        {
            case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
            case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
            case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break; 
            case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
            case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
            case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
            case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
            case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
            case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
        } std::cout << std::endl;
        
        switch (severity)
        {
            case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
            case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
            case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
        } std::cout << std::endl;
        std::cout << std::endl;
    }
}
#endif