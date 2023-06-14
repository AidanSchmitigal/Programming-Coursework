#include "leaderboard.h"

#include "../fileManager.h"

using namespace std;

Leaderboard::Leaderboard() {
    vector<vector<string>> entries = read("src/assets/data/leaderboard.txt");
    for (vector<string> entry : entries) {
        scores.push_back(make_pair(entry[0], stoi(entry[1])));
    }
}

void Leaderboard::addScore(string name, int score) {
    scores.push_back(make_pair(name, score));
    vector<vector<string>> entries;
    for (pair<string, int> score : scores) {
        entries.push_back({score.first, to_string(score.second)});
    }
    write("src/assets/data/leaderboard.txt", entries);
}

vector<pair<string, int>> Leaderboard::getScores() {
    return scores;
}