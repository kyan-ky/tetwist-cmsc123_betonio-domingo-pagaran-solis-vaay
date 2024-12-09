#pragma once
#include "C:\raylib\raylib\src\raylib.h"
#include <vector>
#include <map>
#include "pos.h"
#include "color.h"
#include "board.h"

using namespace std;

class blockMain
{
public:
    blockMain();
    virtual ~blockMain();
    void SetAsBomb();
    void Draw();
    void ghostDraw();
    void Draw(Color);
    void DrawAt(int x, int y);
    void Move(int x, int y);
    vector<Pos> getCellPos();
    void rotateBlock();
    void rotateUndo();
    int cellId;
    map<int, vector<Pos>> cell;
    void resetPosition(int x, int y);
    int initialX;
    int initialY;
    int offsetX;
    int offsetY;
    void SetAsBomb(Texture2D texture); // Set block as a bomb with a texture
    bool IsBomb() const;        
private:
    int cellSz;
    int rotatePos;
    vector<Color> color;
    bool isBomb;           // Whether the block is a bomb
    Texture2D bombTexture; // Texture for the bomb
};
