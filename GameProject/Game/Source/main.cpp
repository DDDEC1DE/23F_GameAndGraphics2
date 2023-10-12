#include "Framework.h"
#include "TicTacToe.h"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    fw::FWWindows framework( 1280, 720 );

    TicTacToe game( &framework );

    framework.Run( &game );
}
