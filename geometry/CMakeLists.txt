cmake_minimum_required(VERSION 3.18)

project(geometry VERSION 1.0)

# finding and linking libraries
find_library(GLEW_LIB GLEW REQUIRED)
find_library(FREETYPE_LIB freetype REQUIRED)
find_library(OPENGL_LIB GL REQUIRED)
find_library(GLFW_LIB glfw REQUIRED)
find_library(TINYXML_LIB tinyxml2 REQUIRED)
add_subdirectory(/home/kobi/Desktop/graphicsMath graphicsMath)

add_library(geometry SHARED
    src/circle.cpp
    src/color.cpp
    src/line.cpp
    src/point.cpp
    src/rectangle.cpp
    src/shader.cpp
    src/events.cpp
    src/nonInclusiveRange.cpp
    src/utility.cpp
    src/geometry.cpp
    src/geometry3d.cpp
    src/cube.cpp
    src/rubiksCube.cpp) # TODO this isnt part of the library

target_link_libraries(geometry ${GLEW_LIB} ${FREETYPE_LIB} ${OPENGL_LIB} graphicsMath)

# editing include paths
target_include_directories(geometry PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/geometry/include
    ${CMAKE_SOURCE_DIR}/guiElements/include
    ~/Desktop/graphicsMath/headers
    /usr/include/freetype2
    /usr/include/GL)