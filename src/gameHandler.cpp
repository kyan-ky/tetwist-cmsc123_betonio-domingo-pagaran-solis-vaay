#include "gameHandler.h"
#include "board.h"
#include <random>
#include <stdlib.h>
#include <cstring>

using namespace std;

gameHandler::gameHandler()
{
    board = Board();
    blockSub = {blockI(), blockJ(), blockL(), blockO(), blockS(), blockT(), blockZ()};
    currBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    checkGameOver = false;
    checkHoldPiece = false;
    score = 0;
    moveDownTimer = 0.0f;
    moveDownDelay = 0.5f;
    lastFrameTime = GetTime();
    InitAudioDevice();
    music = LoadMusicStream("sound/Tetris.mp3");
    PlayMusicStream(music);
    clearLineFx = LoadSound("sound/clear.wav");
    gameOverFx = LoadSound("sound/gameover.wav");
    moveFx = LoadSound("sound/move.mp3");
    dropFx = LoadSound("sound/drop.mp3");
    updateGhostBlock(); // Initialize ghost block

    moveDelay = 0.08f; // Delay in seconds (0.2 default)
    lastMoveTime = 0.0f;

    canHoldPiece = true;

    updateGhostBlock(); // Initialize ghost block
}

gameHandler::~gameHandler()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}

void gameHandler::drawGame()
{
    board.drawBoard();

    ghostBlock.ghostDraw();

    currBlock.Draw();
    int nextBlockX = GetScreenWidth() - 250;
    int nextBlockY = 100;
    switch (nextBlock.cellId)
    {
    case 3:
        nextBlock.DrawAt(nextBlockX - 20, nextBlockY + 20);
        break;
    case 6:
        nextBlock.DrawAt(nextBlockX - 20, nextBlockY + 10);
        break;
    default:
        nextBlock.DrawAt(nextBlockX, nextBlockY);
    }
    Font font = Font();
    DrawTextEx(font, ((getBlockName(heldBlock.cellId)).c_str()), {static_cast<float>(GetScreenWidth() - 745), 100}, 30, 5, white);
    if (checkGameOver)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(GRAY, 0.8f));
        DrawTextEx(font, "Game Over", {static_cast<float>(GetScreenWidth() / 2 - 150), static_cast<float>(GetScreenHeight() / 2 - 50)}, 60, 5, RED);
        DrawTextEx(font, "Press ENTER to Play Again", {static_cast<float>(GetScreenWidth() / 2 - 280), static_cast<float>(GetScreenHeight() / 2 + 100)}, 40, 5, YELLOW);
        StopMusicStream(music);
    }
}

string gameHandler::getBlockName(int cellId)
{
    switch (cellId)
    {
    case 1:
        return "Block J";
    case 2:
        return "Block L";
    case 3:
        return "Block I";
    case 4:
        return "Block S";
    case 5:
        return "Block Z";
    case 6:
        return "Block O";
    case 7:
        return "Block T";
    default:
        return "None";
    }
}

blockMain gameHandler::getRandomBlock()
{
    if (blockSub.empty())
    {
        blockSub = refreshBlocks();
    }
    int random = rand() % blockSub.size();
    blockMain randomBlock = blockSub[random];
    blockSub.erase(blockSub.begin() + random);
    return randomBlock;
}

vector<blockMain> gameHandler::refreshBlocks()
{
    return {blockI(), blockJ(), blockL(), blockO(), blockS(), blockT(), blockZ()};
}

void gameHandler::holdPiece()
{
    if (!canHoldPiece)
    {
        // Prevent holding twice in succession
        return;
    }

    if (!checkHoldPiece)
    {
        // First time holding a piece
        heldBlock = currBlock;        // Move the current block to the hold
        currBlock = nextBlock;        // Replace current block with the next block
        nextBlock = getRandomBlock(); // Generate a new next block
        checkHoldPiece = true;        // Mark that a piece has been held
    }
    else
    {
        // Swap held block with the current block
        swap(currBlock, heldBlock);
    }

    currBlock.resetPosition(0, 0); // Reset the position of the new current block
    canHoldPiece = false;          // Disable holding until the next block is placed
}

