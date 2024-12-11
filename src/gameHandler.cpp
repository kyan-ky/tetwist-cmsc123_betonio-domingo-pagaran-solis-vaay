#include "gameHandler.h"
#include "board.h"
#include <random>
#include <stdlib.h>
#include <cstring>
#include <deque>
#include <iostream>
#include <algorithm>
#include <fstream>

// using namespace std;

gameHandler::gameHandler()
{
    board = Board();
    blockSub = refreshBlocks();         // Initialize the block set
    nextBlocks = getRandomBlockQueue(); // Fill the queue with random blocks

    if (!nextBlocks.empty())
    {
        currBlock = nextBlocks.front(); // Assign the first block as the current block
        nextBlocks.pop_front();         // Remove the used block
    }

    if (!nextBlocks.empty())
    {
        nextBlock = nextBlocks.front(); // Assign the second block as the next block
        nextBlocks.pop_front();         // Remove the used block
    }

    secondIndex = 0;
    if (!nextBlocks.empty())
    {
        secondBlock = nextBlocks.front(); // Assign third block for display
        nextBlocks.pop_front();
    }

    if (!nextBlocks.empty())
    {
        thirdBlock = nextBlocks.front(); // Assign fourth block for display
    }

    checkGameOver = false;
    checkHoldPiece = false;
    score = 0;
    highScore = 0;
    LoadHighScore();
    moveDownTimer = 0.0f;
    moveDownDelay = 0.7f;
    lastFrameTime = GetTime();
    InitAudioDevice();
    music = LoadMusicStream("sound/Tetris.mp3");
    PlayMusicStream(music);
    clearLineFx = LoadSound("sound/clear.wav");
    gameOverFx = LoadSound("sound/gameover.wav");
    moveFx = LoadSound("sound/move.mp3");
    dropFx = LoadSound("sound/drop.mp3");

    moveDelay = 0.08f; // Delay in seconds (0.2 default)
    lastMoveTime = 0.0f;

    canHoldPiece = true;

    updateGhostBlock(); // Initialize ghost block

    flippedBoard = false; // Flag to track if the board has been flipped
}

gameHandler::~gameHandler()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}

void gameHandler::drawGame()
{
    board.drawBoard();
    currBlock.Draw();

    // Draw ghost block with a translucent color
    Color ghostColor = Fade(WHITE, 0.15f); // Adjust transparency as needed
    ghostBlock.Draw(ghostColor);

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

    int secondBlockX = GetScreenWidth() - 250;
    int secondBlockY = 240;
    switch (secondBlock.cellId)
    {
    case 3:
        secondBlock.DrawAt(secondBlockX - 20, secondBlockY + 20);
        break;
    case 6:
        secondBlock.DrawAt(secondBlockX - 20, secondBlockY + 10);
        break;
    default:
        secondBlock.DrawAt(secondBlockX, secondBlockY);
    }

    int thirdBlockX = GetScreenWidth() - 250;
    int thirdBlockY = 370;
    switch (thirdBlock.cellId)
    {
    case 3:
        thirdBlock.DrawAt(thirdBlockX - 20, thirdBlockY + 20);
        break;
    case 6:
        thirdBlock.DrawAt(thirdBlockX - 20, thirdBlockY + 10);
        break;
    default:
        thirdBlock.DrawAt(thirdBlockX, thirdBlockY);
    }

    int heldBlockX = GetScreenWidth() - 730;
    int heldBlockY = 100;
    switch (heldBlock.cellId)
    {
    case 3:
        heldBlock.DrawAt(heldBlockX - 5, heldBlockY + 5);
        break;
    case 6:
        heldBlock.DrawAt(heldBlockX - 5, heldBlockY + 10);
        break;
    default:
        heldBlock.DrawAt(heldBlockX, heldBlockY);
    }

    Font font = LoadFont("src/VCR_OSD_MONO_1.001.ttf"); // Ensure you provide a valid font path
    if (checkGameOver)
    {
        UpdateHighScore(score);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(GRAY, 0.8f));
        DrawTextEx(font, "Game Over", {static_cast<float>(GetScreenWidth() / 2 - 150), static_cast<float>(GetScreenHeight() / 2 - 50)}, 60, 5, RED);
        DrawTextEx(font, "Press ENTER to Play Again", {static_cast<float>(GetScreenWidth() / 2 - 280), static_cast<float>(GetScreenHeight() / 2 + 100)}, 40, 5, YELLOW);
        StopMusicStream(music);
    }

    // Alert if the board was flipped
    if (flippedBoard)
    {
        flippedMessageTime = GetTime(); // Start the timer when the message appears
        displayFlippedMessage = true;   // Set the flag to display the message
        flippedBoard = false;           // Reset the flag after drawing the message
    }

    // Show the flipped message for 3 seconds
    if (displayFlippedMessage && GetTime() - flippedMessageTime < 1.0f)
    {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(GRAY, 0.1f));
        DrawTextEx(font, "Board Flipped!", {static_cast<float>(GetScreenWidth() / 2 - 150), static_cast<float>(GetScreenHeight() / 2)}, 40, 5, ORANGE);
    }
    else
    {
        displayFlippedMessage = false; // Stop showing the message after 3 seconds
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
    case 8:
        return "Bomb";
    case 9:
        return "Star";
    default:
        return "None";
    }
}

