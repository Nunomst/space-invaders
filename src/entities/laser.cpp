#include "laser.hpp"

Laser::Laser(Vector2 position, int speed)
{
    this->position = position;
    this->speed    = speed;
    isActive       = true;
}

void Laser::Draw()
{
    if (isActive)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

Rectangle Laser::getRect()
{
    return {position.x, position.y, 4, 15};
}

void Laser::Update()
{
    if (isActive)
    {
        position.y += speed;
        if (position.y > GetScreenHeight() - 100 || position.y < 25)
        {
            isActive = false;
        }
    }
}
