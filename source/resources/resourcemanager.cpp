/* Created by David Klostermann on 16.06.2017. */

#include "resourcemanager.h"

Resource<AM::Shader> ResourceManager::shaders; //So frckn stupid
Resource<AM::VBO<glm::vec3, 3>> ResourceManager::vbo3D;
Resource<AM::Texture> ResourceManager::textures;