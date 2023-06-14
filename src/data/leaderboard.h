#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <string>
#include <vector>

using namespace std;

class Leaderboard {
   public:
    Leaderboard();
    void addScore(string name, int score);
    vector<pair<string, int>> getScores();

   private:
    vector<pair<string, int>> scores;
};

#endif
