#pragma once

#include "Framework.h"
#include "Datatypes.h"

class Enemy : public fw::GameObject
{
public:
    
    enum class EnemyType
    {
        Flyer
    };

    virtual void Update(float deltaTime) override;

    Enemy(fw::Texture* pTexture, fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::GameObject* pPlayer, vec2 position, vec2 scale);
    ~Enemy();

protected:

    vec2 m_Velocity = vec2(0,0);
    float m_Speed = 6.0f;
    fw::GameObject* m_pPlayer = nullptr;

    EnemyType m_Type = EnemyType::Flyer;
};
