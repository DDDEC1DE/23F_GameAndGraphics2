#pragma once

#include "CoreHeaders.h"
#include "RecourceManager/RecourceManager.h"

namespace fw {

class Texture : public Resource
{
public:
    Texture();
    Texture(const char* filename);
    virtual ~Texture();

    GLuint GetTextureID() { return m_TextureID; }

    static Resource::Type GetType()
    {
        return Resource::Type::Texture;
    }

protected:
    void Create(void* pixels, int w, int h);

    GLuint m_TextureID = 0;
};

} // namespace fw
