# Project Specifications
cmake_minimum_required(VERSION 3.15)
project(Thallium LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Helps language server
set(DEPS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/external")

set(BUILD_SHARED_LIBS OFF)

add_executable(Thallium)

target_sources(Thallium
        PRIVATE
            src/core/application.cpp
            "${DEPS_ROOT}/lib/glad.c"
            "${DEPS_ROOT}/include/stb/stb_image.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/util/camera.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/util/shader.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/util/texture.cpp"
        PRIVATE FILE_SET HEADERS
        FILES
            "${CMAKE_CURRENT_SOURCE_DIR}/src/util/shader.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/util/texture.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/util/camera.h"
)

# Adds root dir as macro for assets
target_compile_definitions(Thallium PRIVATE
        ROOT="$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
)

# GLFW
add_library(glfw3 STATIC IMPORTED)
set_target_properties(glfw3 PROPERTIES
  IMPORTED_LOCATION "${DEPS_ROOT}/lib/glfw3.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${DEPS_ROOT}/include/GLFW"
)

# GLAD & main project
target_include_directories(Thallium PRIVATE "${DEPS_ROOT}/include")

target_link_libraries(Thallium PRIVATE
  glfw3
  opengl32.lib
  gdi32.lib
  user32.lib
  shell32.lib
)


