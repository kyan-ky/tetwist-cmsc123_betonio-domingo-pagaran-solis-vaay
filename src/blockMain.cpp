#include "blockMain.h"
#include "bomb.h"
#include "star.h"
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
    Image bombImage = {0};
    bombImage.width = BOMB_WIDTH;
    bombImage.height = BOMB_HEIGHT;
    bombImage.mipmaps = 1;
    bombImage.format = BOMB_FORMAT;
    bombImage.data = BOMB_DATA;

    bombTexture = LoadTextureFromImage(bombImage);

    Image starImage = {0};
    starImage.width = STAR_WIDTH;
    starImage.height = STAR_HEIGHT;
    starImage.mipmaps = 1;
    starImage.format = STAR_FORMAT;
    starImage.data = STAR_DATA;

    starTexture = LoadTextureFromImage(starImage);
}

void blockMain::Draw()
{
    vector<Pos> tile = getCellPos();
    int startX = (GetScreenWidth() - 10 * cellSz) / 2;
    int startY = (GetScreenHeight() - 20 * cellSz) / 2;
    for (Pos item : tile)
    {
        if (cellId == 8)
        {
            DrawTexture(bombTexture, startX + item.y * cellSz, startY + item.x * cellSz, WHITE);
        }
        else if (cellId == 9)
        {
            DrawTexture(starTexture, startX + item.y * cellSz, startY + item.x * cellSz, WHITE);
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
        if (cellId == 8)
        {
            DrawTexture(bombTexture, x + item.y * cellSz, y + item.x * cellSz, WHITE);
        }
        else if (cellId == 9)
        {
            DrawTexture(starTexture, x + item.y * cellSz, y + item.x * cellSz, WHITE);
        }
        else
        {
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
    offsetX = x;
    offsetY = y;
    rotatePos = 0;
}

//     vector<Pos> tile = getCellPos();
//     for (Pos item : tile) {
//         if (board.checkBounds(item.x, item.y) || board.checkCollision(item.x, item.y)) {
//             return true;
//         }
//     }
//     return false;
// }
