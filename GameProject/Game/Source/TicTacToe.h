#pragma once
#include "Framework.h"
#include "Slot.h"
#include <random>
class TicTacToe : public fw::GameCore
{

	const float TimeBetweenAnimations = 0.25f;
	const int Animation_Play_Times= 13;
public:
	TicTacToe(fw::FWCore* pFW);
	virtual ~TicTacToe();

	virtual void OnKeyDown(int keyCode) override;
	virtual void OnKeyUp(int keyCode) override;
	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	void CreateCircle(fw::intvec2 Position);
	void CreateX(fw::intvec2 Position);
	void CreateStar(fw::intvec2 Position);
	fw::intvec2 GetMousePos();
	bool IsMouseDown();
	Slot* FillSlot(fw::intvec2 position, ESlotState newstate);
	ESlotState CheckForWin();
	void Reset();
	void GameInProgress();
	void WinCondition(float delta);
	void Win();
	
protected:
	fw::ShaderProgram* m_pWhiteShader = nullptr;
	fw::FWCore* m_pFW;
	fw::Mesh* m_pBoardMesh;
	std::vector<fw::Mesh*> xMeshes = {};
	std::vector<fw::Mesh*> oMeshes = {};
	std::vector<fw::Mesh*> starMeshes = {};
	std::vector<int> boardVerts;
	std::vector<int> xVerts;
	std::vector<int> oVerts;
	std::vector<int> starVerts;
	std::vector<Slot*> Slots;
	bool m_MeshIsVisible = true;
	fw::intvec2 mousePos;
	bool mouseDown = false;
	bool mousePressed = false;
	ESlotState m_NextSlotState;
	ESlotState WinState;
	std::random_device rd;
	std::mt19937 gen;
	std::uniform_int_distribution<> dist;
	float timer;
	int animationPlayed;
};
