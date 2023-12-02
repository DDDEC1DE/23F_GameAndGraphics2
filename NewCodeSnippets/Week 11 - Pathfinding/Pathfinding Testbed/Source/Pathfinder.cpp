#include <assert.h>
#include <float.h>
#include <math.h>

#include "Tilemap.h"
#include "Pathfinder.h"

Pathfinder::Pathfinder(Tilemap* pTilemap, int width, int height)
{
    m_pTilemap = pTilemap;

    m_NumNodes = width * height;

    m_Nodes = new PathNode[m_NumNodes];

    m_MapWidth = width;
    m_MapHeight = height;

    Reset();
}
    
Pathfinder::~Pathfinder()
{
    delete[] m_Nodes;
}

void Pathfinder::Reset()
{
    m_NumOpen = 0;

    for( int i=0; i<m_NumNodes; i++ )
    {
        m_Nodes[i].parentNodeIndex = -1;
        m_Nodes[i].status = PathNode::Unchecked;

        m_Nodes[i].cost = FLT_MAX; // Set cost to be highest cost possible, so any comparison will be better.
    }
}
        
bool Pathfinder::FindPath(int sx, int sy, int ex, int ey)
{
    return false;
}

std::vector<int> Pathfinder::GetPath(int ex, int ey)
{
    return {};
}
