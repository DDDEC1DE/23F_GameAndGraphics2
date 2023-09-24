#pragma once

#include <GameDev2D.h>
#include "GameObject.h"

using namespace GameDev2D;

class PoopBullet : public GameObject
{
private:
    static const Color c_Color;
    static const float c_Speed;

public:
    PoopBullet(Game* pGame);
    virtual ~PoopBullet();

    virtual void OnUpdate(float deltaTime) override;
    void SetVariables(Vector2 StartingPoint, Vector2 ControlPoint, Vector2 EndingPoint);
    // Getters.
    Vector2 GetDirection() { return m_Direction; }
    Vector2 GetSpritePosition() { return m_pSprite->GetPosition(); }
    // Setters.
    void SetDirection(Vector2 dir) { m_Direction = dir; }

    virtual void OnRender(BatchRenderer& batchRenderer, bool drawDebugData) override;
private:
    float m_t = 0;
    Vector2 m_StartingPoint;  
    Vector2 m_EndingPoint;    
    Vector2 m_ControlPoint;
    Vector2 m_Direction = Vector2(0,0);
    Sprite* m_pSprite = nullptr;
};
