#pragma once
#include "entities/alien.hpp"
#include "entities/mysteryship.hpp"
#include "entities/obstacle.hpp"
#include "entities/spaceship.hpp"
#include <vector>

class Game {
  public:
    Game();
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    bool run;
    int lives;
    int score;
    int highscore;
    Music music;

  private:
    void DeleteInactiveLasers();
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> CreateAliens();
    void MoveAliens();
    void MoveDownAliens(int distance);
    void AlienShootLaser();
    void CheckForCollisions();
    void GameOver();
    void Reset();
    void InitGame();
    void CheckForHighScore();
    void SaveHighScoreToFile(int highScore);
    int LoadHighScoreFromFile();
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Alien> aliens;
    int aliensDirection;
    std::vector<Laser> alienLasers;
    constexpr static float alienLaserShootInterval = 0.35;
    float timeLastAlienFired;
    Mysteryship mysteryship;
    float mysteryShipSpawnInterval;
    float timeLastSpawn;
    Sound explosionSound;
};