void gameHandler::inputHandler()
{
    if (checkGameOver)
    {
        if (IsKeyPressed(KEY_ENTER))
        { // Use IsKeyPressed for single press events
            checkGameOver = false;
            Reset();
        }
        return;
    }

    float currentTime = GetTime();

    // Continuous movement for long presses
    if (IsKeyDown(KEY_LEFT) && (currentTime - lastMoveTime > moveDelay))
    {
        moveLeft();
        lastMoveTime = currentTime;
    }
    if (IsKeyDown(KEY_RIGHT) && (currentTime - lastMoveTime > moveDelay))
    {
        moveRight();
        lastMoveTime = currentTime;
    }
    if (IsKeyDown(KEY_DOWN) && (currentTime - lastMoveTime > moveDelay))
    {
        moveDown();
        lastMoveTime = currentTime;
    }

    // Actions triggered by single press
    if (IsKeyPressed(KEY_UP))
    {
        rotateBlock();
    }
    if (IsKeyPressed(KEY_SPACE))
    {
        fastDrop();
    }
    if (IsKeyPressed(KEY_C))
    {
        holdPiece();
    }

    // Uncomment if you want to use backspace to exit the game
    // if (IsKeyPressed(KEY_BACKSPACE)) {
    //     CloseWindow();
    // }
}

void gameHandler::updateGame()
{
    float currentTime = GetTime();
    float deltaTime = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    moveDownTimer += deltaTime;

    if (moveDownTimer >= moveDownDelay)
    {
        moveDown();
        moveDownTimer = 0.0f;
    }

    updateGhostBlock();
}

void gameHandler::moveLeft()
{
    if (!checkGameOver)
    {
        currBlock.Move(0, -1);
        if (checkBounds() || checkCollision() == false)
        {
            currBlock.Move(0, 1);
        }
    }
    PlaySound(moveFx);
}

void gameHandler::moveRight()
{
    if (!checkGameOver)
    {
        currBlock.Move(0, 1);
        if (checkBounds() || checkCollision() == false)
        {
            currBlock.Move(0, -1);
        }
    }
    PlaySound(moveFx);
}

void gameHandler::moveDown()
{
    if (!checkGameOver)
    {
        currBlock.Move(1, 0);
        if (checkBounds() || checkCollision() == false)
        {
            currBlock.Move(-1, 0);
            lockBlock();
        }
    }
}

void gameHandler::rotateBlock()
{
    if (!checkGameOver)
    {
        currBlock.rotateBlock();
        if (checkBounds() || checkCollision() == false)
        {
            currBlock.rotateUndo();
        }
    }
    PlaySound(moveFx);
}

void gameHandler::fastDrop()
{
    if (!checkGameOver)
    {
        while (true)
        {
            currBlock.Move(1, 0);
            if (checkBounds() || !checkCollision())
            {
                currBlock.Move(-1, 0);
                lockBlock();
                break;
            }
        }
    }
}

void gameHandler::lockBlock()
{
    vector<Pos> tile = currBlock.getCellPos();
    for (Pos item : tile)
    {
        board.board[item.x][item.y] = currBlock.cellId;
    }
    currBlock = nextBlock;
    if (checkCollision() == false)
    {
        checkGameOver = true;
        PlaySound(gameOverFx);
    }
    nextBlock = getRandomBlock();
    int linesCleared = board.clearLineAll();
    if (linesCleared > 0)
    {
        PlaySound(clearLineFx);
        updateScore(linesCleared);
    }

    canHoldPiece = true;
    PlaySound(dropFx);
}

void gameHandler::updateGhostBlock()
{
    ghostBlock = currBlock; // Copy current block
    while (true)
    {
        ghostBlock.Move(1, 0); // Move down
        if (checkBounds() || !checkCollision(ghostBlock))
        {
            ghostBlock.Move(-1, 0); // Undo move
            break;
        }
    }
}

bool gameHandler::checkCollision(blockMain block)
{
    vector<Pos> tile = block.getCellPos();
    for (Pos item : tile)
    {
        if (!board.checkCollision(item.x, item.y))
        {
            return false;
        }
    }
    return true;
}

bool gameHandler::checkCollision()
{
    return checkCollision(currBlock);
}

bool gameHandler::checkBounds()
{
    vector<Pos> tile = currBlock.getCellPos();
    for (Pos item : tile)
    {
        if (board.checkBounds(item.x, item.y))
        {
            return true;
        }
    }
    return false;
}

void gameHandler::Reset()
{
    board.Initialize();
    blockSub = refreshBlocks();
    currBlock = getRandomBlock();
    nextBlock = getRandomBlock();
    checkGameOver = false;
    checkHoldPiece = false;
    heldBlock = blockMain();
    score = 0;
    moveDownTimer = 0.0f;
    moveDownDelay = 0.5f;
    lastFrameTime = GetTime();
    PlayMusicStream(music);
}

void gameHandler::updateScore(int linesCleared)
{
    switch (linesCleared)
    {
    case 1:
        score += 100;
        break;
    case 2:
        score += 300;
        break;
    case 3:
        score += 500;
        break;
    case 4:
        score += 800;
        break;
    default:
        break;
    }
}