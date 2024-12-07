#include "C:\raylib\raylib\src\raylib.h"
#include "gameHandler.h"

int main() {
    Color bgBlack = Color{53, 56, 57, 255};
    const int screenWidth = 800;
    const int screenHeight = 600;
    bool titleScreenDisplayed = false;
    bool isGamePaused = false;

    InitWindow(screenWidth, screenHeight, "Tetris.exe");
    SetTargetFPS(60);

    Texture2D gif = LoadTexture("tetris.gif");
    gameHandler game = gameHandler();
    
    while (!titleScreenDisplayed) {
        DrawTexture(gif, screenWidth/2 - gif.width/2, screenHeight/2 - gif.height/2 - 100, WHITE);
        DrawText("Press ENTER to start the game.", 60, 320, 40, YELLOW);
        DrawText("Press BACKSPACE to quit.", 120, 400, 40, RED);
        if (IsKeyPressed(KEY_ENTER)) {
            titleScreenDisplayed = true;
        } 
        if (IsKeyPressed(KEY_BACKSPACE)) {
            CloseWindow();
            return 0;
        } 
        BeginDrawing();
        ClearBackground(bgBlack);
        EndDrawing();
    }
    
    while (!WindowShouldClose()) {
        if (!IsWindowFocused()) {
            isGamePaused = true;
        } else {
            isGamePaused = false;
        }
        if (!isGamePaused) {
            UpdateMusicStream(game.music);
            game.inputHandler();
            game.updateGame();
        }
        BeginDrawing();
        ClearBackground(bgBlack);
        Font font = Font();
        DrawRectangle(GetScreenWidth() - 200, 60, 160, 150, black);
        DrawTextEx(font, "Next", {static_cast<float>(GetScreenWidth() - 170), 15}, 45, 5, white);
        DrawRectangle(GetScreenWidth() - 220, 300, 200, 100, black);
        DrawTextEx(font, "Score", {static_cast<float>(GetScreenWidth() - 200), 250}, 45, 5, white);
        DrawTextEx(font, to_string(game.score).c_str(), {static_cast<float>(GetScreenWidth() - 200), 330}, 50, 5, white);
        DrawRectangle(GetScreenWidth() - 780, 75, 200, 75, black);
        DrawTextEx(font, "Hold", {static_cast<float>(GetScreenWidth() - 740), 15}, 45, 5, white);
        DrawRectangle(GetScreenWidth() - 795, 275, 240, 230, black);
        DrawTextEx(font, "How to Play", {static_cast<float>(GetScreenWidth() - 790), 240}, 30, 5, white);
        DrawTextEx(font, "ARROW KEYS", {static_cast<float>(GetScreenWidth() - 790), 280}, 16, 5, white);
        DrawTextEx(font, "UP-Rotate Block", {static_cast<float>(GetScreenWidth() - 790), 320}, 12, 5, white);
        DrawTextEx(font, "LEFT-Move Block Left", {static_cast<float>(GetScreenWidth() - 790), 350}, 12, 5, white);
        DrawTextEx(font, "RIGHT-Move Block Right", {static_cast<float>(GetScreenWidth() - 790), 380}, 12, 5, white);
        DrawTextEx(font, "DOWN-Move Block Down", {static_cast<float>(GetScreenWidth() - 790), 410}, 12, 5, white);
        DrawTextEx(font, "Space-Drop Block", {static_cast<float>(GetScreenWidth() - 790), 440}, 12, 5, white);
        DrawTextEx(font, "C-Shift/Hold Block", {static_cast<float>(GetScreenWidth() - 790), 470}, 12, 5, white);
        game.drawGame();
        EndDrawing();
    }
    CloseWindow();  
    return 0;
}