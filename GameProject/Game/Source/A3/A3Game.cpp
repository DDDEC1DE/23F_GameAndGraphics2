#include "A3Game.h"
#include "DataTypes.h"



A3Game::A3Game(fw::FWCore* pFW) : 
    fw::GameCore(pFW),
    m_pFW(pFW)
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glPointSize(20);
    glLineWidth(5);

    m_pWhiteShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/White.frag"); 
    PlayerMesh = new fw::Mesh();
    std::vector<float> playerverts = GetCoords(fw::vec2(0,0));    
    PlayerMesh->Create(playerverts, GL_TRIANGLE_FAN);

    player = new Player(pFW, PlayerMesh, m_pWhiteShader, fw::vec2(0, 0));
    cam = new fw::Camera(player->GetPosition(), 0.02f);
}


A3Game::~A3Game()
{
    delete m_pWhiteShader;
    delete cam; 
    delete player;
    delete PlayerMesh;
}



void A3Game::OnKeyDown(int keyCode)
{
    if (keyCode == VK_F1)
    {
        wglSwapInterval(1);
    }
    if (keyCode == VK_F2)
    {
        wglSwapInterval(0);
    }
     
}

void A3Game::OnKeyUp(int keyCode)
{
    

}

void A3Game::Update(float deltaTime)
{
  
     
}

void A3Game::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    PlayerMesh->Draw(m_pWhiteShader, cam, cam->m_Position);

    m_pFW->SwapBuffers();
}


 


std::vector<float> A3Game::GetCoords(fw:: vec2 Position)
{
    return  {
     Position.x - 2, Position.y,
     Position.x + 2, Position.y,
     Position.x, Position.y + 8,
     Position.x, Position.y,
     Position.x + 5, Position.y,
     Position.x, Position.y - 8,
     Position.x, Position.y,
     Position.x - 5, Position.y,
     Position.x, Position.y - 8,
     Position.x - 2, Position.y - 2,
     Position.x - 3, Position.y - 10,
     Position.x, Position.y - 8,
     Position.x + 2, Position.y - 2,
     Position.x + 3, Position.y - 10,
     Position.x, Position.y - 8,
    };
}
 