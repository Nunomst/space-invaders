#pragma once
#include "laser.hpp"
#include "raylib.h"
#include <vector>

class Spaceship {
  public:
    Spaceship();
    ~Spaceship();
    void Draw();
    void MoveLeft();
    void MoveRight();
    void FireLaser();
    void Reset();
    Rectangle getRect();
    std::vector<Laser> lasers;

  private:
    Texture2D image;
    Vector2 position;
    double lastFireTime;
    Sound laserSound;
};
