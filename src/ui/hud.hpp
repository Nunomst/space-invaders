#pragma once
#include <raylib.h>
#include <string>

class Hud
{
  public:
    Hud();
    ~Hud();
    void Draw(int score, int highscore, int lives, bool run);
    void Unload();

  private:
    Font font;
    Texture2D spaceshipImage;
    Color yellow;
    float fontSize = 34.0f;

    std::string FormatWithLeadingZeros(int number, int width);
};
