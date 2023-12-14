#include "Enemy.h"


Enemy::Enemy(fw::Texture* pTexture, fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, fw::GameObject* pPlayer, vec2 position, vec2 scale):
GameObject(pTexture, pMesh, pShaderProgram, position, scale),
m_pPlayer(pPlayer)
{

}

Enemy::~Enemy()
{
}

void Enemy::Update(float deltaTime)
{
    m_Velocity = m_pPlayer->GetPosition() - m_Position;

    float magnitude = vec2::Magnitude(m_Velocity);
    if (magnitude == 0)
    {
        m_Velocity = vec2(0, 0);
    }
    else
    {
        m_Velocity /= magnitude;
    }

    m_Position += m_Velocity * deltaTime * m_Speed;
}
