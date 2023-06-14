#include <string>
#include <iostream>
#include "util.h"

using namespace std;

string getColor(int color) {
    return "\033[" + to_string(color) + "m";
}

void drawText(string text, int x, int y, int color) {
    setCursorPosition(x, y);
    cout << getColor(color) << text << "\033[0m";
}

// mr_JonhaS_HSii -> Mr Jonhas Hsii
string toCapitalCase(string text) {
    string result = "";
    bool isSpace = true;
    for (int i = 0; i < text.length(); i++) {
        if (isSpace) {
            result += toupper(text[i]);
            isSpace = false;
        } else {
            if (text[i] == ' ' || text[i] == '_') {
                isSpace = true;
                result += ' ';
            } else {
                result += tolower(text[i]);
            }
        }
    }
    return result;
}

void setCursorPosition(int x, int y) {
    cout << "\033[" << (y + 1) << ";" << (x + 1) << "H";
}

void showCursor() {
    cout << "\033[?25h";
}

void hideCursor() {
    cout << "\033[?25l";
}