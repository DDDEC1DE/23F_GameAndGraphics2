#include "TicTacToe.h"
#include "DataTypes.h"



TicTacToe::TicTacToe(fw::FWCore* pFW) : 
    fw::GameCore(pFW),
    gen(rd()),
    dist(5, 95),
    timer(TimeBetweenAnimations),
    animationPlayed(Animation_Play_Times)
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glPointSize(20);
    glLineWidth(5);
    m_pFW = pFW;

    m_pWhiteShader = new fw::ShaderProgram("Data/Shaders/Basic.vert", "Data/Shaders/White.frag");

    boardVerts = {
            33, 0,
            33, 100,

            66, 0,
            66, 100,

            0, 33,
            100, 33,

            0, 66,
            100, 66
    };

    std::vector<float> MeshCreate = {};
    for (int i = 0; i < boardVerts.size(); i++)
    {
        MeshCreate.push_back(boardVerts[i]);
    }


    m_pBoardMesh = new fw::Mesh();
    m_pBoardMesh->Create(MeshCreate, GL_LINES);
    Slot* slot1 = new Slot(fw::intvec2(16, 16));   //botoom left
    Slots.push_back(slot1);
    Slot* slot2 = new Slot(fw::intvec2(50, 16));    //bottom middle
    Slots.push_back(slot2);
    Slot* slot3 = new Slot(fw::intvec2(83, 16));   //bottom right
    Slots.push_back(slot3);
    Slot* slot4 = new Slot(fw::intvec2(16, 50));   //middle left
    Slots.push_back(slot4);
    Slot* slot5 = new Slot(fw::intvec2(50, 50));   //middle middle
    Slots.push_back(slot5);
    Slot* slot6 = new Slot(fw::intvec2(83, 50));   //middle right    
    Slots.push_back(slot6);
    Slot* slot7 = new Slot(fw::intvec2(16, 83));   //top left
    Slots.push_back(slot7);
    Slot* slot8 = new Slot(fw::intvec2(50, 83));   //top middle
    Slots.push_back(slot8);
    Slot* slot9 = new Slot(fw::intvec2(83, 83));   //top right
    Slots.push_back(slot9);

    m_NextSlotState = ESlotState::O;
    WinState = ESlotState::Empty;

}

TicTacToe::~TicTacToe()
{
    delete m_pWhiteShader;
    delete m_pBoardMesh;
    for (fw::Mesh* oMesh : oMeshes)
    {
        delete oMesh;
    }
    for (fw::Mesh* xMesh : xMeshes)
    {
        delete xMesh;
    }
    for (fw::Mesh* starMesh : starMeshes)
    {
        delete starMesh;
    }
    for (Slot* slot : Slots)
    {
        delete slot;
    }
}



void TicTacToe::OnKeyDown(int keyCode)
{
    if (keyCode == VK_F1)
    {
        wglSwapInterval(1);
    }
    if (keyCode == VK_F2)
    {
        wglSwapInterval(0);
    }

    if (keyCode == 0x52)
    {
        Reset();
    }
}

void TicTacToe::OnKeyUp(int keyCode)
{
    m_MeshIsVisible = true;
}

void TicTacToe::Update(float deltaTime)
{
    GetMousePos();
    IsMouseDown();
    WinState = CheckForWin();
    if (WinState != ESlotState::Empty)
    {
        WinCondition(deltaTime);
    }
    else
    {
        GameInProgress();
    }
}

void TicTacToe::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (m_MeshIsVisible)
    {
        m_pBoardMesh->Draw(m_pWhiteShader, vec2(0, 0));
        for (fw::Mesh* oMesh : oMeshes)
        {
            oMesh->Draw(m_pWhiteShader, vec2(0, 0));
        }
        for (fw::Mesh* xMesh : xMeshes)
        {
            xMesh->Draw(m_pWhiteShader, vec2(0, 0));
        }
        for (fw::Mesh* starMesh : starMeshes)
        {
            starMesh->Draw(m_pWhiteShader, vec2(0, 0));
        }
    }

    m_pFW->SwapBuffers();
}


void TicTacToe::CreateCircle(fw::intvec2 Position)
{

    const int points = 100;
    const float angleIncrement = 2.0f * 3.14159f / points;
    const int radius = 12;

    std::vector<float> circleVerts;

    for (int i = 0; i < points; i++)
    {
        float x = Position.x + radius * cos(i * angleIncrement);
        float y = Position.y + radius * sin(i * angleIncrement);
        circleVerts.push_back(x);
        circleVerts.push_back(y);
    }

    fw::Mesh* oMesh = new fw::Mesh();
    oMesh->Create(circleVerts, GL_LINE_LOOP);
    oMeshes.push_back(oMesh);
}

void TicTacToe::CreateX(fw::intvec2 Position)
{
    int offset = -17;
    Position.x += offset;
    Position.y += offset;
    xVerts = {
        Position.x, Position.y ,  // Bottom left of the X.
        Position.x + 33,Position.y + 33,  // Top right of the X.

        Position.x + 33,Position.y,  // Bottom right of the X.
        Position.x, Position.y + 33   // Top left of the X.
    };
    fw::Mesh* xMesh = new fw::Mesh();
    std::vector<float> MeshCreate = {};
    for (int i = 0; i < xVerts.size(); i++)
    {
        MeshCreate.push_back(xVerts[i]);
    }

    xMesh->Create(MeshCreate, GL_LINES);
    xMeshes.push_back(xMesh);
}

