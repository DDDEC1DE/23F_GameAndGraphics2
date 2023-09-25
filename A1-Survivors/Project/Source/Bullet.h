#pragma once

#include <GameDev2D.h>
#include "GameObject.h"

using namespace GameDev2D;

class Bullet : public GameObject
{
private:
    static const Color c_Color;
    static const float c_Speed;

public:
    Bullet(Game* pGame);
    virtual ~Bullet();
    void HideBullet();
    virtual void OnUpdate(float deltaTime) override;
    void Reset() override;
    // Getters.
    Vector2 GetDirection() { return m_Direction; }
    Vector2 GetSpritePosition() { return m_pSprite->GetPosition(); }
    // Setters.
    void SetDirection(Vector2 dir) { m_Direction = dir; }

    virtual void OnRender(BatchRenderer& batchRenderer, bool drawDebugData) override;
private:
    Vector2 m_Direction = Vector2(0,0);
    Sprite* m_pSprite = nullptr;
};
