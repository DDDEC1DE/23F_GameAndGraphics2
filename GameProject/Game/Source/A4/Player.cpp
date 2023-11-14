#include "Player.h"


Player::Player(fw::FWCore* pFW, fw::Mesh* Mesh, fw::ShaderProgram* shader, fw::vec2 Position) : GameObject(pFW, Mesh, shader, Position),
m_pFW(pFW),
m_Mesh(Mesh),
m_shader(shader),
m_Position(Position)
{

}

Player::~Player()
{
}

void Player::OnKeyDown(int keyCode)
{
}

void Player::OnKeyUp(int keyCode)
{
}

void Player::Update(float deltaTime)
{
}

void Player::Draw()
{
}
