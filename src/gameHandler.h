#pragma once
#include "board.h"
#include "blockSub.cpp"
#include <string>

using namespace std;

class gameHandler
{
public:
    gameHandler();
    ~gameHandler();
    blockMain getRandomBlock();
    vector<blockMain> refreshBlocks();
    void drawGame();
    void holdPiece();
    void inputHandler();
    void updateGame();
    void moveLeft();
    void moveRight();
    void moveDown();
    Board board;
    bool checkGameOver;
    bool checkHoldPiece;
    int score;
    Music music;
    string getBlockName(int cellId);

private:
    bool checkBounds();
    void Reset();
    void updateScore(int linesCleared);
    void rotateBlock();
    void fastDrop();
    void lockBlock();
    bool checkCollision();
    vector<blockMain> blockSub;
    blockMain currBlock;
    blockMain nextBlock;
    blockMain heldBlock;
    float moveDownTimer;
    float moveDownDelay;
    float lastFrameTime;
    Sound clearLineFx;
    Sound moveFx;
    Sound dropFx;
    Sound gameOverFx;

    float moveDelay; // Delay between key repeats
    float lastMoveTime;

    bool canHoldPiece;
};
