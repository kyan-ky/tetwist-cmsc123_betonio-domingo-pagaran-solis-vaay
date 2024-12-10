#include "blockMain.h"

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
}

void blockMain::Draw()
{
    vector<Pos> tile = getCellPos();
    int startX = (GetScreenWidth() - 10 * cellSz) / 2;
    int startY = (GetScreenHeight() - 20 * cellSz) / 2;
    for (Pos item : tile)
    {
        DrawRectangle(startX + item.y * cellSz + 1, startY + item.x * cellSz + 1, cellSz - 1, cellSz - 1, color[cellId]);
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
        DrawRectangle(x + item.y * cellSz + 1, y + item.x * cellSz + 1, cellSz - 1, cellSz - 1, color[cellId]);
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

void blockMain::resetPosition()
{
    // Reset offsets to position the block at the top center of the board
    offsetX = (GetScreenWidth() - cellSz) / 2;
    offsetY =  0;
}

//     vector<Pos> tile = getCellPos();
//     for (Pos item : tile) {
//         if (board.checkBounds(item.x, item.y) || board.checkCollision(item.x, item.y)) {
//             return true;
//         }
//     }
//     return false;
// }
