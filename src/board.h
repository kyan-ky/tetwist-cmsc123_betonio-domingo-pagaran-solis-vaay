#pragma once
#include "C:\raylib\raylib\src\raylib.h"
#include <vector>

using namespace std;

class Board
{
public:
    Board();
    void Initialize();
    void displayPrint();
    void drawBoard();
    bool checkBounds(int x, int y);
    bool checkCollision(int x, int y);
    int clearLineAll();
    int board[20][10];
    void plantBombAndClear();
    void updateBomb(float deltaTime);
private:
    bool checkLine(int x);
    void clearLine(int x);
    void moveLineDown(int x, int rows);
    int rows;
    int cols;
    int cellSz;
    vector<Color> color;
    float bombTimer;      // Timer for the bomb planting interval
    float bombInterval;   // Time interval for planting a bomb
    int bombRow;          // Row affected by the bomb
    bool bombPlanted;
};