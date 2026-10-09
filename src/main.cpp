#include "game.hpp"
#include <raylib.h>
#include <string>

std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros       = width - numberText.length();
    return numberText      = std::string(leadingZeros, '0') + numberText;
}

int main() {
    Color grey   = {29, 29, 29, 255};
    Color yellow = {243, 216, 63, 255};

    const int offset       = 50;
    const int SCREENWIDTH  = 750;
    const int SCREENHEIGHT = 700;

    InitWindow(SCREENWIDTH + offset, SCREENHEIGHT + (offset * 2), "Scape Invaders");
    InitAudioDevice();

    Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

    Texture2D spaceshipImage = LoadTexture("graphics/spaceship.png");

    SetTargetFPS(60);

    Game game;

    while (WindowShouldClose() == false) {
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        BeginDrawing();
        ClearBackground(grey);

        DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
        DrawLineEx({25, 730}, {775, 730}, 3, yellow);

        if (game.run) {
            DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
        } else {
            DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);
        }

        float x = 50.0;
        for (int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage, {x, 740}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        DrawTextEx(font, "HIGH SCORE", {570, 15}, 34, 2, yellow);
        std::string highScoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highScoreText.c_str(), {655, 40}, 34, 2, yellow);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();
}
