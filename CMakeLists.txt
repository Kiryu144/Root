cmake_minimum_required(VERSION 3.7)
project(Root)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES source/main.cpp)

include_directories(${PROJECT_SOURCE_DIR}/../Amethyst/source/)
include_directories(${PROJECT_SOURCE_DIR}/source/)
include_directories(${PROJECT_SOURCE_DIR}/external/include)

link_directories(${PROJECT_SOURCE_DIR}/../Amethyst/cmake-build-debug/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLEW/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLFW/)

add_executable(Root ${SOURCE_FILES})
target_link_libraries(Root amethyst glew32 glfw3 gdi32 opengl32)