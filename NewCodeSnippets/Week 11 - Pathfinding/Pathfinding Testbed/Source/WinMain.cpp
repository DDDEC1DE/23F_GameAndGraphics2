#include <Windows.h>
#include <stdio.h>

#include "Tilemap.h"
#include "Pathfinder.h"

static void OutputMessage(const char* message, ...)
{
#define MAX_MESSAGE 1024
    char szBuff[MAX_MESSAGE];
    va_list arg;
    va_start(arg, message);
    vsnprintf_s( szBuff, sizeof(szBuff), _TRUNCATE, message, arg );
    va_end(arg);

    szBuff[MAX_MESSAGE-1] = 0; // vsnprintf_s might do this, but docs are unclear
    OutputDebugString( szBuff );
}

double GetSystemTime()
{
    unsigned __int64 freq;
    unsigned __int64 time;

    QueryPerformanceFrequency( (LARGE_INTEGER*)&freq );
    QueryPerformanceCounter( (LARGE_INTEGER*)&time );

    double timeseconds = (double)time / freq;

    return timeseconds;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    Tilemap tilemap;
    Pathfinder pathfinder( &tilemap, 10, 10 );

    // Comment out this srand for a predictable layout.
    srand( (unsigned int)GetSystemTime() );
    tilemap.Create();

    tilemap.Draw();

    int startx = 1;
    int starty = 1;
    int endx = 5;
    int endy = 5;
    bool found = pathfinder.FindPath( startx, starty, endx, endy );

    OutputMessage( "Found = %d\n", found );

    std::vector<int> path = pathfinder.GetPath( endx, endy );

    OutputMessage( "Length = %d\n", path.size() );
    for( int i=0; i<path.size(); i++ )
    {
        OutputMessage( "%d\n", path[i] );
    }

    OutputMessage( "done\n" );
}
