#pragma once

#include "CoreHeaders.h"
#include "Math/vec2.h"

namespace fw {

struct VertexFormat
{
    float position[2];
    float uv[2];
};
    
class ShaderProgram;
class Texture;

class Mesh
{
public:
    Mesh();
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;
    virtual ~Mesh();

    void Create(std::vector<VertexFormat>& verts, GLenum primitiveType);
    void Draw(ShaderProgram* pShader, Texture* pTexture, vec2 offset);

protected:
    GLuint m_VBO = 0;
    int m_NumVerts = 0;
    GLenum m_PrimitiveType = GL_POINTS;
};

} // namespace fw
