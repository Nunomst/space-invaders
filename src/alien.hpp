#pragma once
#include <raylib.h>

class Alien {
  public:
    Alien(int type, Vector2 position);
    void Draw();
    void Update();
    int GetType();
    Texture2D image;
    int type;
    Vector2 position;

  private:
};
