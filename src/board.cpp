#include "board.h"
#include "color.h"
#include <iostream>
#include <algorithm>

using namespace std;

Board::Board()
{
    rows = 20;
    cols = 10;
    cellSz = 30;
    Initialize();
    color = getCellColor();
}

void Board::Initialize()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            board[i][j] = 0;
        }
    }
}

void Board::displayPrint()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

void Board::drawBoard()
{
    int startX = (GetScreenWidth() - cols * cellSz) / 2;
    int startY = (GetScreenHeight() - rows * cellSz) / 2;
    int borderWidth = 20;
    int borderPad = 10;
    Color borderColor = lightgray;
    DrawRectangleRounded(
        Rectangle{float(startX - borderPad), float(startY - borderPad),
                  float(cols * cellSz + 2 * borderPad), float(rows * cellSz + 2 * borderPad)},
        0.05f,
        borderWidth,
        borderColor);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            DrawRectangle(startX + j * cellSz + 1, startY + i * cellSz + 1, cellSz - 1, cellSz - 1, color[board[i][j]]);
        }
    }
}

bool Board::checkBounds(int x, int y)
{
    return !(x >= 0 && x < rows && y >= 0 && y < cols);
}

bool Board::checkCollision(int x, int y)
{
    if (board[x][y] == 0)
    {
        return true;
    }
    return false;
}

bool Board::checkLine(int x)
{
    for (int i = 0; i < cols; i++)
    {
        if (board[x][i] == 0)
        {
            return false;
        }
    }
    return true;
}

int Board::clearLineAll()
{
    int linesCleared = 0;
    for (int i = rows - 1; i >= 0; i--)
    {
        if (checkLine(i))
        {
            clearLine(i);
            linesCleared++;
        }
        else if (linesCleared > 0)
        {
            moveLineDown(i, linesCleared);
        }
    }
    return linesCleared;
}

void Board::clearLine(int x)
{
    for (int i = 0; i < cols; i++)
    {
        board[x][i] = 0;
    }
}

void Board::moveLineDown(int x, int rows)
{
    for (int i = 0; i < cols; i++)
    {
        board[x + rows][i] = board[x][i];
        board[x][i] = 0;
    }
}
void Board::clear3x3Block(int startX, int startY)
{
    for (int i = -1; i <= 1; i++)  
    {
        for (int j = -1; j <= 1; j++)  
        {
            int x = startX + i;
            int y = startY + j;


            if (x >= 0 && x < rows && y >= 0 && y < cols)
            {
                board[x][y] = 0;
            }
        }
    }
}
void Board::populate3x3Block(int startX, int startY, int value)
{
    for (int i = -1; i <= 1; i++) 
    {
        for (int j = -1; j <= 1; j++) 
        {
            int x = startX + i;
            int y = startY + j;


            if (x >= 0 && x < rows && y >= 0 && y < cols)
            {

                board[x][y] = value;
            }
        }
    }
}

int Board::getRows() const {
    return rows;
}

int Board::getCols() const {
    return cols;
}

void Board::invertColors()
{
    for (int i = 0; i < 10; i++) // Assuming you have 10 colors
    {
        // Invert the color and clamp the values to ensure they are within the valid range
        color[i].r = static_cast<unsigned char>(std::clamp(255 - static_cast<int>(color[i].r), 0, 255));
        color[i].g = static_cast<unsigned char>(std::clamp(255 - static_cast<int>(color[i].g), 0, 255));
        color[i].b = static_cast<unsigned char>(std::clamp(255 - static_cast<int>(color[i].b), 0, 255));
        
        // Adjust the alpha value to make it less pure
        color[i].a = static_cast<unsigned char>(std::clamp(color[i].a * 0.8f, 0.0f, 255.0f)); // Reduce alpha to 80%
    }
}
