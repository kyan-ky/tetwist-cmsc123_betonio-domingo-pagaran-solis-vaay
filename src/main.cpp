#include "gameHandler.h"

int main()
{
    Color bgBlack = Color{53, 56, 57, 255};
    Font font = LoadFont("src/VCR_OSD_MONO_1.001.ttf");
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
    Texture2D bgMenu = LoadTexture("assets/menu.png");
    Texture2D logo = LoadTexture("assets/logo.png");

    Texture2D gif = LoadTexture("tetris.gif");
    gameHandler game = gameHandler();

    float scrollingMountainFar = 0.0f;
    float scrollingMountainNear = 0.0f;
    float scrollingDarkTrees = 0.0f;
    float scrollingForegroundTrees = 0.0f;

    enum ScreenState
    {
        MAIN_MENU,
        MECHANICS_SCREEN
    };

    ScreenState currentScreen = MAIN_MENU;
    int selectedOption = 0;

    while (!titleScreenDisplayed)
    {
        BeginDrawing();
        ClearBackground(bgBlack);

        Rectangle sourceRect = {0, 0, (float)bgMenu.width, (float)bgMenu.height};

        Rectangle destRect = {0, 0, (float)screenWidth, (float)screenHeight};

        Vector2 origin = {0, 0};

        DrawTexturePro(bgMenu, sourceRect, destRect, origin, 0.0f, WHITE);

        if (currentScreen == MAIN_MENU)
        {
            float scaleX = (float)screenWidth / logo.width;
            float scaleY = (float)screenHeight / logo.height;
            float scale = scaleX < scaleY ? scaleX : scaleY;

            Rectangle dest = {
                screenWidth / 2.0f - (logo.width * scale) / 2.0f,
                0,
                logo.width * scale,
                logo.height * scale};

            float textVerticalOffset = dest.height + 20;

            std::string highScoreText = "High Score: " + std::to_string(game.highScore);
            DrawTextEx(font, highScoreText.c_str(), {screenWidth / 2.0f - MeasureText(highScoreText.c_str(), 30) / 2, screenHeight - 50}, 30, 2, YELLOW);

            Rectangle src = {0, 0, (float)logo.width, (float)logo.height};
            Vector2 origin = {0, 0};
            DrawTexturePro(logo, src, dest, origin, 0.0f, WHITE);

            std::vector<std::string> menuOptions = {"Play", "Mechanics", "Quit"};

            if (IsKeyPressed(KEY_DOWN))
            {
                selectedOption = (selectedOption + 1) % menuOptions.size();
            }
            if (IsKeyPressed(KEY_UP))
            {
                selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
            }

            for (size_t i = 0; i < menuOptions.size(); ++i)
            {
                std::string displayText = (i == selectedOption)
                                              ? ">> " + menuOptions[i] + " <<"
                                              : menuOptions[i];

                Color color = (i == selectedOption) ? YELLOW : GRAY;
                DrawTextEx(font, displayText.c_str(),
                           {static_cast<float>(screenWidth / 2 - MeasureText(displayText.c_str(), 40) / 2),
                            static_cast<float>(textVerticalOffset + i * 50)},
                           40, 2, color);
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                if (selectedOption == 0)
                {
                    titleScreenDisplayed = true;
                }
                else if (selectedOption == 1)
                {
                    currentScreen = MECHANICS_SCREEN;
                }
                else if (selectedOption == 2)
                {
                    CloseWindow();
                    return 0;
                }
            }
        }

        else if (currentScreen == MECHANICS_SCREEN)
        {
            DrawTextEx(font, "How to Play", {225, 60}, 50, 10, WHITE);
            DrawTextEx(font, "ARROW KEYS", {270, 160}, 25, 10, WHITE);
            DrawTextEx(font, "[UP] - Rotate Block", {200, 200}, 18, 10, WHITE);
            DrawTextEx(font, "[LEFT] - Move Block Left", {200, 230}, 18, 10, WHITE);
            DrawTextEx(font, "[RIGHT] - Move Block Right", {200, 260}, 18, 10, WHITE);
            DrawTextEx(font, "[DOWN] - Move Block Down", {200, 290}, 18, 10, WHITE);
            DrawTextEx(font, "[SPACE] - Drop Block", {200, 320}, 18, 10, WHITE);
            DrawTextEx(font, "[C] - Shift/Hold Block", {200, 350}, 18, 10, WHITE);

            DrawTextEx(font, "POWER-UPS", {20, 400}, 25, 10, WHITE);
            DrawTextEx(font, "BOMB - occuppies a single cell and clears all \n      blocks in the 8 surrounding cells\n      when triggered.", {20, 460}, 18, 10, WHITE);
            DrawTextEx(font, "STAR - occuppies a single cell and fills all \n      blocks in the 8 surrounding cells\n      when triggered.", {20, 520}, 18, 10, WHITE);
            DrawTextEx(font, "4-LINE CLEAR - Clearing four lines flips \n      the entire board horizontally.", {20, 580}, 18, 10, WHITE);

            DrawTextEx(font, "[SPACE] Main Menu",
                       {screenWidth - 250, screenHeight - 50}, 15, 5, YELLOW);

            if (IsKeyPressed(KEY_SPACE))
            {
                currentScreen = MAIN_MENU;
            }
        }

        if (WindowShouldClose())
        {
            CloseWindow();
            return 0;
        }

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

        if (scrollingMountainFar <= -bgmountainFar.width * 2)
            scrollingMountainFar = 0;
        if (scrollingMountainNear <= -bgmountainNear.width * 2)
            scrollingMountainNear = 0;
        if (scrollingDarkTrees <= -bgDarkTrees.width * 2)
            scrollingDarkTrees = 0;
        if (scrollingForegroundTrees <= -bgFgTrees.width * 2)
            scrollingForegroundTrees = 0;

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureEx(bgMoon, (Vector2){(float)bgMoon.width - 280, 10}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgmountainFar, (Vector2){scrollingMountainFar, 20}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgmountainFar, (Vector2){scrollingMountainFar + bgmountainFar.width * 2, 20}, 0.0f, 4.0f, WHITE);

        DrawTextureEx(bgmountainNear, (Vector2){scrollingMountainNear, 40}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgmountainNear, (Vector2){scrollingMountainNear + bgmountainNear.width * 2, 40}, 0.0f, 4.0f, WHITE);

        DrawTextureEx(bgDarkTrees, (Vector2){scrollingDarkTrees, 60}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgDarkTrees, (Vector2){scrollingDarkTrees + bgDarkTrees.width * 2, 60}, 0.0f, 4.0f, WHITE);

        DrawTextureEx(bgFgTrees, (Vector2){scrollingForegroundTrees, 60}, 0.0f, 4.0f, WHITE);
        DrawTextureEx(bgFgTrees, (Vector2){scrollingForegroundTrees + bgFgTrees.width * 2, 60}, 0.0f, 4.0f, WHITE);

        // DrawTextureEx(bgTexture, (Vector2){bgX, 0.0f}, 0.0f, scaleX, WHITE);
        // DrawTextureEx(bgTexture, (Vector2){bgX + bgTexture.width * scaleX, 0.0f}, 0.0f, scaleX, WHITE);

        Font font = LoadFont("src/VCR_OSD_MONO_1.001.ttf");
        DrawRectangle(GetScreenWidth() - 200, 70, 160, 120, black);
        DrawRectangle(GetScreenWidth() - 200, 210, 160, 120, black);
        DrawRectangle(GetScreenWidth() - 200, 350, 160, 120, black);
        DrawTextEx(font, "Next", {static_cast<float>(GetScreenWidth() - 170), 15}, 45, 5, white);

        DrawRectangle(GetScreenWidth() - 220, 580, 200, 100, black);
        DrawTextEx(font, "Score", {static_cast<float>(GetScreenWidth() - 210), 500}, 60, 5, white);
        DrawTextEx(font, to_string(game.score).c_str(), {static_cast<float>(GetScreenWidth() - 200), 590}, 50, 5, white);
        DrawRectangle(GetScreenWidth() - 760, 75, 160, 120, black);
        DrawTextEx(font, "Hold", {static_cast<float>(GetScreenWidth() - 740), 15}, 45, 5, white);

        game.drawGame();
        EndDrawing();
    }
    UnloadTexture(bgmountainFar);
    UnloadTexture(bgMenu);
    UnloadTexture(bgMoon);
    UnloadTexture(bgmountainNear);
    UnloadTexture(bgDarkTrees);
    UnloadTexture(bgFgTrees);
    UnloadTexture(logo);

    CloseWindow();

    return 0;
}