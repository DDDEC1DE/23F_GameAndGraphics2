#include "GameSurvivors.h"
#include "DataTypes.h"
#include "Player.h"
#include "GameCamera.h"

#include "RecourceManager/RecourceManager.h"
#include "Animation/Animation.h"

GameSurvivors::GameSurvivors(fw::FWCore* pFW) : fw::GameCore(pFW)
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glPointSize(20);
    glLineWidth(5);

    m_pResourceManager = new fw::ResourceManager();
    
    m_pResourceManager->Add("BasicShader", new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/White.frag"));
    m_pResourceManager->Add("FlowerTexture", new fw::Texture("Data/Textures/Flower.png"));
    m_pResourceManager->Add("BackgroundTexture", new fw::Texture("Data/Textures/BG.png"));

    // Animation setup
    {
        m_pResourceManager->Add("player_down_1",    new fw::Texture("Data/Textures/player_down1.png"));
        m_pResourceManager->Add("player_down_2",    new fw::Texture("Data/Textures/player_down2.png"));
        m_pResourceManager->Add("player_down_3",    new fw::Texture("Data/Textures/player_down3.png"));
        m_pResourceManager->Add("player_up_1",      new fw::Texture("Data/Textures/player_up1.png"));
        m_pResourceManager->Add("player_up_2",      new fw::Texture("Data/Textures/player_up2.png"));
        m_pResourceManager->Add("player_up_3",      new fw::Texture("Data/Textures/player_up3.png"));
        m_pResourceManager->Add("player_left_1",    new fw::Texture("Data/Textures/player_left1.png"));
        m_pResourceManager->Add("player_left_2",    new fw::Texture("Data/Textures/player_left2.png"));
        m_pResourceManager->Add("player_left_3",    new fw::Texture("Data/Textures/player_left3.png"));
        m_pResourceManager->Add("player_right_1",   new fw::Texture("Data/Textures/player_right1.png"));
        m_pResourceManager->Add("player_right_2",   new fw::Texture("Data/Textures/player_right2.png"));
        m_pResourceManager->Add("player_right_3",   new fw::Texture("Data/Textures/player_right3.png"));

        fw::Animation* player_up_anim = new fw::Animation();
        player_up_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_up_1"));
        player_up_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_up_2"));
        player_up_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_up_3"));
        player_up_anim->m_bIsLooping = true;

        m_pResourceManager->Add("Walk_up", player_up_anim);
        
        fw::Animation* player_right_anim = new fw::Animation();
        player_right_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_right_1"));
        player_right_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_right_2"));
        player_right_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_right_3"));
        player_right_anim->m_bIsLooping = true;

        m_pResourceManager->Add("Walk_right", player_right_anim);    
        
        fw::Animation* player_left_anim = new fw::Animation();
        player_left_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_left_1"));
        player_left_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_left_2"));
        player_left_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_left_3"));
        player_left_anim->m_bIsLooping = true;

        m_pResourceManager->Add("Walk_left", player_left_anim);       
        
        fw::Animation* player_down_anim = new fw::Animation();
        player_down_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_down_1"));
        player_down_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_down_2"));
        player_down_anim->AddFrame(m_pResourceManager->GetResource<fw::Texture>("player_down_3"));
        player_down_anim->m_bIsLooping = true;

        m_pResourceManager->Add("Walk_down", player_down_anim);

        fw::AnimationSet* sokoban_animation_set = new fw::AnimationSet();
        sokoban_animation_set->m_AnimationList["Walk_up"]    = player_up_anim;
        sokoban_animation_set->m_AnimationList["Walk_right"] = player_right_anim;
        sokoban_animation_set->m_AnimationList["Walk_left"]  = player_left_anim;
        sokoban_animation_set->m_AnimationList["Walk_down"]  = player_down_anim;

        m_pResourceManager->Add("PlayerAnimationSet", sokoban_animation_set);
    }

    m_pResourceManager->Add("EnemyFlyerTexture", new fw::Texture("Data/Textures/fly_anim_f1.png"));

    std::vector<fw::VertexFormat> attribs =
    {
        { -25,  25,  0.0f, 1.0f },
        {  25,  25,  1.0f, 1.0f },
        { -25, -25,  0.0f, 0.0f },
        {  25, -25,  1.0f, 0.0f },
    };

    fw::Mesh* SquareMesh = new fw::Mesh();
    SquareMesh->Create(attribs, GL_TRIANGLE_STRIP);
    m_pResourceManager->Add("SquareMesh", SquareMesh);

    fw::GameObject* BackgroundObject = new fw::GameObject
    (
        m_pResourceManager->GetResource<fw::Texture>("BackgroundTexture"), 
        m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
        m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
        vec2(50, 50), 
        vec2(3.555f, 2)
    );
    m_GameObjects.push_back(BackgroundObject);

    // Add CameraAnchors
    {
        fw::GameObject* CameraAnchor1 = new fw::GameObject
        (
            m_pResourceManager->GetResource<fw::Texture>("FlowerTexture"),
            m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
            m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
            vec2(85, 85),
            vec2(0.1f, 0.1f)
        );

        CameraAnchor1->AddTag("CameraFollow");
        m_GameObjects.push_back(CameraAnchor1);
        
        fw::GameObject* CameraAnchor2 = new fw::GameObject
        (
            m_pResourceManager->GetResource<fw::Texture>("FlowerTexture"),
            m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
            m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
            vec2(15, 85),
            vec2(0.1f, 0.1f)
        );

        CameraAnchor2->AddTag("CameraFollow");
        m_GameObjects.push_back(CameraAnchor2);
        
        fw::GameObject* CameraAnchor3 = new fw::GameObject
        (
            m_pResourceManager->GetResource<fw::Texture>("FlowerTexture"),
            m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
            m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
            vec2(85, 15),
            vec2(0.1f, 0.1f)
        );

        CameraAnchor3->AddTag("CameraFollow");
        m_GameObjects.push_back(CameraAnchor3);
        
        fw::GameObject* CameraAnchor4 = new fw::GameObject
        (
            m_pResourceManager->GetResource<fw::Texture>("FlowerTexture"),
            m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
            m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
            vec2(15, 15),
            vec2(0.1f, 0.1f)
        );

        CameraAnchor4->AddTag("CameraFollow");
        m_GameObjects.push_back(CameraAnchor4);

    }
    

    m_pPlayer = new Player
    (
        m_pResourceManager->GetResource<fw::Texture>("KnightRunTexture_f1"),
        m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
        m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
        vec2(50, 50),
        vec2(0.1f, 0.1f),
        m_pResourceManager->GetResource<fw::AnimationSet>("PlayerAnimationSet")
    ); 
    
    m_pCamera = new GameCamera(fw::vec2(50, 50), 50);
    m_pCamera->AddNewTrackedObject(m_pPlayer);
}

