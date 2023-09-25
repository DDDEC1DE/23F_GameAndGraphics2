#include "Weapon_Gun.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"
#include "Player.h"

using namespace GameDev2D;

const int Weapon_Gun::c_NumBullets = 5;
const int Weapon_Gun::c_BulletDamage = 1;
const float Weapon_Gun::c_InitialBulletSpawnTime = 0.7f;
const float Weapon_Gun::c_BulletSpawnTimeDecreasePerLevel = 0.05f;

Weapon_Gun::Weapon_Gun(Game* pGame)
    : Weapon( pGame )
{
    // Fill a vector with bullets.
    for( int i=0; i<c_NumBullets; i++ )
    {
        Bullet* pBullet = new Bullet( pGame );
        m_Bullets.push_back( pBullet );
    }
}

Weapon_Gun::~Weapon_Gun()
{
    for( Bullet* pBullet : m_Bullets )
    {
        delete pBullet;
    }
}

void Weapon_Gun::Reset()
{
    for( Bullet* pBullet : m_Bullets )
    {
        pBullet->Reset();
    }

    m_CurrentBulletSpawnTime = c_InitialBulletSpawnTime;
    m_BulletSpawnTimer = 0;
}

void Weapon_Gun::OnUpdate(float deltaTime)
{
    for( Bullet* pBullet : m_Bullets )
    {
        if( pBullet->IsActive() )
        {
            pBullet->OnUpdate( deltaTime );
        }
    }

    if( m_pGame->IsGameOver() == false )
    {
        m_BulletSpawnTimer -= deltaTime;
        if( m_BulletSpawnTimer < 0 )
        {
            m_BulletSpawnTimer = m_CurrentBulletSpawnTime;
            SpawnBullet( m_pGame->GetPlayer()->GetPosition() );
        }
    }
}

void Weapon_Gun::OnRender(BatchRenderer& batchRenderer, bool drawDebugData)
{
    for( Bullet* pBullet : m_Bullets )
    {
        if( pBullet->IsActive() )
        {
            pBullet->OnRender( batchRenderer, drawDebugData );
        }
    }
}

void Weapon_Gun::HandleCollisions(EnemyList& enemyList)
{
    // Bullets hitting enemies.
    for( int b=0; b<c_NumBullets; b++ )
    {
        if( m_Bullets[b]->IsActive() )
        {
            Vector2 bulletPos = m_Bullets[b]->GetPosition();
            float bulletRadius = m_Bullets[b]->GetRadius();

            // Check if they collide with any enemies.
            for( size_t e=0; e<enemyList.size(); e++ )
            {
                if( enemyList[e]->IsActive() && enemyList[e]->GetHealth() > 0 )
                {
                    Vector2 EnemyPos = enemyList[e]->GetPosition();
                    Vector2 EnemyToBulletDir = (EnemyPos - bulletPos).Normalized();
                    Vector2 BulletToEnemyDir = (bulletPos - enemyList[e]->GetPosition()).Normalized();
                    float enemyhalfradius = enemyList[e]->GetRadius()/2;
                    float bullethalfradius = bulletRadius/2;
                    Vector2 BulletContactPoint = bulletPos - (bullethalfradius * BulletToEnemyDir);
                    Vector2 EnemyContactPoint = EnemyPos - (enemyhalfradius * EnemyToBulletDir);
                    float distance = BulletContactPoint.DistanceSquared(EnemyContactPoint);
                    if (distance <= pow(bulletRadius + enemyhalfradius*2, 2))
                    {
                        enemyList[e]->ApplyDamage(c_BulletDamage);
                        m_Bullets[b]->SetActive(false);
                       
                    }

                }        
            }
        }        
    }
}

void Weapon_Gun::SpawnBullet(Vector2 pos)
{
    Bullet* pBullet = nullptr;

    // Find the first inactive Bullet.
    for( int i=0; i<c_NumBullets; i++ )
    {
        if( m_Bullets[i]->IsActive() == false )
        {
            pBullet = m_Bullets[i];
            break;
        }
    }

    // Active the Bullet and send it toward the closest enemy.
    if( pBullet )
    {
        Vector2 playerPos = m_pGame->GetPlayer()->GetPosition();
        Enemy* nearestEnemy = m_pGame->GetClosestEnemy( playerPos );
        if( nearestEnemy )
        {
            pBullet->SetActive( true );
            pBullet->SetPosition( pos );

            Vector2 enemyPos = nearestEnemy->GetPosition();
            Vector2 dir = (enemyPos - playerPos).Normalized();
            pBullet->SetDirection( dir );
            pBullet;
        }
    }
}

void Weapon_Gun::ColissionCheck()
{

}

void Weapon_Gun::LevelUp()
{
    m_CurrentBulletSpawnTime -= c_BulletSpawnTimeDecreasePerLevel;
}

void Weapon_Gun::HideBullets()
{
    for (Bullet* pBullet : m_Bullets)
    {
        pBullet->HideBullet();
    }
}
