#pragma once

#include "Framework.h"



enum ESlotState
{
    Empty,
    X,
    O,
};

class Slot
{
public:
	Slot(fw::intvec2 Position);
	~Slot();

    void SetState(ESlotState state) { m_State = state; }
    ESlotState GetState() { return m_State; }

    void SetPosition(fw::intvec2 position) { m_Position = position; }
    fw::intvec2 GetPosition() { return m_Position; }

    bool Ignore;
private:
    ESlotState m_State;
    fw::intvec2 m_Position;
};
