#include "fileManager.h"

#include <fstream>
#include <iostream>

using namespace std;

vector<vector<string>> read(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return {};
    }
    vector<vector<string>> lines;
    int numLines;
    file >> numLines;
    for (int i = 0; i < numLines; i++) {
        vector<string> line;
        string word;
        while (file >> word) {
            line.push_back(word);
        }
        lines.push_back(line);
    }
    return lines;
}

template <typename T>
vector<T> read(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        return {};
    }
    vector<T> lines;
    int numLines;
    file >> numLines;
    for (int i = 0; i < numLines; i++) {
        T line;
        file >> line;
        lines.push_back(line);
    }
    return lines;
}

void write(string filename, vector<vector<string>> lines) {
    ofstream file(filename);
    file << lines.size() << endl;
    for (vector<string> line : lines) {
        for (string word : line) {
            file << word << " ";
        }
        file << endl;
    }
}

template <typename T>
void write(string filename, vector<T> lines) {
    ofstream file(filename);
    file << lines.size() << endl;
    for (T line : lines) {
        file << line << endl;
    }
}