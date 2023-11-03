#pragma once

#include "CoreHeaders.h"
#include "Math/vec2.h"

namespace fw {

class ShaderProgram;

struct VertexFormat
{
    float position[2];
    float uv[2];
};
class Mesh
{
public:
    Mesh();
    Mesh(const Mesh& other) = delete;
    Mesh& operator=(const Mesh& other) = delete;
    virtual ~Mesh();

    void Create(const std::vector<VertexFormat>& verts, GLenum primitiveType);
    void Draw(ShaderProgram* pShader, vec2 offset);


    GLuint m_VBO = 0;
    int m_NumVerts = 0;
    GLenum m_PrimitiveType = GL_POINTS;
};

} // namespace fw
