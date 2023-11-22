#pragma once
#include "Framework.h"
#include "Player.h"

class A3Game : public fw::GameCore
{

    const float TimeBetweenAnimations = 0.25f;
    const int Animation_Play_Times = 13;
public:
    A3Game(fw::FWCore* pFW);
    virtual ~A3Game();

    virtual void OnKeyDown(int keyCode) override;
    virtual void OnKeyUp(int keyCode) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw() override;
    std::vector<float> GetCoords(fw::vec2 Position);


protected:
    fw::ShaderProgram* m_pWhiteShader = nullptr;
    fw::FWCore* m_pFW;
    fw::Camera* cam;
    Player* player;
    fw::Mesh* PlayerMesh;
};
