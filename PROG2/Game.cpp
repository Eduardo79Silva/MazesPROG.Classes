using namespace std;
#include "Game.h"
#include<iostream>;
#include <string>;
#include<stdio.h>;
#include<vector>;

Game::Game(const std::string& filename)
{
	bool over = false;
	std::ifstream mazeMap(filename);
	int mazeHeight, mazeWidth, number_of_robots = 0;
	char x, objectChar;
	std::string newline;


	mazeMap >> mazeHeight >> x >> mazeWidth;
	maze = Maze(mazeHeight, mazeWidth);
	mazeMap >> std::noskipws;


	for (int i = 0; i < mazeHeight; i++) //this puts the maze into the vector
	{
		std::getline(mazeMap, newline);
		for (int j = 0; j < mazeWidth; j++)
		{
			mazeMap >> objectChar;
			if (objectChar == 'R') // find robots
			{
				robots.push_back(Robot(i, j)); //this way of creating will put the robots in order of their id in the vector
			}
			else if (objectChar == 'H') // finds the hero and saves its position
			{
				player = Player(i, j, 'H');
			}
			else if (objectChar == '*' || objectChar == '+' || objectChar == 'O')
			{
				maze.addPost(Post(i, j, objectChar));
			}
		}
	}
	mazeMap.close();
}

bool Game::play()
{
	Movement playermove;
	Robot testsrobot;
	score.TimeStart();
	while (!over)
	{
		showGameDisplay();
		do
		{
			playermove = getinput();
		} while (!isvalid(playermove)); //game could be over if player suicides here
		if (!over && player.isAlive()) //the game being over while the playes still alive = gate reach, so player still needs to move
		{
			player.move(playermove);
		}
		if (!over)
		{
			for (unsigned k = 0; k < robots.size(); k++)
			{
				testsrobot = robots[k];
				testsrobot.move(player.getRow(), player.getCol());
				//testar colisão com o robo de testes
			}
		}
	}
	return player.isAlive();
}


bool Game::isValid()
{
	if (over == true) //in case user types cntrl z
	{
		return true;
	}
	int playermovex = player.getCol() + move.dCol;
	int playermovey = player.getRow() + move.dRow;
	for (int k = 0; k < maze.postssize(); k++) //check if player is trying to move to a cell occupied by non-electrified post
	{
		if ((maze.getpost(k).getRow() == playermovey) && (maze.getpost(k).getCol() == playermovex))
		{
			if (maze.getpost(k).getSymbol() == '+')
			{
				std::cout << "invalid move" << std::endl;
				return false;
			}

			else if (maze.getpost(k).getSymbol() == '*')
			{
				player.setAsDead(); //player suicide (but is a valid move)
				over = true;
				score.TimeEnd();
				return true;
			}
			else
			{
				over = true; //player reached gate
				score.TimeEnd();
				return true;
			}
		}
	}
	for (unsigned k = 0; k < robots.size(); k++)
	{
		if (robots[k].getRow() == playermovey && robots[k].getCol() == playermovex) //cant move to dead/stuck robots
		{
			if (robots[k].getsymbol() == 'r')
			{
				std::cout << "invalid move" << std::endl;
				return false;
			}
			else //player tries to punch the living robot?
			{
				player.setAsDead(); //player suicide (but is a valid move)
				over = true;
				std::cout << "Player used 'Punch Robot!', it's not very effective..." << std::endl;
				score.TimeEnd();
				return true;
			}
		}
	}
	return true;
}

void Game::showGameDisplay() const
{
	bool gotsomething = false;
	std::string display = "";
	for (int i = 0; i < maze.getnumRows(); i++)
	{
		for (int j = 0; j < maze.getnumCols(); j++)
		{
			for (int k = 0; k < maze.postssize(); k++)
			{
				if (maze.getpost(k).getRow() == i && maze.getpost(k).getCol() == j)
				{
					display += maze.getpost(k).getSymbol();
					gotsomething = true;
					break;
				}
			}
			if (player.getRow() == i && player.getCol() == j && !gotsomething)
			{
				display += player.getSymbol();
				gotsomething = true;
			}
			if (!gotsomething)
			{
				for (unsigned k = 0; k < robots.size(); k++)
				{
					if (robots[k].getRow() == i && robots[k].getCol() == j)
					{
						display += robots[k].getsymbol();
						gotsomething = true;
						break;
					}
				}
			}
			if (!gotsomething)
			{
				display += " ";
			}
			gotsomething = false;
		}
		display += '\n';
	}
	std::cout << display << std::endl;
}

bool Game::collide(Robot& robot, Post& post)
{
	return false;
}

bool Game::collide(Robot& robot, Player& player)
{
	return false;
}
