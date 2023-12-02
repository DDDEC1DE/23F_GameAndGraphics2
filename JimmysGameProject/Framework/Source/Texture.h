#pragma once

#include "CoreHeaders.h"

namespace fw {

class Texture
{
public:
    Texture();
    Texture(const char* filename);
    virtual ~Texture();

    GLuint GetTextureID() { return m_TextureID; }

protected:
    void Create(void* pixels, int w, int h);

    GLuint m_TextureID = 0;
};

} // namespace fw
