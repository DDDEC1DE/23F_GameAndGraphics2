#pragma once
#include "Framework.h"

class GameSurvivors : public fw::GameCore
{
public:
	GameSurvivors(fw::FWCore* m_pFW);

	virtual void Update() override;
	virtual void Draw() override;
	
	virtual ~GameSurvivors();

private:

};

