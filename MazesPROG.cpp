#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    bool playerAlive = true;
    bool mazeOpened = false;
    string mazeNum;
    string playerMove;

   while (playerAlive) {
        int lineCount = 0;
        if (mazeOpened == false) {
            cout << "Choose the maze's number: "; cin >> mazeNum;
        }

        string line;
        ifstream myfile("MAZE_" + mazeNum + ".txt");
        if (myfile.is_open())
        {

            while (myfile.good())
            {
                getline(myfile, line);
                if (lineCount > 0) {
                    cout << line << endl;
                }
                lineCount++;
                  
            }
            myfile.close();
            mazeOpened = true;
        }

       
        cout << "Direction to move: "; cin >> playerMove;



    }

    return 0;
}

