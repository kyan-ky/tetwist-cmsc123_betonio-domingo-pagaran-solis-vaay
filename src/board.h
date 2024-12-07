#pragma once
#include <vector>
#include "C:\raylib\raylib\src\raylib.h"

using namespace std;

class Board {
public:
    Board();
    void Initialize();
    void displayPrint();
    void drawBoard();
    bool checkBounds(int x, int y);
    bool checkCollision(int x, int y);
    int clearLineAll();
    int board[20][10];
private:
    bool checkLine(int x);
    void clearLine(int x);
    void moveLineDown(int x, int rows);
    int rows;
    int cols;
    int cellSz;
    vector<Color> color;
};