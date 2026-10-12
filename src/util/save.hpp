#pragma once

class Save
{
  public:
    Save();
    ~Save();
    void CheckForHighScore(int score);
    int LoadHighScoreFromFile();

  private:
    int highscore;
    void SaveHighScoreToFile(int highScore);
};
