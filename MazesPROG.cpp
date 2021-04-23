#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    string mazeNum;
    cout << "Choose the maze's number: "; cin >> mazeNum;
    string line;
    ifstream myfile("MAZE_" + mazeNum + ".txt");
    if (myfile.is_open())
    {
        while (myfile.good())
        {
            getline(myfile, line);
            cout << line << endl;
        }
        myfile.close();
    }

    else cout << "Unable to open file";

    return 0;
}

