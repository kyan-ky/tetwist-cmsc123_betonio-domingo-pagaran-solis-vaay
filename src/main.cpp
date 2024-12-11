#include "gameHandler.h"

int main()
{
    Color bgBlack = Color{53, 56, 57, 255};
    const int screenWidth = 800;
    const int screenHeight = 700;
    bool titleScreenDisplayed = false;
    bool isGamePaused = false;

    InitWindow(screenWidth, screenHeight, "Te-Twist");
    SetTargetFPS(60);

    Texture2D bgMoon = LoadTexture("assets/parallax-mountain-bg.png");
    Texture2D bgFgTrees = LoadTexture("assets/parallax-mountain-foreground-trees.png");
    Texture2D bgmountainFar = LoadTexture("assets/parallax-mountain-montain-far.png");
    Texture2D bgmountainNear = LoadTexture("assets/parallax-mountain-mountains.png");
    Texture2D bgDarkTrees = LoadTexture("assets/parallax-mountain-trees.png");

    Texture2D gif = LoadTexture("tetris.gif");
    gameHandler game = gameHandler();

 
    float scrollingMountainFar = 0.0f;
    float scrollingMountainNear = 0.0f;
    float scrollingDarkTrees = 0.0f;
    float scrollingForegroundTrees = 0.0f;

    while (!titleScreenDisplayed)
    {
        DrawTexture(gif, screenWidth / 2 - gif.width / 2, screenHeight / 2 - gif.height / 2 - 100, WHITE);
        DrawText("Press ENTER to start the game.", 60, 320, 40, YELLOW);
        DrawText("Press BACKSPACE to quit.", 120, 400, 40, RED);
        if (IsKeyPressed(KEY_ENTER))
        {
            titleScreenDisplayed = true;
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            CloseWindow();
            return 0;
        }
        BeginDrawing();
        ClearBackground(bgBlack);
        EndDrawing();
    }

    while (!WindowShouldClose())
    {
        if (!IsWindowFocused())
        {
            isGamePaused = true;
        }
        else
        {
            isGamePaused = false;
        }
        if (!isGamePaused)
        {
            UpdateMusicStream(game.music);
            game.inputHandler();
            game.updateGame();
        }

        scrollingMountainFar -= 0.1f;
        scrollingMountainNear -= 0.5f;
        scrollingDarkTrees -= 0.9f;
        scrollingForegroundTrees -= 1.0f;

        if(scrollingMountainFar <= -bgmountainFar.width*2) scrollingMountainFar = 0;
        if(scrollingMountainNear <= -bgmountainNear.width*2) scrollingMountainNear = 0;
        if(scrollingDarkTrees <= -bgDarkTrees.width*2) scrollingDarkTrees = 0;
        if(scrollingForegroundTrees <= -bgFgTrees.width*2) scrollingForegroundTrees = 0;



        BeginDrawing();
        ClearBackground(RAYWHITE);
       
        DrawTextureEx(bgMoon, (Vector2){(float)bgMoon.width - 280, 10}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgmountainFar, (Vector2){scrollingMountainFar, 20}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgmountainFar, (Vector2){scrollingMountainFar + bgmountainFar.width*2, 20}, 0.0f, 4.0f, WHITE);
        
        DrawTextureEx(bgmountainNear, (Vector2){scrollingMountainNear, 40}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgmountainNear, (Vector2){scrollingMountainNear + bgmountainNear.width*2, 40}, 0.0f, 4.0f, WHITE);

        DrawTextureEx(bgDarkTrees, (Vector2){scrollingDarkTrees, 60}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgDarkTrees, (Vector2){scrollingDarkTrees + bgDarkTrees.width*2, 60}, 0.0f, 4.0f, WHITE);

        DrawTextureEx(bgFgTrees, (Vector2){scrollingForegroundTrees, 60}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgFgTrees, (Vector2){scrollingForegroundTrees + bgFgTrees.width*2, 60}, 0.0f, 4.0f, WHITE);

        //DrawTextureEx(bgTexture, (Vector2){bgX, 0.0f}, 0.0f, scaleX, WHITE);
        //DrawTextureEx(bgTexture, (Vector2){bgX + bgTexture.width * scaleX, 0.0f}, 0.0f, scaleX, WHITE);


        Font font = Font();
        DrawRectangle(GetScreenWidth() - 200, 70, 160, 120, black);
        DrawRectangle(GetScreenWidth() - 200, 210, 160, 120, black);
        DrawRectangle(GetScreenWidth() - 200, 350, 160, 120, black);
        DrawTextEx(font, "Next", {static_cast<float>(GetScreenWidth() - 170), 15}, 45, 5, white);

        DrawRectangle(GetScreenWidth() - 220, 580, 200, 100, black);
        DrawTextEx(font, "Score", {static_cast<float>(GetScreenWidth() - 210), 500}, 60, 5, white);
        DrawTextEx(font, to_string(game.score).c_str(), {static_cast<float>(GetScreenWidth() - 200), 590}, 50, 5, white);
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
    UnloadTexture(bgmountainFar);
    UnloadTexture(bgMoon);
    UnloadTexture(bgmountainNear);
    UnloadTexture(bgDarkTrees);
    UnloadTexture(bgFgTrees);

    CloseWindow();  

    return 0;
}