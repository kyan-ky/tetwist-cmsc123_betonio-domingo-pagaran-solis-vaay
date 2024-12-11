#pragma once
#include <raylib.h>
#include "board.h"
#include "blockSub.cpp"
#include <string>
#include <deque>

using namespace std;

class gameHandler
{
public:
    gameHandler();
    ~gameHandler();
    blockMain getRandomBlock();
    blockMain getCurrentBlock();
    blockMain getNextBlock();
    blockMain getSecondBlock();
    blockMain getThirdBlock();
    deque<blockMain> getRandomBlockQueue();
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
    int highScore;
    Music music;
    string getBlockName(int cellId);
    void LoadHighScore();
    void UpdateHighScore(int);

private:
    void Reset();
    void updateScore(int linesCleared);
    void rotateBlock();
    void fastDrop();
    void lockBlock();
    bool checkCollision();
    bool checkBounds();
    bool checkBounds(blockMain block);
    vector<blockMain> blockSub;
    deque<blockMain> nextBlocks;
    blockMain currBlock;
    blockMain nextBlock;
    blockMain heldBlock;
    size_t secondIndex;
    int thirdIndex;
    blockMain secondBlock;
    blockMain thirdBlock;
    float moveDownTimer;
    float lastFrameTime;
    Sound clearLineFx;
    Sound moveFx;
    Sound dropFx;
    Sound gameOverFx;
    blockMain ghostBlock;                 // New variable to store the ghost block
    bool checkCollision(blockMain block); // Overloaded to check collision for a specific block
    void updateGhostBlock();              // New method to update the ghost block position
    float moveDelay;                      // Delay between key repeats
    float lastMoveTime;
    bool canHoldPiece;
    void reverseBoard();
    bool heldBlockBool;

    bool flippedBoard;
    float flippedMessageTime = 0.0f;    // Time when the flipped message is displayed
    bool displayFlippedMessage = false; // Flag to control message display

    float moveDownDelayEasy = 0.8f;   // Delay for 0 to 800
    float moveDownDelayMedium = 0.7f;  // Delay for 800
    float moveDownDelayMedium2 = 0.6f; // Delay for 1600
    float moveDownDelayHard = 0.5f;    // Delay for 2400
    float moveDownDelayHard2 = 0.4f;   // Delay for 3500
    float moveDownDelayExtraHard = 0.2f; // Delay for 5000
    float moveDownDelayExtreme = 0.1f; // Delay for 7000
    float moveDownDelay;                // Current move down delay
    int currentPhase;                    // Current phase (0: easy, 1: medium, 2: hard, 3: extra hard, 4: extreme)
};
