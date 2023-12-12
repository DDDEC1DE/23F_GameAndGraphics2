#pragma once

#include "Math/vec2.h"
#include "RecourceManager/RecourceManager.h"

namespace fw {

class ShaderProgram : public Resource
{
public:
    ShaderProgram();
    ShaderProgram(const char* vertFilename, const char* fragFilename);
    virtual ~ShaderProgram();

    GLuint GetProgram() { return m_Program; }

    void SetUniform1f(const char* uniformName, float value);
    void SetUniform2f(const char* uniformName, vec2 value);

    static Resource::Type GetType()
    {
        return Resource::Type::Shader;
    }

protected:
    void Cleanup();

    void CompileShader(GLuint& shaderHandle, const char* shaderString);
    bool Init(const char* vertFilename, const char* fragFilename);
    bool Reload();

protected:
    char* m_VertShaderString = nullptr;
    char* m_FragShaderString = nullptr;

    GLuint m_VertShader = 0;
    GLuint m_FragShader = 0;
    GLuint m_Program = 0;
};

} // namespace fw
