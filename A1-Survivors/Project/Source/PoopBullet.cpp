#include "PoopBullet.h"

using namespace GameDev2D;

const Color PoopBullet::c_Color = ColorList::Green;
const float PoopBullet::c_Speed = 1.5f;

PoopBullet::PoopBullet(Game* pGame)
    : GameObject(pGame)
{
    m_Radius = 1.0f;
    m_pSprite = new Sprite("funny_kaka");

    m_pSprite->SetAnchor(0.5f, 0.5f);
    m_pSprite->SetScale(1.0f, 1.0f);
}

PoopBullet::~PoopBullet()
{
    delete m_pSprite;
}

void PoopBullet::OnUpdate(float deltaTime)
{
    // Initialize t somewhere, maybe in Reset() method, and set it to 0
    // Increment t here; Make sure it stays within [0, 1]
    m_t += deltaTime * c_Speed;  // you can change the speed here
    if (m_t > 1.0f) m_t = 1.0f;

    Vector2 P0 = m_StartingPoint;  // the initial firing position
    Vector2 P1 = m_EndingPoint;    // the target position
    Vector2 P2 = m_ControlPoint;   // some point that the bullet should pass through

    // Compute the new position along the Bezier curve
    Vector2 newPosition = pow((1 - m_t), 2) * P0 + 2 * (1 - m_t) * m_t * P2 + pow(m_t, 2) * P1;

    // Update the bullet's position
    SetPosition(newPosition);


    // TODO: If the PoopBullet goes off screen, deactivate it.
    if (m_Position.x < -m_Radius
        || m_Position.x >= GameDev2D::GetScreenWidth()+ m_Radius
        || m_Position.y < -m_Radius
        || m_Position.y >= GameDev2D::GetScreenHeight()+m_Radius)
    {
        SetActive(false);
    }


}

void PoopBullet::SetVariables(Vector2 StartingPoint, Vector2 ControlPoint, Vector2 EndingPoint)
{
    m_StartingPoint = StartingPoint;
    m_ControlPoint = ControlPoint;
    m_EndingPoint = EndingPoint;
    m_t = 0;
}

void PoopBullet::Reset()
{
       SetActive(false);
}

void PoopBullet::OnRender(BatchRenderer& batchRenderer, bool drawDebugData)
{
    m_pSprite->SetPosition(m_Position);
    batchRenderer.RenderSprite(m_pSprite);
}
