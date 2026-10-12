#include "save.hpp"
#include <fstream>
#include <iostream>

Save::Save() {}

Save::~Save() {}

void Save::CheckForHighScore(int score)
{
    if (score > highscore)
    {
        highscore = score;
        SaveHighScoreToFile(highscore);
    }
}

int Save::LoadHighScoreFromFile()
{
    int loadedHighScore = 0;
    std::ifstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile >> loadedHighScore;
        highScoreFile.close();
    }
    else
    {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighScore;
}

void Save::SaveHighScoreToFile(int highScore)
{
    std::ofstream highScoreFile("highscore.txt");
    if (highScoreFile.is_open())
    {
        highScoreFile << highScore;
        highScoreFile.close();
    }
    else
    {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}
