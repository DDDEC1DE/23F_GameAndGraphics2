#include "GameObject.h"
#include "Texture.h"
#include "Camera/Camera.h"
#include "Mesh.h"

namespace fw {

    GameObject::GameObject(Texture* pTexture, Mesh* pMesh, ShaderProgram* pShaderProgram, vec2 position, vec2 scale):
        m_Position(position),
        m_Scale(scale),
        m_pTexture(pTexture),
        m_pMesh(pMesh),
        m_pShader(pShaderProgram)
    {
    }

    GameObject::~GameObject()
    {
    }

    void GameObject::Update(float deltaTime)
    {
    }

    vec2 GameObject::GetPosition()
    {
        return m_Position;
    }

    vec2 GameObject::GetScale()
    {
        return m_Scale;
    }

    Texture* GameObject::GetTexture()
    {
        return m_pTexture;
    }

    void GameObject::Draw(Camera* pCamera)
    {
        m_pMesh->Draw(m_pShader, m_pTexture, m_Position, m_Scale, pCamera->m_Position, pCamera->m_ProjectionScale);
    }

    void GameObject::AddTag(std::string newTag)
    {
        if (std::find(m_Tags.begin(), m_Tags.end(), newTag) != m_Tags.end())
        {
            return;
        }

        m_Tags.push_back(newTag);
    }

    void GameObject::RemoveTag(std::string newTag)
    {
        m_Tags.erase(std::remove(m_Tags.begin(), m_Tags.end(), newTag), m_Tags.end());
    }

    bool GameObject::HasTag(std::string tag)
    {
        return (std::find(m_Tags.begin(), m_Tags.end(), tag) != m_Tags.end());
    }
} // namespace fw