blockMain gameHandler::getCurrentBlock()
{
    if (nextBlocks.empty())
    {
        nextBlocks = getRandomBlockQueue();
    }
    return nextBlocks.front();
}

blockMain gameHandler::getRandomBlock()
{
    if (blockSub.empty())
    {
        blockSub = refreshBlocks();
    }
    cout << "current popped" << endl;
    blockMain currBlock = nextBlocks.front();
    nextBlocks.pop_front();
    return currBlock;
}

blockMain gameHandler::getNextBlock()
{
    if (nextBlocks.empty())
    {
        nextBlocks = getRandomBlockQueue();
    }

    if (secondIndex >= 6)
    {
        secondIndex = 0;
    }

    cout << "nextblock pop" << endl;
    blockMain next = nextBlocks.front();
    nextBlocks.pop_front();

    return next;
}

blockMain gameHandler::getSecondBlock()
{
    if (nextBlocks.empty())
    {
        nextBlocks = getRandomBlockQueue();
    }

    blockMain s = nextBlocks.front();
    return s;
}

blockMain gameHandler::getThirdBlock()
{
    if (nextBlocks.size() <= 1)
    {
        nextBlocks = getRandomBlockQueue();
    }
    blockMain third = nextBlocks.at(1);

    return third;
}

deque<blockMain> gameHandler::getRandomBlockQueue()
{
    deque<blockMain> blocks;

    random_device rd;
    mt19937 g(rd());

    shuffle(blockSub.begin(), blockSub.end(), g);
    for (int i = 0; i < 7; i++)
    {
        blocks.emplace_back(blockSub[i]);
    }

    return blocks;
}

vector<blockMain> gameHandler::refreshBlocks()
{
    return {blockI(), blockJ(), blockL(), blockO(), blockS(), blockT(), blockZ(), blockBomb(), blockStar()};
}

void gameHandler::holdPiece()
{
    if (!canHoldPiece)
        return;

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

    heldBlock.resetPosition(0, 0);
    currBlock.resetPosition(0, 0); // Reset the position of the new current block
    canHoldPiece = false;          // Disable holding until the next block is placed
}

