cmake_minimum_required(VERSION 3.7)
project(Root)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static-libgcc -static-libstdc++ ")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES source/main.cpp source/application.cpp source/application.h source/static/basicmesh.h source/world/chunk/chunk.cpp source/world/chunk/chunk.h source/voxel/voxel.cpp source/voxel/voxel.h source/world/block/block.cpp source/world/block/block.h source/world/block/iblockaccessible.h source/world/block/blockmesh.cpp source/world/block/blockmesh.h source/resources/resourcemanager.h source/resources/resourcemanager.cpp source/world/world/blockworld.cpp source/world/world/blockworld.h source/render/irenderbatch.h source/render/chunkbatch.cpp source/render/chunkbatch.h source/world/world/terraingenerator.cpp source/world/world/terraingenerator.h source/voxel/voxelstructure.cpp source/voxel/voxelstructure.h)

include_directories(${PROJECT_SOURCE_DIR}/../Amethyst/source/)
include_directories(${PROJECT_SOURCE_DIR}/source/)
include_directories(${PROJECT_SOURCE_DIR}/external/include)

link_directories(${PROJECT_SOURCE_DIR}/../Amethyst/cmake-build-debug/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLEW/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLFW/)

add_executable(Root ${SOURCE_FILES})
target_link_libraries(Root amethyst glew32 glfw3 gdi32 opengl32)