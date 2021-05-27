using namespace std;
#pragma once
#include "Position.h"
#include "Post.h"

class Maze {
public:
	Maze(int numRows, int numCols);
	bool addPost(const Post& post, const Position& position)
		int getnumRows() const;
	int getnumCols() const;
	// other methods
private:
	int numRows, numCols;
	// data structure that represents the posts
};

Maze::Maze{
	this->numRows = numRows;
	this->numCols = numCols;
}