void gameHandler::inputHandler()
{
    if (checkGameOver)
    {
        if (IsKeyPressed(KEY_ENTER))
        { // Use IsKeyPressed for single press events
            UpdateHighScore(score);
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
    if (IsKeyPressed(KEY_C) && canHoldPiece)
    {
        holdPiece();
        canHoldPiece = false;
    }

    updateGhostBlock();
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
    heldBlockBool = true;
    if (score % 800 == 0 && score > 0)
    {
        if (moveDownDelay > 0.1f)
        {                           // Ensure it doesn't go below 0.1 seconds
            moveDownDelay -= 0.05f; // Decrease delay by 0.05 seconds
        }
    }
    if (moveDownTimer >= moveDownDelay)
    {
        moveDown();
        moveDownTimer = 0.0f;

        updateGhostBlock(); // Update ghost block position
    }
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
    if (checkGameOver)
        return;

    // Attempt to rotate the block
    currBlock.rotateBlock();

    // Check for boundary violations or collisions
    if (checkBounds() || !checkCollision())
    {
        // Try shifting the block to accommodate rotation
        for (int offset = -2; offset <= 2; ++offset)
        {
            currBlock.Move(0, offset); // Move horizontally
            if (!checkBounds() && checkCollision())
            {
                PlaySound(moveFx); // Play sound for successful adjustment
                return;            // Successfully rotated with an adjustment
            }
            currBlock.Move(0, -offset); // Undo the shift
        }

        // If no adjustment works, undo the rotation
        currBlock.rotateUndo();
    }
    else
    {
        PlaySound(moveFx); // Play sound for successful rotation
    }
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
    if (currBlock.cellId == 8)
    {
        int bombX = tile[0].x; // Assuming all positions in the bomb block are the same
        int bombY = tile[0].y;
        board.clear3x3Block(bombX, bombY); // Clear the surrounding 3x3 area
        PlaySound(dropFx);                 // Play the sound for bomb drop
    }
    else if (currBlock.cellId == 9)
    {
        int bombX = tile[0].x; // Assuming all positions in the bomb block are the same
        int bombY = tile[0].y;
        board.populate3x3Block(bombX, bombY, 10); // Clear the surrounding 3x3 area
        PlaySound(dropFx);                        // Play the sound for bomb drop
    }
    currBlock = nextBlock;
    if (checkCollision() == false)
    {
        checkGameOver = true;
        PlaySound(gameOverFx);
    }

    nextBlock = getNextBlock();
    secondBlock = getSecondBlock();
    thirdBlock = getThirdBlock();

    int linesCleared = board.clearLineAll();
    if (linesCleared > 0)
    {
        PlaySound(clearLineFx);
        updateScore(linesCleared);
        if (linesCleared >= 4)
        {
            reverseBoard();
            flippedBoard = true; // Mark that the board has been flipped
        }
    }

    canHoldPiece = true;
    PlaySound(dropFx);
    updateGhostBlock();
}

void gameHandler::reverseBoard()
{
    int rows = board.getRows();
    int cols = board.getCols();

    // Reverse the board
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols / 2; ++j)
        {
            std::swap(board.board[i][j], board.board[i][cols - j - 1]);
        }
    }
}

void gameHandler::updateGhostBlock()
{
    ghostBlock = currBlock; // Copy current block
    while (true)
    {
        ghostBlock.Move(1, 0); // Move down
        if (checkBounds(ghostBlock) || !checkCollision(ghostBlock))
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

bool gameHandler::checkBounds(blockMain block)
{
    vector<Pos> tile = block.getCellPos();
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
    deque<blockMain> nextBlocks = getRandomBlockQueue();
    currBlock = getCurrentBlock();
    nextBlock = getNextBlock();
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

void gameHandler::LoadHighScore()
{
    std::ifstream scoreFile("highscore.txt");
    if (!scoreFile.is_open())
    {
        // If the file doesn't exist, create it with a default value of 0
        std::ofstream createFile("highscore.txt");
        createFile << "0"; // Initialize high score to 0
        createFile.close();
        highScore = 0;
    }
    else
    {
        // Read the high score from the file
        scoreFile >> highScore;
        scoreFile.close();
    }
}

// Save the high score to the file
void gameHandler::UpdateHighScore(int score)
{
    if (score > highScore)
    {
        highScore = score; // Update the high score
        std::ofstream scoreFile("highscore.txt");
        if (scoreFile.is_open())
        {
            scoreFile << highScore; // Save the new high score
            scoreFile.close();
        }
        else
        {
            std::cerr << "Error: Could not write to highscore.txt\n";
        }
    }
}
