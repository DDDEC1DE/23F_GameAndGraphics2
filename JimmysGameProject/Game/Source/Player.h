#pragma once

#include "Framework.h"
#include "Datatypes.h"

#include "Animation/Animation.h"

class Player : public fw::GameObject
{

public:

    enum class InputOptions
    {
        Up = 0,
        Down,
        Left,
        Right,
        Attack,
        ChooseWeapon1,
        ChooseWeapon2
    };

    virtual void Update(float deltaTime) override;
    virtual void Draw(fw::Camera* pCamera) override;

    Player(fw::Texture* pTexture, fw::Mesh* pMesh, fw::ShaderProgram* pShaderProgram, vec2 position, vec2 scale, fw::AnimationSet* animationSet);
    ~Player();

    void ProcessInput(InputOptions input, bool isPressed);

protected:

    vec2 m_Velocity;
    float m_Speed = 15.0f;
    fw::AnimationPlayer* m_AnimationPlayer = nullptr;
};
