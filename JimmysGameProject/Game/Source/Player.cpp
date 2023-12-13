#include "Player.h"

Player::Player(fw::Texture* pTexture, fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, vec2 position, vec2 scale, fw::AnimationSet* animationset) :
    GameObject(pTexture, pMesh, pShaderProgram, position, scale)
{
    m_AnimationPlayer = new fw::AnimationPlayer(animationset, "Walk_down");
    m_AnimationPlayer->Rewind();
    m_AnimationPlayer->Stop();
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
    case InputOptions::Up:
        m_Velocity += isPressed ? vec2(0, 1) : vec2(0, -1);
        DirectionInputChanged();
        break;

    case InputOptions::Left:
        m_Velocity += isPressed ? vec2(-1, 0) : vec2(1, 0);
        DirectionInputChanged();
        break;

    case InputOptions::Down:
        m_Velocity += isPressed ? vec2(0, -1) : vec2(0, 1);
        DirectionInputChanged();
        break;

    case InputOptions::Right:
        m_Velocity += isPressed ? vec2(1, 0) : vec2(-1, 0);
        DirectionInputChanged();
        break;

    case InputOptions::ChooseWeapon1:
        // TODO Choose weapon 1
        break;

    case InputOptions::ChooseWeapon2:
        // TODO Choose weapon 2
        break;
    }
}

void Player::DirectionInputChanged()
{
    if (vec2::Magnitude(m_Velocity) == 0)
    {
        m_AnimationPlayer->Stop();
    }
    else
    {
        if (!m_AnimationPlayer->GetIsPlaying())
            m_AnimationPlayer->Play();

        if (m_Velocity.x != 0)
        {
            m_AnimationPlayer->SetAnimation(m_Velocity.x > 0 ? "Walk_right" : "Walk_left");
        }
        else
        {
            m_AnimationPlayer->SetAnimation(m_Velocity.y > 0 ? "Walk_up" : "Walk_down");
        }
    }
}