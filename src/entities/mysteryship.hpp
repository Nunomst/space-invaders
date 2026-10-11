#pragma once
#include <raylib.h>

class Mysteryship
{
  public:
    Mysteryship();
    ~Mysteryship();
    void Update();
    void Draw();
    void Spawn();
    Rectangle getRect();
    bool isVisible;

  private:
    Vector2 position{0.0f, 0.0f};
    Texture2D image;
    int speed = 0;
};
