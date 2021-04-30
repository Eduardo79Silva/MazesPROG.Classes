//T07_G12
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
using namespace std;

void SameCellRobots(vector<string>& robots, const int robotsX, const int robotsY) { //Function to detect when 2 robots collide
    for (int i = 1; i < robots.size(); i++) {
        if (to_string(robotsX) + " " + to_string(robotsY) == robots[i]) {
            robots[i] = "r";
        }
    }
}
void Display(const vector<vector<char>>& maze) {          // Displays the maze
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            cout << maze[i][j];
            
        }
        cout << endl;
    } 
}
void MazeClear(vector<vector<char>>& maze) {  // This function iterates through the maze to clear the old robots and player positions
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++) {
            if (maze[i][j] == 'R' || maze[i][j] == 'H') {
                maze[i][j] = ' ';
            }
        }
    }
    return;
}
bool RobotsAlive(const vector<string>& robots) {
    for (int i = 1; i < robots.size(); i++) {
        if (robots[i] != "r") {
            return true;
        }
    }
    return false;
}
bool RobotsCollision(const string playerPos, const vector<string>& robots) {
    for (size_t i = 1; i < robots.size(); i++) {
        if (robots[i] == playerPos) {
            return true;
        }
    }
    return false;

}
double Timer()
{
    static std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end-start;
    return time.count();
}

void Leaderboard(string playerName, double timeRounded, string leaderString, unsigned mazeNum) {

    vector<string> leaderboardString;
    string score, time, old1, old2, screenString, mazeNumString;
    vector<double> scoresVector;

    if (mazeNum < 10 || mazeNum >= 1) {
        mazeNumString = '0'+ to_string(mazeNum);
    }
    else {
        mazeNumString = to_string(mazeNum);
    }

    ofstream leaderboardCheck("MAZE_" + mazeNumString + "_WINNERS.TXT", ios::app);
    leaderboardCheck.close();

    ifstream recall("MAZE_" + mazeNumString + "_WINNERS.TXT");
    if (!recall)
    {
        cout << "Ups! Can't open the leaderboard...";
        return;
    }

    if (recall.is_open())
    {
        getline(recall, old1);
        getline(recall, old2);

        while (getline(recall, score))
        {
            leaderboardString.push_back(score);
        }
        for (size_t i = 0; i < leaderboardString.size(); i++)
        {
            for (int j = 21; j >= 16; j--)
            {
                if (leaderboardString[i][j] == ' ' || leaderboardString[i][j] == '-')
                {
                    break;
                }
                else
                {
                    time = leaderboardString[i][j] + time;
                }
            }
            scoresVector.push_back(stod(time));
            time = "";
        }
    }

    if (leaderboardString.size() == 0)
    {
        leaderboardString.push_back(leaderString);
    }

    bool last_score = false;

    for (size_t i = 0; i < scoresVector.size(); i++)
    {
        if (timeRounded <= scoresVector[i])
        {
            leaderboardString.insert(leaderboardString.begin() + i, leaderString);
            break;
        }
        if (i == scoresVector.size() - 1)
        {
            last_score = true;
        }
    }

    if (last_score)
    {
        leaderboardString.push_back(leaderString);
    }

    ofstream updatedLeaderboard("MAZE_" + mazeNumString + "_WINNERS.TXT");
    updatedLeaderboard <<
        "Player Name         -  Time" << endl <<
        "###########################" << endl;
    for (size_t i = 0; i < leaderboardString.size(); i++)
    {
        updatedLeaderboard << leaderboardString[i] << endl;
    }
    updatedLeaderboard.close();

    ifstream screen("MAZE_" + mazeNumString + "_WINNERS.TXT");
    while (getline(screen, screenString))
    {
        cout << screenString << endl;
    }
}

