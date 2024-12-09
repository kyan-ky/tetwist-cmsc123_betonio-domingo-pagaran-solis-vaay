#include "board.h"
#include "color.h"
#include <iostream>

using namespace std;

Board::Board()
{
    rows = 20;
    cols = 10;
    cellSz = 30;
    Initialize();
    color = getCellColor();
    bombTimer = 0.0f;
    bombInterval = 5.0f; // Bomb plants every 5 seconds
    bombRow = -1;        // No bomb row initially
    bombPlanted = false; 
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
    int bombRow = rand() % rows;
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
        if (bombPlanted && i == bombRow) {
    DrawRectangle(startX, startY + i * cellSz, cols * cellSz, cellSz, RED); // Highlight the bomb row
}

        }
    }
}
void Board::plantBombAndClear() {
    int bombRow = rand() % rows; // Select a random row
    if (bombRow >= 0 && bombRow < rows) {
        clearLine(bombRow); // Use the existing clearLine method to clear the row
        // Optional: Add visual or audio feedback
        cout << "Bomb detonated at row: " << bombRow << endl;
    }
}
void Board::updateBomb(float deltaTime)
{
    bombTimer += deltaTime;

    if (bombTimer >= bombInterval) {
        bombTimer = 0.0f;
        bombRow = rand() % rows; // Select a random row for the bomb
        bombPlanted = true;
        clearLine(bombRow);      // Clear the bomb row immediately
        PlaySound(LoadSound("sound/bomb_explosion.mp3")); // Optional: Explosion sound
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
    // Clear the specified row
    for (int i = 0; i < cols; i++) {
        board[x][i] = 0;
    }

    // Shift all rows above the cleared row down
    for (int row = x; row > 0; row--) {
        for (int col = 0; col < cols; col++) {
            board[row][col] = board[row - 1][col];
        }
    }

    // Clear the topmost row (which has been shifted down)
    for (int col = 0; col < cols; col++) {
        board[0][col] = 0;
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
