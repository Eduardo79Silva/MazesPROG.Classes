#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

void display(vector<vector<char>>& maze) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            cout << maze[i][j];
            
        }
        cout << endl;
    } 
}

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
            // This loop clears the input stream and checks if the input is valid
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cin >> mazeNum;
           

            if (!cin.good()) {

                cout << "That maze doesn't exist, would you mind trying another one?";

            }
        } while (!cin.good());

        mazeFile = "MAZE_" + mazeNum + ".txt";

        mazeMap.open(mazeFile); // Used to open the maze chosen by the player

        if (mazeMap.is_open()) {
            string playerPos;
            char x;
            int mazeWidth, mazeHeight;
            int robotsNum{};

            mazeMap >> mazeHeight >> x >> mazeWidth;

            vector<vector<char>> maze(mazeHeight, vector<char>(mazeWidth));
            mazeMap >> noskipws;

            for (int i = 0; i < mazeHeight; i++) {
                getline(mazeMap, line);
                for (int j = 0; j < mazeWidth; j++) {
                    mazeMap >> maze[i][j];
                    if (maze[i][j] == 'R') {
                        robotsNum++;
                    }
                    else if (maze[i][j] == 'H') {
                        playerPos = to_string(i) + "" + to_string(j);
                    }
                }
            }
            display(maze);

            mazeMap.close();
            vector<string> robots(robotsNum + 1);
            int robotID = 1;
            for (int i = 0; i < mazeHeight; i++) {
                for (int j = 0; j < mazeWidth; j++) {
                    if (maze[i][j] == 'R') {
                        robots[robotID] = to_string(i) + "" + to_string(j);
                        robotID++;
                    }
                }
            }
            mazeOpened = true;
            auto start = std::chrono::high_resolution_clock::now();
            //play(maze, robots, playerPos, mazeNum);

        }
        else {
            cout << "That maze doesn't exist, would you mind trying another one?" << endl;
        }
    }
   
}

bool RobotsAlive(const vector<string>& robots) {
    for (int i = 1; i < robots.size(); i++) {
        if (robots[i] != "r") {
            return true;
        }
    }
    return false;
}

void MazeClear(vector<vector<char>>& maze) {
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'R' || maze[i][j] == 'H') {
                maze[i][j] = ' ';
            }
        }
    }
    return
}

void MoveRobots(string& player, vector<vector<char>>& maze, vector<string>& robots, unsigned mazeNum) {
    int playerX, playerY, robotX, robotY;

}

void Play(vector<vector<char>>& maze, vector<string>& robots, string playerPos, unsigned int mazeNum) {
    while (playerPos != "h" && RobotsAlive(robots) && !cin.eof()) {
        display(maze);
        MazeClear(maze);
        //PlayerInput();
        //MoveRobots();
    }
}

void MainMenu() {
    unsigned short answer;
    bool error = false;

    do{
        cout <<
            "----------------" << endl <<
            "|  MAIN  MENU  |" << endl <<
            "|Rules: 1      |" << endl <<
            "|Play: 2       |" << endl <<
            "|Exit: 0       |" << endl <<
            "----------------" << endl;
        cin >> answer;
        if (cin.eof()) {
            return;
        }
        if (!cin.good()) {
            cout << "Sadly that's not an option. Please choose another one."<<endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            error = true;

        }
        else if(answer == 1)
        {
            cout << ""; //insert rules here
            MainMenu();
            error = false;
        }
        else if (answer == 2) {
            MazeOpened();
            error = false;
        }
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

