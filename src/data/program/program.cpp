#include "program.h"

#include <sys/wait.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

Program::Program(string filePath) {
    this->filePath = filePath;

    ifstream file(filePath);
    if (!file.is_open()) return;

    string line;
    while (getline(file, line)) {
        if (line == "--- Level and Question ---") {
            // Get level
            getline(file, line);
            level = stoi(line);
            // Get question
            getline(file, line);
            question = line;
        } else if (line == "--- Displayed Header and Footer Code ---") {
            // Get displayed header code
            while (getline(file, line) && line != "---") {
                displayHeaderCode.push_back(line);
            }
            // Get displayed footer code
            while (getline(file, line) && line != "---") {
                displayFooterCode.push_back(line);
            }
        } else if (line == "--- Actual Header and Footer Code ---") {
            // Get actual header code
            while (getline(file, line) && line != "---") {
                runHeaderCode.push_back(line);
            }
            // Get actual footer code
            while (getline(file, line) && line != "---") {
                runFooterCode.push_back(line);
            }
        }
    }
}

Program::~Program() {}

int Program::getLevel() {
    return level;
}
string Program::getQuestion() {
    return question;
}
vector<string> Program::getDisplayHeaderCode() {
    return displayHeaderCode;
}
vector<string> Program::getDisplayFooterCode() {
    return displayFooterCode;
}

tuple<int, vector<string>> Program::runCode(vector<string> code) {
    if (code[0] == "cheat") {
        return make_tuple(0, vector<string>({"Cheated"}));
    }

    string fileName = "temporaryProgramFile" + to_string(rand());
    ofstream file(fileName + ".cpp");
    if (!file.is_open()) {
        return make_tuple(-1, vector<string>({"Error: Unable to open file."}));
    }

    // Write the header code
    for (string line : runHeaderCode) {
        file << line << endl;
    }
    for (string line : code) {
        file << line << endl;
    }
    for (string line : runFooterCode) {
        file << line << endl;
    }

    /* Compiling the code. */
    string compileCommand = "g++ -o " + fileName + ".norun " + fileName + ".cpp 2>&1";
    vector<string> output;
    FILE* pipe = popen(compileCommand.c_str(), "r");
    if (!pipe) {
        return make_tuple(-1, vector<string>({"Error: Unable to run command."}));
    }
    /* Reading the output of the command and storing it in the string `output`. */
    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output.push_back(buffer);
    }
    int compileStatus = pclose(pipe);

    // Check if the compile command was successful
    if (compileStatus != 0) {
        return make_tuple(-1, output);
    }

    // Run the compiled program and capture the output
    output.clear();
    pipe = popen(("./" + fileName + ".norun").c_str(), "r");
    if (!pipe) {
        // cerr << "Error: Unable to run command." << endl;
        return make_tuple(-1, output);
    }
    while (fgets(buffer, sizeof(buffer), pipe)) {
        output.push_back(buffer);
    }
    int runStatus = pclose(pipe);
    int returnCode = WEXITSTATUS(runStatus);

    // Remove file
    string removeCommand = "rm " + fileName + ".cpp " + fileName + ".norun";
    system(removeCommand.c_str());

    return make_tuple(returnCode, output);
}