#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>

using namespace std;

vector<vector<string>> read(string filename);

template <typename T>
vector<T> read(string filename);

void write(string filename, vector<vector<string>> lines);

template <typename T>
void write(string filename, vector<T> lines);

#endif