#include "Framework.h"
#include "A4/A4Game.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    fw::FWWindows framework(1280, 720);

    A4Game game(&framework);

    framework.Run(&game);
}
