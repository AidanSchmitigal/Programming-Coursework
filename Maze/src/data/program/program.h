#include <string>
#include <tuple>
#include <vector>

using namespace std;

class Program {
   public:
    Program(string filePath);
    ~Program();

    int getLevel();
    string getQuestion();
    vector<string> getDisplayHeaderCode();
    vector<string> getDisplayFooterCode();

    tuple<int, vector<string>> runCode(vector<string> code);

   private:
    string filePath;
    int level;
    string question;
    vector<string> displayHeaderCode;
    vector<string> displayFooterCode;
    vector<string> runHeaderCode;
    vector<string> runFooterCode;
};