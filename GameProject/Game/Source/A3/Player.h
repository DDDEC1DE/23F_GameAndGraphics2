#pragma once

#include "Framework.h"

 
class Player : public fw::GameObject
{
public:
    Player( fw::FWCore* pFW, fw::Mesh* Mesh, fw::ShaderProgram* shader, fw::vec2 Position);
	~Player();

   


    virtual void OnKeyDown(int keyCode) override;
    virtual void OnKeyUp(int keyCode) override;
    virtual void Update(float deltaTime) override;
    virtual void Draw()override;
    void SetPosition(fw::vec2 position) { m_Position = position; }
    fw::vec2 GetPosition() { return m_Position; }

private:
    fw::Mesh* m_Mesh;
    fw::FWCore* m_pFW;
    fw::ShaderProgram* m_shader;
    fw::vec2 m_Position;
};
