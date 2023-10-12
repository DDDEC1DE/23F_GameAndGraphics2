#include "Slot.h"

Slot::Slot(fw::intvec2 Position)
{
       m_Position = Position;
       Ignore = false;
       m_State = ESlotState::Empty;
       
}

Slot::~Slot()
{
}
