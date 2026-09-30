#pragma once
#include "alien.hpp"
#include "obstacle.hpp"
#include "spaceship.hpp"
#include <vector>

class Game {
  public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();

  private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliensDirection;
};
