#include "blockMain.h"
#include "bomba.h" // Include the generated bomb.h file

using namespace std;

blockMain::blockMain()
{
    cellSz = 30;
    rotatePos = 0;
    color = getCellColor();
    offsetX = 0;
    offsetY = 0;
    initialX = (GetScreenWidth() - 10 * cellSz) / 2;
    initialY = (GetScreenHeight() - 20 * cellSz) / 2;
    isBomb = false;

    // Generate bomb texture from embedded data
    Image bombImage = {0};
        bombImage.width = BOMBA_WIDTH;
        bombImage.height = BOMBA_HEIGHT;
        bombImage.mipmaps = 1;
        bombImage.format = BOMBA_FORMAT;
        bombImage.data = BOMBA_DATA;    
        
    bombTexture = LoadTextureFromImage(bombImage);
    // UnloadImage(bombImage); // Free memory after loading texture
}

blockMain::~blockMain()
{
    if (isBomb)
    {
        UnloadTexture(bombTexture); // Unload bomb texture if it was set
    }
}

// void blockMain::SetAsBomb()
// {
//     isBomb = true;
// }

// bool blockMain::IsBomb() const
// {
//     return isBomb;
// }

void blockMain::Draw()
{
    vector<Pos> tile = getCellPos();
    int startX = (GetScreenWidth() - 10 * cellSz) / 2;
    int startY = (GetScreenHeight() - 20 * cellSz) / 2;
    for (Pos item : tile)
    
    {
                    // DrawTexture(bombTexture, startX + item.y * cellSz, startY + item.x * cellSz, WHITE);
        if (cellId ==8)
        {
            // Draw bomb texture
            DrawTexture(bombTexture, startX + item.y * cellSz, startY + item.x * cellSz, WHITE);
        }
        else
        {
            DrawRectangle(startX + item.y * cellSz + 1, startY + item.x * cellSz + 1, cellSz - 1, cellSz - 1, color[cellId]);
        }
    }
}

void blockMain::ghostDraw()
{
    vector<Pos> tile = getCellPos();
    int startX = (GetScreenWidth() - 10 * cellSz) / 2;
    int startY = (GetScreenHeight() - 20 * cellSz) / 2;

    Color fadedWhite = Fade(white, 0.5f);

    for (Pos item : tile)
    {
        DrawRectangle(startX + item.y * cellSz + 1, startY + item.x * cellSz + 1, cellSz - 1, cellSz - 1, fadedWhite);
    }
}

void blockMain::Draw(Color color)
{
    int startX = (GetScreenWidth() - 10 * cellSz) / 2;
    int startY = (GetScreenHeight() - 20 * cellSz) / 2;
    for (Pos cell : getCellPos())
    {
        DrawRectangle(startX + cell.y * cellSz + 1, startY + cell.x * cellSz + 1, cellSz - 1, cellSz - 1, color);
    }
}

void blockMain::DrawAt(int x, int y)
{
    vector<Pos> tile = getCellPos();
    for (Pos item : tile)
    {
                if (cellId ==8) 
        {
            DrawTexture(bombTexture, x + item.y * cellSz, y + item.x * cellSz, WHITE);
        }
        else{
        DrawRectangle(x + item.y * cellSz + 1, y + item.x * cellSz + 1, cellSz - 1, cellSz - 1, color[cellId]);
    }
    }
}

void blockMain::Move(int x, int y)
{
    offsetX += x;
    offsetY += y;
}

vector<Pos> blockMain::getCellPos()
{
    vector<Pos> tile = cell[rotatePos];
    vector<Pos> moved;
    for (Pos item : tile)
    {
        Pos newPos = Pos(item.x + offsetX, item.y + offsetY);
        moved.push_back(newPos);
    }
    return moved;
}

void blockMain::rotateBlock()
{
    rotatePos++;
    if (rotatePos == int(cell.size()))
    {
        rotatePos = 0;
    }
}

void blockMain::rotateUndo()
{
    rotatePos--;
    if (rotatePos == -1)
    {
        rotatePos = int(cell.size()) - 1;
    }
}

void blockMain::resetPosition(int x, int y)
{
    x = (GetScreenWidth() - 10 * cellSz) / 2;
    y = (GetScreenHeight() - 20 * cellSz) / 2;
}
