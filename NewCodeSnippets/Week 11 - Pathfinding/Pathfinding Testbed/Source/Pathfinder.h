#ifndef __PathFinder_H__
#define __PathFinder_H__

#include <vector>

struct PathNode
{
    enum PathNodeStatus
    {
        Unchecked,
        Open,
        Closed,
    };

    int parentNodeIndex;
    PathNodeStatus status;

    float cost;
};

class Pathfinder
{
protected:
    int m_MapWidth;
    int m_MapHeight;
    Tilemap* m_pTilemap;

    PathNode* m_Nodes;
    int m_NumNodes;

    std::vector<int> m_OpenNodeIndexes;
    int m_NumOpen;

public:
    Pathfinder(Tilemap* pTilemap, int width, int height);
    virtual ~Pathfinder();

    void Reset();

    // Start a search, supply the starting tile x,y and ending tile x,y.
    // Returns true if path found, false otherwise.
    bool FindPath(int sx, int sy, int ex, int ey);

    // Retrieve the final path, pass a nullptr for "path" to just get length of the path.
    std::vector<int> GetPath(int ex, int ey);
};

#endif //__PathFinder_H__
