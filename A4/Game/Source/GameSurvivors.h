#pragma once
#include "Framework.h"
#include "Enemy.h"

class Player;
class GameCamera;

namespace fw
{
	class ResourceManager;
}

class GameSurvivors : public fw::GameCore
{
public:
	GameSurvivors(fw::FWCore* pFW);
	virtual ~GameSurvivors();

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;

	void SpawnEnemy(Enemy::EnemyType typeToSpawn);

protected:

	std::vector<fw::GameObject*> m_GameObjects;

	Player* m_pPlayer = nullptr;

	float m_SpawnTimer = 0;
	float m_SpawnRate = 1;

	GameCamera* m_pCamera = nullptr;

    fw::ResourceManager* m_pResourceManager = nullptr;

};
