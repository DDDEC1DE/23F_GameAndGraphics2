#pragma once

#include <GameDev2D.h>
#include "Weapon.h"

using namespace GameDev2D;

class PoopBullet;

class Weapon_Pooper : public Weapon
{
private:
    static const int c_NumBullets;
    static const int c_BulletDamage;
    static const float c_InitialBulletSpawnTime;
    static const float c_BulletSpawnTimeDecreasePerLevel;

public:
    Weapon_Pooper(Game* pGame);
    virtual ~Weapon_Pooper();

    virtual void Reset() override;
    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender(BatchRenderer& batchRenderer, bool drawDebugData) override;
    virtual void HandleCollisions(EnemyList& enemyList) override;
    virtual void LevelUp() override;

    virtual void HideBullets() override;
    void SpawnBullet(Vector2 pos);
    void ColissionCheck();
private:
    std::vector<PoopBullet*> m_Bullets;
    bool stop = false;
    float m_CurrentBulletSpawnTime = 0.0f;
    float m_BulletSpawnTimer = 0.0f;
};
