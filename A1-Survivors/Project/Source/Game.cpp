#include "Game.h"
#include "Enemy.h"
#include "Pickup.h"
#include "Player.h"
#include "Weapon_Pooper.h"
#include "Weapon_Gun.h"

const int Game::c_NumEnemies = 16;
const int Game::c_NumPickups = 300;
const int Game::c_InitialXPRequiredToLevelUp = 10;
const float Game::c_XPMultiplierPerLevel = 1.5f;
const float Game::c_InitialEnemySpawnTime = 3.0f;

using namespace GameDev2D;

Game::Game()
    : m_Font("OpenSans-CondBold_32")
{
    // Create the background.
    m_pBG = new Sprite("BG");

    // Create a player.
    m_pPlayer = new Player(this);

    m_Weapons.push_back(new Weapon_Pooper(this));
    m_Weapons.push_back(new Weapon_Gun(this));

    // Fill a vector with enemies.


    // Fill a vector with pickups.
    for (int i = 0; i < c_NumPickups; i++)
    {
        Pickup* pPickup = new Pickup(this);
        m_Pickups.push_back(pPickup);
    }
    for (int i = 0; i < c_NumEnemies; i++)
    {
        Enemy* pEnemy = new Enemy(this);
        pEnemy->SetActive(false);
        m_Enemies.push_back(pEnemy);
    }
    Reset();
}

Game::~Game()
{
    // Delete all objects.
    delete m_pPlayer;

    for (Weapon* pWeapon : m_Weapons)
    {
        delete pWeapon;
    }

    for (Enemy* pEnemy : m_Enemies)
    {
        delete pEnemy;
    }

    for (Pickup* pPickup : m_Pickups)
    {
        delete pPickup;
    }
}

void Game::Reset()
{
    m_GameOver = false;
    m_EnemiesKilled = 0;
    m_ExperiencePoints = 0;
    m_TimePlayed = 0;
    m_CurrentXPRequiredToLevelUp = c_InitialXPRequiredToLevelUp;

    m_EnemySpawnTimer = 0;

    for (Weapon* pWeapon : m_Weapons)
    {
        pWeapon->Reset();
    }

    for (Enemy* pEnemy : m_Enemies)
    {
        pEnemy->Reset();
    }

    for (Pickup* pPickup : m_Pickups)
    {
        pPickup->Reset();
    }

    m_pPlayer->Reset();
    m_pPlayer->SetActive(true);
    m_pPlayer->SetPosition(Vector2(GameDev2D::GetScreenWidth() / 2.0f, GameDev2D::GetScreenHeight() / 2.0f));


    for (int i = 0; i < 10; i++)
    {
        SpawnEnemies();
    }



}

void Game::OnUpdate(float deltaTime)
{
    if (m_GameOver == false)
    {
        m_TimePlayed += deltaTime;
    }

    // Update the player, enemies and pickups.
    if (m_GameOver == false)
    {
        m_pPlayer->OnUpdate(deltaTime);


        m_Weapons[currentWeaponIndex]->OnUpdate(deltaTime);
        m_Weapons[currentWeaponIndex]->HandleCollisions(m_Enemies);


        for (Enemy* pEnemy : m_Enemies)
        {
            if (pEnemy->IsActive())
            {

                pEnemy->OnUpdate(deltaTime);
            }
        }

        for (Pickup* pPickup : m_Pickups)
        {
            if (pPickup->IsActive())
            {
                pPickup->OnUpdate(deltaTime);
            }
        }

        // Update timers and spawn objects if needed.

        m_EnemySpawnTimer -= deltaTime;
        if (m_EnemySpawnTimer < 0)
        {
            m_EnemySpawnTimer = c_InitialEnemySpawnTime;
            SpawnEnemies();
        }




        GetClosestEnemy(m_pPlayer->GetPosition());

        // Handle collisions.
        HandleCollisions();

        // Handle xp, leveling up and weapon upgrades.
        HandleXP();
    }
}

