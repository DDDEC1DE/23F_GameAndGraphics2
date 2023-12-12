#pragma once

#include "CoreHeaders.h"
#include <string>

namespace fw {

class Resource
{
public:
    enum class Type
    {
        Mesh,
        Texture,
        Shader,
        Animation,
        AnimationSet
    };
};

class ResourceManager
{
public:
    ResourceManager();
    ~ResourceManager();

    template<class T>
    void Add(std::string name, T* pResource)
    {
        m_Resources[T::GetType()][name] = pResource;
    }

    template<class T>
    T* GetResource(std::string name) 
    {
        return static_cast<T*>(m_Resources[T::GetType()][name]);
    }

protected:
    std::map<Resource::Type, std::map<std::string, Resource* >> m_Resources;
};

} // namespace fw
