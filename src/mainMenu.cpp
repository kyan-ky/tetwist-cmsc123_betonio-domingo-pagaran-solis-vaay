#include <raylib.h>
#include <string>
#include <vector>

using namespace std;

void showMainMenu(Font font, Texture2D bgMenu, Texture2D logo, gameHandler &game, int screenWidth, int screenHeight)
{
    bool titleScreenDisplayed = false;
    int selectedOption = 0;

    while (!titleScreenDisplayed)
    {
        BeginDrawing();
        ClearBackground(Color{53, 56, 57, 255});

        // Draw the background image for the menu
        Rectangle sourceRect = {0, 0, (float)bgMenu.width, (float)bgMenu.height};
        Rectangle destRect = {0, 0, (float)screenWidth, (float)screenHeight};
        Vector2 origin = {0, 0};
        DrawTexturePro(bgMenu, sourceRect, destRect, origin, 0.0f, WHITE);

        // Draw the logo
        float scaleX = (float)screenWidth / logo.width;
        float scaleY = (float)screenHeight / logo.height;
        float scale = scaleX < scaleY ? scaleX : scaleY;
        Rectangle dest = {
            screenWidth / 2.0f - (logo.width * scale) / 2.0f,
            0,
            logo.width * scale,
            logo.height * scale};
        DrawTexturePro(logo, {0, 0, (float)logo.width, (float)logo.height}, dest, origin, 0.0f, WHITE);

        // Draw the high score text
        std::string highScoreText = "High Score: " + std::to_string(game.highScore);
        DrawTextEx(font, highScoreText.c_str(), {screenWidth / 2.0f - MeasureText(highScoreText.c_str(), 30) / 2, float(screenHeight) - 50}, 30, 2, YELLOW);

        // Menu options
        std::vector<std::string> menuOptions = {"Play", "Mechanics", "Quit"};
        if (IsKeyPressed(KEY_DOWN))
        {
            selectedOption = (selectedOption + 1) % menuOptions.size();
        }
        if (IsKeyPressed(KEY_UP))
        {
            selectedOption = (selectedOption - 1 + menuOptions.size()) % menuOptions.size();
        }

        // Draw menu options
        for (size_t i = 0; i < menuOptions.size(); ++i)
        {
            std::string displayText = (i == selectedOption)
                                          ? ">> " + menuOptions[i] + " <<"
                                          : menuOptions[i];

            Color color = (i == selectedOption) ? YELLOW : GRAY;
            DrawTextEx(font, displayText.c_str(),
                       {static_cast<float>(screenWidth / 2 - MeasureText(displayText.c_str(), 40) / 2),
                        static_cast<float>(dest.height + 20 + i * 50)},
                       40, 2, color);
        }

        // Handle selection
        if (IsKeyPressed(KEY_ENTER))
        {
            if (selectedOption == 0) // Play
            {
                titleScreenDisplayed = true;
            }
            else if (selectedOption == 1) // Mechanics
            {
                // Transition to mechanics screen
                // You can implement this screen transition logic here
            }
            else if (selectedOption == 2) // Quit
            {
                CloseWindow();
                return;
            }
        }

        EndDrawing();
    }
}
