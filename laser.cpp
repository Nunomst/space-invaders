#include "laser.hpp"

Laser::Laser(Vector2 position, int speed) {
    this->position = position;
    this->speed = speed;
    isActive = true;
}

void Laser::Draw() {
    if (isActive)
        DrawRectangle(position.x, position.y, 4, 15, {243, 216, 63, 255});
}

void Laser::Update() {
    position.y += speed;
    if (isActive) {
        if (position.y > GetScreenHeight() || position.y < 0) {
            isActive = false;
        }
    }
}
