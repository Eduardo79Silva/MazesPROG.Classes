#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    MazeOpened();

    return 0;
}

void Play() {

    auto start = high_resolution_clock::now();

}

void player_input() {

    string key;
    string playerPos;
    string pl = "H";

    while (pl == "H") {

        cout << "Where do you want to go? "; cin >> key;

        if (key == "q") {

            if (maze[i - 1][j + 1] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i - 1][j + 1] == "R") || (maze[i - 1][j + 1] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i - 1][j + 1];

            }
        }

        if (key == "w") {

            if (maze[i][j + 1] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i][j + 1] == "R") || (maze[i][j + 1] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i][j + 1];

            }

        }

        if (key == "e") {

            if (maze[i + 1][j + 1] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i + 1][j + 1] == "R") || (maze[i + 1][j + 1] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i + 1][j + 1];

            }

        }

        if (key == "a") {

            if (maze[i - 1][j] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i - 1][j] == "R") || (maze[i - 1][j] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i - 1][j];

            }

        }

        if (key == "s") {

            continue;

        }

        if (key == "d") {

            if (maze[i + 1][j] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i + 1][j] == "R") || (maze[i + 1][j] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i + 1][j];

            }

        }

        if (key == "z") {

            if (maze[i - 1][j - 1] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i - 1][j - 1] == "R") || (maze[i - 1][j - 1] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i - 1][j - 1];

            }

        }

        if (key == "x") {

            if (maze[i][j - 1] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i][j - 1] == "R") || (maze[i][j - 1] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i][j - 1];

            }

        }

        if (key == "c") {

            if (maze[i + 1][j - 1] == "r") {

                cout << "That position is invalid. \n"; cout << "Please try again.";

            }

            else if ((maze[i + 1][j - 1] == "R") || (maze[i + 1][j - 1] == "*")) {

                pl = "h";

            }

            else {

                playerPos == maze[i + 1][j - 1];

            }

        }

        GameOver();

    }

}


void GameOver() {

    string inp = " ";

    cout << (string(100, "\n"));

    cout << "Game Over\n";

    cout << "Press space to try again\n"; cout << "Press any other key to exit "; cin >> inp;

    if (inp == " ") {

        main();

    }

}