void TicTacToe::CreateStar(fw::intvec2 Position)
{

    fw::Mesh* starMesh = new fw::Mesh();

    starVerts = {
     Position.x - 2, Position.y,
     Position.x+2, Position.y,
     Position.x, Position.y+8,
     Position.x, Position.y,
     Position.x+5, Position.y,
     Position.x, Position.y-8,
     Position.x, Position.y,
     Position.x - 5, Position.y,
     Position.x, Position.y - 8,
     Position.x-2, Position.y - 2,
     Position.x-3, Position.y - 10,
     Position.x, Position.y - 8,
     Position.x + 2, Position.y - 2,
     Position.x + 3, Position.y - 10,
     Position.x, Position.y - 8,
    };

    std::vector<float> MeshCreate = {};
    for (int i = 0; i < starVerts.size(); i++)
    {
        MeshCreate.push_back(starVerts[i]);
    }
    starMesh->Create(MeshCreate, GL_TRIANGLE_FAN);
    starMeshes.push_back(starMesh);
}




fw::intvec2 TicTacToe::GetMousePos() {
    int mouseX, mouseY;
    m_pFW->GetMouseCoordinates(&mouseX, &mouseY);

    int windowWidth = m_pFW->GetWindowWidth();
    int windowHeight = m_pFW->GetWindowHeight();

    mousePos.x = (mouseX * 100) / windowWidth;
    mousePos.y = 100 - (mouseY * 100) / windowHeight;

    return mousePos;
}








bool TicTacToe::IsMouseDown()
{
    mouseDown = m_pFW->IsMouseButtonDown(0);
    if (mouseDown == true)
    {
        mouseDown = true;
    }
    return mouseDown;
}

Slot* TicTacToe::FillSlot(fw::intvec2 position, ESlotState newstate)
{
    Slot* closestslot = Slots[0];

   



    float currentclosestdistance = position.DistanceTo(closestslot->GetPosition());

    for (int i = 0; i < Slots.size(); i++)
    {

        float newdistance = position.DistanceTo(Slots[i]->GetPosition());
        if (newdistance < currentclosestdistance)
        {
            currentclosestdistance = newdistance;
            closestslot = Slots[i];
        }

    }
    

    if (closestslot->GetState() == ESlotState::Empty)
    {
        if (newstate == ESlotState::O)
        {
            CreateCircle(closestslot->GetPosition());
            closestslot->SetState(ESlotState::O);
        }
        else if (newstate == ESlotState::X)
        {
            CreateX(closestslot->GetPosition());
            closestslot->SetState(ESlotState::X);
        }
    }
    else
    {
        closestslot->Ignore = true;
    }



    return closestslot;

}

ESlotState TicTacToe::CheckForWin()
{
    for (int i = 0; i < 3; i++) {
        if (Slots[i * 3]->GetState() != ESlotState::Empty &&
            Slots[i * 3]->GetState() == Slots[i * 3 + 1]->GetState() &&
            Slots[i * 3]->GetState() == Slots[i * 3 + 2]->GetState()) {
            return Slots[i * 3]->GetState();
        }





        if (Slots[i]->GetState() != ESlotState::Empty &&
            Slots[i]->GetState() == Slots[i + 3]->GetState() &&
            Slots[i]->GetState() == Slots[i + 6]->GetState()) {
            return Slots[i]->GetState();
        }
    }

    if (Slots[0]->GetState() != ESlotState::Empty &&
        Slots[0]->GetState() == Slots[4]->GetState() &&
        Slots[0]->GetState() == Slots[8]->GetState()) {
        return Slots[0]->GetState();
    }

    if (Slots[2]->GetState() != ESlotState::Empty &&
        Slots[2]->GetState() == Slots[4]->GetState() &&
        Slots[2]->GetState() == Slots[6]->GetState()) {
        return Slots[2]->GetState();
    }

    return ESlotState::Empty;
}

void TicTacToe::Reset()
{
    starMeshes.clear();
    oMeshes.clear();
    xMeshes.clear();
    animationPlayed = Animation_Play_Times;
    timer = TimeBetweenAnimations;
    m_NextSlotState = ESlotState::O;
    for (Slot* slot : Slots)
    {
        slot->SetState(ESlotState::Empty);
    }
}

void TicTacToe::GameInProgress()
{
    if (IsMouseDown())
    {
        if (mousePos.x > 100 || mousePos.x < 0 || mousePos.y > 100 || mousePos.y < 0)
        {
            return;
        }
        if (mousePressed == false)
        {
            Slot* ClosestSlot = FillSlot(mousePos, m_NextSlotState);

            if (ClosestSlot->Ignore == true) {
                
                return;
            }

            mousePressed = true;
            switch (m_NextSlotState)
            {
            case Empty:
                return;
                break;
            case X:
                m_NextSlotState = ESlotState::O;
                break;
            case O:
                m_NextSlotState = ESlotState::X;
                break;
            }
        }

    }
    else
    {
        mousePressed = false;
    }
}

void TicTacToe::WinCondition(float delta)
{
    if (animationPlayed < 0)
    {
        return;
    }

    timer -= delta;

    if (timer <= 0)
    {
        timer = TimeBetweenAnimations;
        Win();
        animationPlayed--;
    }

}

void TicTacToe::Win()
{

    for (int i = 0; i < 3; i++) {  
        int X = dist(gen);
        int Y = dist(gen);
        CreateStar(fw::intvec2(X, Y));
    }

    if (WinState != ESlotState::Empty) {
        for (int i = 0; i < 3; i++) {  
            int X = dist(gen);
            int Y = dist(gen);
            if (WinState == ESlotState::X) {
                CreateX(fw::intvec2(X, Y));
            }
            else {
                CreateCircle(fw::intvec2(X, Y));
            }
        }
    }
    
}