void Game::OnRender(BatchRenderer& batchRenderer)
{
    batchRenderer.BeginScene();

    // Render the bg, active enemies/pickups/weapons and the player.
    batchRenderer.RenderSprite(m_pBG);

    for (Pickup* pPickup : m_Pickups)
    {
        if (pPickup->IsActive())
        {
            pPickup->OnRender(batchRenderer, m_DrawDebugData);
        }
    }

    for (Weapon* pWeapon : m_Weapons)
    {
        pWeapon->OnRender(batchRenderer, m_DrawDebugData);
    }


    for (Enemy* pEnemy : m_Enemies)
    {
        if (pEnemy->IsActive())
        {
            pEnemy->OnRender(batchRenderer, m_DrawDebugData);
        }
    }

    if (m_GameOver == false)
    {
        m_pPlayer->OnRender(batchRenderer, m_DrawDebugData);
    }

    // Draw some text.
    if (true)
    {
        char tempString[100];
        sprintf_s(tempString, 100, "Time: %0.0f", m_TimePlayed);
        m_Font.SetText(tempString);
        m_Font.SetPosition(200, 5);
        batchRenderer.RenderSpriteFont(m_Font);

        sprintf_s(tempString, 100, "Kills: %d", m_EnemiesKilled);
        m_Font.SetText(tempString);
        m_Font.SetPosition(500, 5);
        batchRenderer.RenderSpriteFont(m_Font);

        sprintf_s(tempString, 100, "XP: %d / %d", m_ExperiencePoints, m_CurrentXPRequiredToLevelUp);
        m_Font.SetText(tempString);
        m_Font.SetPosition(800, 5);
        batchRenderer.RenderSpriteFont(m_Font);




        sprintf_s(tempString, 100, "1 - Poop flinger \n2 - Pickle shooter");
        m_Font.SetText(tempString);
        m_Font.SetPosition(800, 650);
        batchRenderer.RenderSpriteFont(m_Font);
    }

    batchRenderer.EndScene();
}

void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
{
    if (keyCode == KeyCode::One && keyState == KeyState::Down)
    {
        m_Weapons[currentWeaponIndex]->HideBullets();
        currentWeaponIndex = 0;
    }
    if (keyCode == KeyCode::Two && keyState == KeyState::Down)
    {
        m_Weapons[currentWeaponIndex]->HideBullets();
        currentWeaponIndex = 1;
    }
    if (keyCode == KeyCode::Escape)
    {
        Application::Get().Quit();
    }

    if (keyCode == KeyCode::R && keyState == KeyState::Down)
    {
        Reset();
    }

    if (keyCode == KeyCode::F1 && keyState == KeyState::Down)
    {
        m_DrawDebugData = !m_DrawDebugData;
    }

    // Debug leveling up.
    if (keyCode == KeyCode::X && keyState == KeyState::Down)
    {
        m_ExperiencePoints += m_CurrentXPRequiredToLevelUp;
    }

    // Send key events to the player.
    m_pPlayer->OnKeyEvent(keyCode, keyState);
}

void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
{
}

void Game::OnMouseMovedEvent(float mouseX, float mouseY)
{
}

void Game::SpawnEnemies()
{

    int side = Math::RandomInt(0, 3);
    Vector2 pos;
    if (side == 0) // Left
    {
        pos = Vector2(Math::RandomFloat(-264, -64), Math::RandomFloat(0, 704));
    }
    else if (side == 1) // Right
    {
        pos = Vector2(Math::RandomFloat(1280, 1480), Math::RandomFloat(0, 704));
    }
    else if (side == 2) // Top
    {
        pos = Vector2(Math::RandomFloat(0, 1280), Math::RandomFloat(704, 904));
    }
    else if (side == 3) // Bottom
    {
        pos = Vector2(Math::RandomFloat(0, 1280), Math::RandomFloat(-264, -64));
    }

    SpawnEnemy(pos);

}

void Game::SpawnEnemy(Vector2 pos)
{
    Enemy* pEnemy = new Enemy(this);
    pEnemy->SetActive(true);
    pEnemy->SetPosition(pos);
    // Find the first inactive Enemy.

    if (m_Enemies.size() > 0)
    {
        bool AddEnemy = true;
        for (int i = 0; i < m_Enemies.size(); i++)
        {
            if (m_Enemies[i]->IsActive() == false)
            {
                m_Enemies[i] = pEnemy;
                AddEnemy = false;
                break;
            }
        }
        //m_Enemies.push_back(pEnemy);
    }
    else
    {
        m_Enemies.push_back(pEnemy);
    }
}

