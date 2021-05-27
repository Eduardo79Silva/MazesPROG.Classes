#include "Maze.h"



Maze::Maze(int numRows, int numCols)
{
	numCols = nCols;
	numRows = nRows;
}

bool Maze::addPost(const Post& post, const Position& position)
{
	posts.push_back(post);
	return false;
}

int Maze::getnumRows() const
{
	return 0;
}

int Maze::getnumCols() const
{
	return 0;
}