GameSurvivors::~GameSurvivors()
{
    for (fw::GameObject* gameobject : m_GameObjects)
    {
        delete gameobject;
        gameobject = nullptr;
    }

    delete m_pPlayer;
    m_pPlayer = nullptr;
}

void GameSurvivors::OnKeyDown(int keyCode)
{
    switch (keyCode)
    {
        // W
        case 87: m_pPlayer->ProcessInput(Player::InputOptions::Up, true);
        break;

        // A
        case 65: m_pPlayer->ProcessInput(Player::InputOptions::Left, true);
        break;

        // S
        case 83: m_pPlayer->ProcessInput(Player::InputOptions::Down, true);
        break;

        // D
        case 68: m_pPlayer->ProcessInput(Player::InputOptions::Right, true);
        break;

        // X
        case 88: m_pCamera->RemoveLastTrackedObject();
        break;

        // 1
        case 49: m_pPlayer->ProcessInput(Player::InputOptions::ChooseWeapon1, true);
        break;

        // 2
        case 50: m_pPlayer->ProcessInput(Player::InputOptions::ChooseWeapon2, true);
        break;

        // V-Sync on
        case VK_F1: wglSwapInterval(1);
        break;

        // V-Sync off
        case VK_F2: wglSwapInterval(0);
        break;
    }
}

void GameSurvivors::OnKeyUp(int keyCode)
{
    switch (keyCode)
    {
        // W
        case 87: m_pPlayer->ProcessInput(Player::InputOptions::Up, false);
        break;

        // A
        case 65: m_pPlayer->ProcessInput(Player::InputOptions::Left, false);
        break;

        // S
        case 83: m_pPlayer->ProcessInput(Player::InputOptions::Down, false);
        break;

        // D
        case 68: m_pPlayer->ProcessInput(Player::InputOptions::Right, false);
        break;

        // 1
        case 49: m_pPlayer->ProcessInput(Player::InputOptions::ChooseWeapon1, false);
        break;

        // 2
        case 50: m_pPlayer->ProcessInput(Player::InputOptions::ChooseWeapon2, false);
        break;
    }
}

void GameSurvivors::Update(float deltaTime)
{
    // Spawn enemies on timer
    m_SpawnTimer += deltaTime;
    if (m_SpawnRate > 0 && m_SpawnTimer >= 1 / m_SpawnRate)
    {
        m_SpawnTimer = 0;
        SpawnEnemy(Enemy::EnemyType::Flyer);
    }

    m_pPlayer->Update(deltaTime);

    for (fw::GameObject* gameobject : m_GameObjects)
    {
        gameobject->Update(deltaTime);

        if (gameobject->HasTag("CameraFollow") && vec2::Magnitude(gameobject->GetPosition() - m_pPlayer->GetPosition()) < 5)
        {
            m_pCamera->AddNewTrackedObject(gameobject);
        }
    }

    m_pCamera->Update(deltaTime);
}

void GameSurvivors::SpawnEnemy(Enemy::EnemyType typeToSpawn)
{
    fw::GameObject* newEnemy = nullptr;

    vec2 SpawnPoint(-10, -10);

    switch (typeToSpawn)
    {
    case Enemy::EnemyType::Flyer:
        newEnemy = new Enemy(
            m_pResourceManager->GetResource<fw::Texture>("EnemyFlyerTexture"),
            m_pResourceManager->GetResource<fw::Mesh>("SquareMesh"),
            m_pResourceManager->GetResource<fw::ShaderProgram>("BasicShader"),
            m_pPlayer,
            SpawnPoint, 
            vec2(0.2f, 0.2f)
        );
        break;
    }

    m_GameObjects.push_back(newEnemy);
}

void GameSurvivors::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for (fw::GameObject* gameobject : m_GameObjects)
    {
        gameobject->Draw(m_pCamera);
    }

    m_pPlayer->Draw(m_pCamera);

    m_pFW->SwapBuffers();
}
