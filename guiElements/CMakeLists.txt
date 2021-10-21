cmake_minimum_required(VERSION 3.18)

project(guiElements VERSION 1.0)

# finding and linking libraries
find_library(GLEW_LIB GLEW REQUIRED)
find_library(FREETYPE_LIB freetype REQUIRED)
find_library(OPENGL_LIB GL REQUIRED)
find_library(GLFW_LIB glfw REQUIRED)
find_library(TINYXML_LIB tinyxml2 REQUIRED)
add_subdirectory(/home/kobi/Desktop/opengl/geometry geometry)

# guiElements
add_library(guiElements SHARED
    src/button.cpp
    src/checkbox.cpp
    src/container.cpp
    src/graph.cpp
    src/input.cpp
    src/text.cpp
    src/element.cpp
    src/lineBreak.cpp
    src/window.cpp
    src/grid.cpp)

target_include_directories(guiElements PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/geometry/include
    ${CMAKE_SOURCE_DIR}/guiElements/include)

target_link_libraries(guiElements geometry)