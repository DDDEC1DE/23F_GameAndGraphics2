#pragma once

#include "CoreHeaders.h"
#include "Math/vec2.h"
#include <string>

namespace fw 
{
    class Texture;
    class Mesh;
    class Camera;
    class ShaderProgram;

    class GameObject
    {
    public:
        GameObject(Texture* pTexture, Mesh* pMesh, ShaderProgram* pShaderProgram, vec2 position = vec2(0, 0), vec2 scale = vec2(1, 0));
        ~GameObject();

        vec2 GetPosition();
        vec2 GetScale();
        Texture* GetTexture();

        virtual void Update(float deltaTime);

        virtual void Draw(Camera* pCamera);

        void AddTag(std::string newTag);
        void RemoveTag(std::string newTag);
        bool HasTag(std::string tag);

    protected:
        vec2 m_Position;
        vec2 m_Scale;
        Texture* m_pTexture;

        Mesh* m_pMesh;
        ShaderProgram* m_pShader;

        std::vector<std::string> m_Tags;
    };

} // namespace fw
