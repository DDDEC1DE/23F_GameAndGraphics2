#include "Bullet.h"

using namespace GameDev2D;

const Color Bullet::c_Color = ColorList::Green;
const float Bullet::c_Speed = 1000.0f;

Bullet::Bullet(Game* pGame)
    : GameObject(pGame)
{
    m_Radius = 1.0f;
    m_pSprite = new Sprite("Cool_Pickle");

    m_pSprite->SetAnchor(0.5f, 0.5f);
    m_pSprite->SetScale(1.0f, 1.0f);
}

Bullet::~Bullet()
{
    delete m_pSprite;
}

void Bullet::HideBullet()
{
    SetActive(false);
}

void Bullet::OnUpdate(float deltaTime)
{
    Vector2 velocity = m_Direction * c_Speed;
    m_Position += velocity * deltaTime;

    // TODO: If the bullet goes off screen, deactivate it.
    if (m_Position.x < -m_Radius
        || m_Position.x >= GameDev2D::GetScreenWidth()+ m_Radius
        || m_Position.y < -m_Radius
        || m_Position.y >= GameDev2D::GetScreenHeight()+m_Radius)
    {
        HideBullet();
    }


}

void Bullet::Reset()
{
       SetActive(false);
}

void Bullet::OnRender(BatchRenderer& batchRenderer, bool drawDebugData)
{
    m_pSprite->SetPosition(m_Position);
    batchRenderer.RenderSprite(m_pSprite);
}
