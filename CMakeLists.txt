cmake_minimum_required(VERSION 3.18)

project(graphicsLibrary VERSION 1.0)

# finding and linking libraries
find_library(GLEW_LIB GLEW REQUIRED)
find_library(FREETYPE_LIB freetype REQUIRED)
find_library(OPENGL_LIB GL REQUIRED)
find_library(GLFW_LIB glfw REQUIRED)
find_library(TINYXML_LIB tinyxml2 REQUIRED)
add_subdirectory(/home/kobi/Desktop/opengl/guiElements guiElements)

# main
add_executable(main
    main.cpp)
target_link_libraries(main guiElements geometry ${GLFW_LIB} ${TINYXML_LIB})