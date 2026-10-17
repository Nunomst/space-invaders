#include "hud.hpp"

Hud::Hud()
{
    yellow         = {243, 216, 63, 255};
    font           = LoadFontEx("font/monogram.ttf", 64, 0, 0);
    spaceshipImage = LoadTexture("graphics/spaceship.png");
}

Hud::~Hud() {}

void Hud::Draw(int score, int highscore, int lives, bool run)
{
    DrawRectangleRoundedLinesEx({10, 10, 780, 780}, 0.18f, 20, 2, yellow);
    DrawLineEx({25, 730}, {775, 730}, 3, yellow);

    if (run)
    {
        DrawTextEx(font, "LEVEL 01", {570, 740}, fontSize, 2, yellow);
    }
    else
    {
        DrawTextEx(font, "GAME OVER", {570, 740}, fontSize, 2, yellow);
    }

    float x = 50.0;
    for (int i = 0; i < lives; i++)
    {
        DrawTextureV(spaceshipImage, {x, 740}, WHITE);
        x += 50;
    }

    DrawTextEx(font, "SCORE", {50, 15}, fontSize, 2, yellow);
    DrawTextEx(font, FormatWithLeadingZeros(score, 5).c_str(), {50, 40}, fontSize, 2, yellow);

    DrawTextEx(font, "HIGH SCORE", {570, 15}, fontSize, 2, yellow);
    DrawTextEx(font, FormatWithLeadingZeros(highscore, 5).c_str(), {655, 40}, fontSize, 2, yellow);
}

void Hud::Unload()
{
    UnloadFont(font);
    UnloadTexture(spaceshipImage);
}

std::string Hud::FormatWithLeadingZeros(int number, int width)
{
    std::string numberText = std::to_string(number);
    int leadingZeros       = width - numberText.length();
    return numberText      = std::string(leadingZeros, '0') + numberText;
}
