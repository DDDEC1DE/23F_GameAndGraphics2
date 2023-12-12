#include "Player.h"

Player::Player(fw::Texture* pTexture, fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, vec2 position, vec2 scale, fw::AnimationSet* animationset) :
GameObject(pTexture, pMesh, pShaderProgram, position, scale)
{
    m_AnimationPlayer = new fw::AnimationPlayer(animationset, "KnightRunAnimation");
    m_AnimationPlayer->Play();
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    m_Position += m_Velocity * deltaTime * m_Speed;
    m_AnimationPlayer->Update(deltaTime);
}

void Player::Draw(fw::Camera* pCamera)
{
    m_pMesh->Draw(m_pShader, m_AnimationPlayer->GetCurrentTexture(), m_Position, m_Scale, pCamera->m_Position, pCamera->m_ProjectionScale);
}

void Player::ProcessInput(InputOptions input, bool isPressed)
{
    switch (input)
    {
        // W
        case InputOptions::Up:
            m_Velocity += isPressed ? vec2(0, 1) : vec2(0,-1);
        break;

        // A
        case InputOptions::Left:
            m_Velocity += isPressed ? vec2(-1, 0) : vec2(1, 0);
        break;

        // S
        case InputOptions::Down:
            m_Velocity += isPressed ? vec2(0,-1) : vec2(0, 1);
        break;

        // D
        case InputOptions::Right: 
            m_Velocity += isPressed ? vec2(1, 0) : vec2(-1, 0);
        break;

        // 1
        case InputOptions::ChooseWeapon1:
            // TODO Choose weapon 1
        break;

        // 2
        case InputOptions::ChooseWeapon2:
            // TODO Choose weapon 2
        break;
    }
}