#ifndef __Tilemap_H__
#define __Tilemap_H__

class GameCore;

class Tilemap
{
public:
    unsigned char* m_Tiles;

public:
    Tilemap();
    virtual ~Tilemap();

    void Create();
    void Draw();

    bool IsTileWalkableAtTilePos(int x, int y);
};

#endif //__Tilemap_H__