void Game::SpawnPickup(Vector2 pos)
{
    Pickup* pPickup = new Pickup(this);


    pPickup->SetActive(true);
    pPickup->SetPosition(pos);
    if (m_Pickups.size() > 0)
    {
        for (int i = 0; i < m_Pickups.size(); i++)
        {
            if (m_Pickups[i]->IsActive() == false)
            {
                m_Pickups[i] = pPickup;
                break;
            }
        }
    }
    else
    {
        m_Pickups.push_back(pPickup);
    }
}

void Game::HandleCollisions()
{
    // Weapons hitting enemies.
    for (Weapon* pWeapon : m_Weapons)
    {
        pWeapon->HandleCollisions(m_Enemies);
    }

    // Enemies hitting the player.
    for (int e = 0; e < c_NumEnemies; e++)
    {
        if (m_Enemies[e]->IsActive() && !m_Enemies[e]->IsFadingOut())
        {
            Vector2 EnemyPos = m_Enemies[e]->GetSpritePos();
            float EnemyRadius = m_Enemies[e]->GetRadius();


            Vector2 PlayerPos = m_pPlayer->GetPosition();
            Vector2 PlayerToEnemyDir = (PlayerPos - EnemyPos).Normalized();
            Vector2 EnemyToPlayerDir = (EnemyPos - m_pPlayer->GetPosition()).Normalized();
            float Playerhalfradius = m_pPlayer->GetRadius() / 2;
            float Enemyhalfradius = EnemyRadius / 2;
            Vector2 EnemyContactPoint = EnemyPos - (Enemyhalfradius * EnemyToPlayerDir);
            Vector2 PlayerContactPoint = PlayerPos - (Playerhalfradius * PlayerToEnemyDir);
            float distance = EnemyContactPoint.DistanceSquared(PlayerContactPoint);
            if (distance <= pow(EnemyRadius + Playerhalfradius * 2, 2))
            {
                m_pPlayer->SetActive(false);
                m_GameOver = true;
            }



        }
    }

    // Player hitting pickups.
    for (int p = 0; p < c_NumPickups; p++)
    {
        if (m_Pickups[p]->IsActive() && !m_Pickups[p]->IsAnimating())
        {
            Vector2 pickupPos = m_Pickups[p]->GetPosition();
            float pickupRadius = m_Pickups[p]->GetRadius();

            // Check if they collide with the player.
            Vector2 playerPos = m_pPlayer->GetPosition();
            float playerPickupRadius = m_pPlayer->GetPickupRadius();

            if (playerPos.Distance(pickupPos) < playerPickupRadius + pickupRadius)
            {
                m_Pickups[p]->PickupObject(playerPos);
                m_ExperiencePoints++;
            }
        }
    }
}

void Game::HandleXP()
{
    if (m_ExperiencePoints >= m_CurrentXPRequiredToLevelUp)
    {
        m_ExperiencePoints -= m_CurrentXPRequiredToLevelUp;
        m_CurrentXPRequiredToLevelUp = (int)(m_CurrentXPRequiredToLevelUp * c_XPMultiplierPerLevel);

        for (Weapon* pWeapon : m_Weapons)
        {
            pWeapon->LevelUp();
        }
    }
}

void Game::OnEnemyKilled(Vector2 location)
{
    SpawnEnemies();
    SpawnPickup(location);
    m_EnemiesKilled++;
}

Enemy* Game::GetClosestEnemy(Vector2 pos)
{
    float closestDistance = FLT_MAX;
    Enemy* pClosestEnemy = nullptr;

    for (int i = 0; i < c_NumEnemies; i++)
    {
        if (m_Enemies[i]->IsActive())
        {
            Vector2 enemyPos = m_Enemies[i]->GetPosition();
            float enemySize = m_Enemies[i]->GetRadius() / 2;

            // Don't target enemies that are offscreen.
            if (enemyPos.x < enemySize || enemyPos.x > GameDev2D::GetScreenWidth() - enemySize ||
                enemyPos.y < enemySize || enemyPos.y > GameDev2D::GetScreenHeight() - enemySize)
            {
                continue;
            }
            else
            {

                float distance = m_Enemies[i]->GetPosition().Distance(pos);
                if (distance < closestDistance)
                {
                    closestDistance = distance;
                    pClosestEnemy = m_Enemies[i];
                }
                FoundClosestEnemy = true;
            }
        }
    }

    return pClosestEnemy;
}
