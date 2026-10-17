#pragma once
#include <raylib.h>

class Laser
{
  public:
    Laser(Vector2 position, int speed);
    void Update();
    void Draw();
    Rectangle getRect();
    bool isActive;

  private:
    Vector2 position;
    int speed;
};