void GameOver(const vector<vector<char>>& maze, string playerPos, unsigned mazeNum) {
    double time = Timer();
    string playerName;
    Display(maze);
    if (playerPos != "h")
    {
        cout << "Congratulations! You survived the maze! " << endl;    //Winning dialogue
        cout << "Time Played: " << time << " s" << endl;
        cout << "Your Name (20 characters max): ";
        cin.ignore();
        getline(cin, playerName);
        if (cin.eof())
        {
            return;
        }

        while (playerName.size() < 1 || playerName.size() > 20)
        {
            cout << "Invalid name size! Please try again." << endl;
            getline(cin, playerName);
            if (cin.eof())
            {
                return;
            }
        }

        int spacesNum = 20 - playerName.size();  
        string spaces(spacesNum, ' ');    
        playerName = playerName + spaces;              

        double timeRounded = round(time * 1000.0) / 1000.0; 
        string stringRounded = to_string(timeRounded);
        for (int i = stringRounded.size() - 1; i > 0; i--) 
        {
            if (stringRounded[i] == '0')
            {
                stringRounded.pop_back();
            }
            else
            {
                break;
            }
        }
        int timeSize = stringRounded.size();

        spacesNum = 0;                                
        spacesNum = 6 - timeSize;                     
        string timeSpaces(spacesNum, ' ');			

        string leaderString = playerName + "-" + timeSpaces + stringRounded;

        Leaderboard(playerName, timeRounded, leaderString, mazeNum);

    }
    else
    {
        cout << "OH NOOOO! You lost... I bet you'll do better next time ;). " << endl;     // Losing dialogue
        cout << "Time Played: " << time << " s" << endl;
    }
}
void PlayerInput(vector<vector<char>>& maze, string& playerPos, vector<string>& robots) { //After saving the maze as a bidimensional vector, this function takes the player's input and changes he's coordinates in the maze

    char key;
    string pl = "H";
    bool error = true;
    size_t space = playerPos.find(" ");
    int playerX{}, playerY{}, robotsX, robotsY;

    while (error) {


        if (playerPos != "h") {                                                 //Player's position saved as "x y" is separated into integers
            playerX = stoi(playerPos.substr(0, space));
            playerY = stoi(playerPos.substr(space));
        }
        error = false;

        cout << "Where do you want to go? "; cin >> key;


        if (cin.eof()) {
            return;
        }
        if (!cin.good() || (cin.peek() != EOF && cin.peek() != '\n')) {
            cout << "invalid input, try again." << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            error = true;
        }

        else if (key == 'q' || key == 'Q') {
            playerX -= 1;
            playerY -= 1;
        }

        else if (key == 'w' || key == 'W') {
            playerX -= 1;
        }

        else if (key == 'e' || key == 'E') {
            playerX -= 1;                                                          //This block reads players input
            playerY += 1;
        }

        else if (key == 'a' || key == 'A') {
            playerY -= 1;
        }

        else if (key == 's' || key == 'S') {
            //Stay put
        }

        else if (key == 'd' || key == 'D') {
            playerY += 1;
        }

        else if (key == 'z' || key == 'Z') {
            playerX += 1;
            playerY -= 1;
        }

        else if (key == 'x' || key == 'X') {
            playerX += 1;
        }

        else if (key == 'c' || key == 'C') {
            playerX += 1;
            playerY += 1;
        }

        else {
            cout << "Didn't understand that input, can you try again?" << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            error = true;
        }


        if ((maze[playerX][playerY] == 'r') && !error) {
            cout << "Nice try ;) but you can't move there. Choose a valid direction" << endl;
            error = true;
        }

        else if (!error) {
            playerPos = to_string(playerX) + " " + to_string(playerY);

            if (maze[playerX][playerY] != ' ' || RobotsCollision(playerPos, robots)) {
                for (size_t i = 1; i < robots.size(); i++) {
                    if (robots[i] != "r")
                    {
                        robotsX = stoi(robots[i].substr(0, space));
                        robotsY = stoi(robots[i].substr(space));
                        maze[robotsX][robotsY] = 'R';
                    }
                }
                maze[playerX][playerY] = 'h';
                playerPos = "h";
            }
            else {
                maze[playerX][playerY] = 'H';
                playerPos = to_string(playerX) + " " + to_string(playerY);
            }
        }
    }
}
void MoveRobots(vector<vector<char>>& maze, string& playerPos, vector<string>& robots, unsigned mazeNum) {        //Function to move the robots
    int playerX, playerY, robotX, robotY;

    size_t space = playerPos.find(" ");

    if (playerPos != "h")
    {
        playerX = stoi(playerPos.substr(0, space));
        playerY = stoi(playerPos.substr(space));


        for (size_t i = 1; i < robots.size(); i++)
        {

            if (robots[i] == "r") {
                continue;
            }

            else{
                space = robots[i].find(" ");
                robotX = stoi(robots[i].substr(0, space)); 
                robotY = stoi(robots[i].substr(space));

                if (playerX < robotX && playerY < robotY){
                    robotX -= 1;
                    robotY -= 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R'){
                            SameCellRobots(robots, robotX, robotY);
                        }
                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX < robotX && playerY == robotY){
                    robotX -= 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R'){
                            SameCellRobots(robots, robotX, robotY);
                        }
                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX < robotX && playerY > robotY){
                    robotX -= 1;
                    robotY += 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R'){
                            SameCellRobots(robots, robotX, robotY);
                        }

                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX == robotX && playerY < robotY){
                    robotY -= 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R'){
                            SameCellRobots(robots, robotX, robotY);
                        }

                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX == robotX && playerY > robotY){
                    robotY += 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h')
                    {
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R')
                        {
                            SameCellRobots(robots, robotX, robotY);
                        }

                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }
                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX > robotX && playerY < robotY){
                    robotX += 1;
                    robotY -= 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R')
                        {
                            SameCellRobots(robots, robotX, robotY);
                        }

                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX > robotX && playerY == robotY){
                    robotX += 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R'){
                            SameCellRobots(robots, robotX, robotY);
                        }

                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }

                else if (playerX > robotX && playerY > robotY){
                    robotX += 1;
                    robotY += 1;

                    if (maze[robotX][robotY] == 'H' || maze[robotX][robotY] == 'h'){
                        maze[robotX][robotY] = 'h';
                        playerPos = "h";
                    }

                    else if (maze[robotX][robotY] != ' '){

                        if (maze[robotX][robotY] == 'R'){
                            SameCellRobots(robots, robotX, robotY);
                        }

                        robots[i] = "r";
                        maze[robotX][robotY] = 'r';
                    }

                    else{
                        maze[robotX][robotY] = 'R';
                        robots[i] = to_string(robotX) + " " + to_string(robotY);
                    }
                }
            }
        }
    }
    if (playerPos == "h" || !RobotsAlive(robots)) 
    {
        GameOver(maze, playerPos, mazeNum);
        return;
    }

} 
void Play(vector<vector<char>>& maze, vector<string>& robots, string playerPos, unsigned int mazeNum) {
    while (playerPos != "h" && RobotsAlive(robots) && !cin.eof()) {
        Display(maze);
        MazeClear(maze);
        PlayerInput(maze, playerPos, robots);
        MoveRobots(maze, playerPos, robots, mazeNum);
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
            string playerPos;
            char x;
            int mazeWidth, mazeHeight;
            int robotsNum{};

            mazeMap >> mazeHeight >> x >> mazeWidth;

            vector<vector<char>> maze(mazeHeight, vector<char>(mazeWidth));         //Turning the maze into a bidimensional vector
            mazeMap >> noskipws;

            for (int i = 0; i < mazeHeight; i++) {
                getline(mazeMap, line);
                for (int j = 0; j < mazeWidth; j++) {
                    mazeMap >> maze[i][j];
                    if (maze[i][j] == 'R') {
                        robotsNum++;
                    }
                    else if (maze[i][j] == 'H') {
                        playerPos = to_string(i) + " " + to_string(j);              //Saving players coordinates in the following format: "x y"
                    }
                }
            }

            mazeMap.close();
            vector<string> robots(robotsNum + 1);
            int robotID = 1;
            for (int i = 0; i < mazeHeight; i++) {
                for (int j = 0; j < mazeWidth; j++) {
                    if (maze[i][j] == 'R') {
                        robots[robotID] = to_string(i) + " " + to_string(j);        //Saving robots coordinates in the following format: "x y"
                        robotID++;
                    }
                }
            }
            Timer();
            mazeOpened = true;
            Play(maze, robots, playerPos, stoi(mazeNum));

        }
        else {
            cout << "That maze doesn't exist, would you mind trying another one?" << endl;
        }

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

