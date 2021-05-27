//T07_G12
using namespace std;
#include "Game.h"
#include "Maze.h"
#include "Movement.h"
#include "Player.h"
#include "Position.h"
#include "Post.h"
#include "Robot.h"

void MazeOpened() {
    string mazeNum;
    string playerMove;
    string line;
    string mazeFile;
    bool mazeOpened = false;

    ifstream mazeMap;

    while (mazeOpened == false) {
        cout << "Choose the maze's number (for numbers until 10 add a '0' before): ";
        do {
            cin.clear();
            cin.ignore(INT_MAX, '\n');                  //Emptying input stream
            cin >> mazeNum;


            if (!cin.good()) {

                cout << "That maze doesn't exist, would you mind trying another one?";

            }
        } while (!cin.good());

        mazeFile = "MAZE_" + mazeNum + ".txt";

        mazeMap.open(mazeFile); // Used to open the maze chosen by the player

        if (mazeMap.is_open()) {
            map.close();
            error = false;
            Game game(file);
            play(game);
            return;

        }
        else {
            cout << "That maze doesn't exist, would you mind trying another one?" << endl;
        }

    }

}

void MainMenu() {
    unsigned short answer;
    bool error = false;

    do {
        cout <<
            "----------------" << endl <<
            "|  MAIN  MENU  |" << endl <<
            "|Rules:   1    |" << endl <<
            "|Play:    2    |" << endl <<
            "|Winners: 3    |" << endl <<
            "|Exit:    0    |" << endl <<
            "----------------" << endl;
        cin >> answer;
        if (cin.eof()) {
            return;
        }
        if (!cin.good()) {
            cout << "Sadly that's not an option. Please choose another one." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            error = true;

        }
        else if (answer == 1)
        {
            cout << "##########################################################################################################" << endl <<
                "|                                                RULES                                                   |" << endl <<
                "##########################################################################################################" << endl <<
                "|You will play in a maze made up of high-voltage fences.                                                 |" << endl <<
                "|There are angry robots chasing you.                                                                     |" << endl <<
                "|The only way you have to win is by crushing them agaisnt each other or the fences                       |" << endl <<
                "|Although, if you hit the robots or the fences you're the one dying. R.I.P.                              |" << endl <<
                "|The robots use a built in sonar system to detect you and walk directly towards you                      |" << endl <<
                "|                                                                                                        |" << endl <<
                "|You can move in all the directions using the following keys                                             |" << endl <<
                "|                                                                                                        |" << endl <<
                "|                                     Q        W         E                                               |" << endl <<
                "|                                                                                                        |" << endl <<
                "|                                     A       You        D                                               |" << endl <<
                "|                                                                                                        |" << endl <<
                "|                                     Z        X         C                                               |" << endl <<
                "|                                                                                                        |" << endl <<
                "|You can also stay in the same place by choosing 'S'.                                                    |" << endl <<
                "##########################################################################################################" << endl;
            MainMenu();
            error = false;
        }
        else if (answer == 2) {
            MazeOpened();
            error = false;
        }

        // Player opens winners
        //
        //
        //


        else if (answer == 0) {
            error = false;
            return;
        }
        else {
            cout << "Sadly that's not an option. Please choose another one." << endl;
        }
    } while (error);
}

int main()
{
    MainMenu();

    return 0;
}
