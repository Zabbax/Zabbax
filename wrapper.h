#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string.h>
#include <fstream>
#include <sstream>
#include "list.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct question 
{
    string name;
    string description;
};

struct player 
{
    string name;
    int score;
};

class wrapper 
{
public:
    wrapper(string linuxfile, string playerfile) 
    {
        mlinuxFile = linuxfile;
        mGameFile = playerfile;

        modified = false;
    }

    wrapper(const wrapper& app) 
    {
        mlinuxFile = app.mlinuxFile;
        mGameFile = app.mGameFile;
        modified = false;
    }

    void run();

private:
    List<question> mQuestions;
    player players[10];
    int playerCount;
    string mlinuxFile;
    string mGameFile;

    //load commands and saved players
    void importlinuxlist();
    void importplayers();

    //parse linux commands and players
    question parselinuxline(string line);
    player parseplayer(string line);
    void printmenu();

    void printrules();
    void playgame(int startScore);
    void loadprevioussave(int& score);

    //add remove linux commands
    void add();
    void remove();

    bool modified;
    void updateplayer(string name, int score);

    //save questions and players
    void savequestion();
    void saveplayers();

    void randomize(int intArray[], int length, int min, int max);
};

int random(int min, int max);
int prompt(int min, int max, string message);
bool operator==(const question& lhs, const question& rhs);