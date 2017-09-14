cmake_minimum_required(VERSION 3.7)
project(Root)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static-libgcc -static-libstdc++ ")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES
    source/main.cpp source/application.cpp source/application.h)

include_directories(${PROJECT_SOURCE_DIR}/../Amethyst/source/)
include_directories(${PROJECT_SOURCE_DIR}/source/)
include_directories(${PROJECT_SOURCE_DIR}/external/include)
include_directories(${PROJECT_SOURCE_DIR}/external/include/FREETYPE/)

link_directories(${PROJECT_SOURCE_DIR}/../Amethyst/cmake-build-debug/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLEW/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLFW/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/FREETYPE/)

add_executable(Root ${SOURCE_FILES})
target_link_libraries(Root amethyst glew32 glfw3 gdi32 opengl32 freetype)