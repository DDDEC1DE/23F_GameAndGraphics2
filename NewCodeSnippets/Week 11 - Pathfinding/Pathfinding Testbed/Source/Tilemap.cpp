#include <Windows.h>
#include <stdio.h>

#include "Tilemap.h"

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

Tilemap::Tilemap()
{
    m_Tiles = 0;
}

Tilemap::~Tilemap()
{
    delete m_Tiles;
}

void Tilemap::Create()
{
    m_Tiles = new unsigned char[10*10];

    for( int y=0; y<10; y++ )
    {
        for( int x=0; x<10; x++ )
        {
            int index = y*10 + x;

            if( rand()%3 == 0 )
                m_Tiles[index] = 1;
            else
                m_Tiles[index] = 0;
        }
    }
}

void Tilemap::Draw()
{
    OutputMessage( "\n" );
    OutputMessage( "Tilemap:\n" );

    for( int y=10-1; y>=0; y-- )
    {
        for( int x=0; x<10; x++ )
        {
            OutputMessage( "%d", m_Tiles[y*10 + x] );
        }

        OutputMessage( "\n" );
    }

    OutputMessage( "\n" );
    OutputMessage( "\n" );
}

bool Tilemap::IsTileWalkableAtTilePos(int x, int y)
{
    if( x < 0 || x >= 10 || y < 0 || y >= 10 )
        return false;

    return m_Tiles[y*10 + x] == 0 ? true : false;
}
