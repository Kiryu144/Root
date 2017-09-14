/* Created by David Klostermann on 16.06.2017. */
#ifndef ROOT_RESOURCEMANAGER_H
#define ROOT_RESOURCEMANAGER_H

#include <amethyst>
#include <memory>

template <typename T>
class Resource {
private:
    std::map<std::string, std::unique_ptr<T>> m_storage;
public:
    void add(std::string name, T* element){
        m_storage[name] = std::unique_ptr<T>(element);
    }

    void remove(std::string name){
        m_storage.erase(name);
    }

    T& get(std::string name){
        return *m_storage[name];
    }
};

class ResourceManager {
public:
    static Resource<AM::Shader> shaders;
    static Resource<AM::VBO<glm::vec3, 3>> vbo3D;
    static Resource<AM::Texture> textures;
};


#endif
