#include "Player.h"

Player::Player(int row, int col, char symbol)
{
	this->row = row;
	this->col = col;
	this->symbol = symbol;
	alive = true;
}

Player::Player()
{
	row = -1;
	col = -1;
	symbol = 'H';
	alive = true;
}

int Player::getRow() const
{
	return 0;
}

int Player::getCol() const
{
	return 0;
}

char Player::getSymbol() const
{
	return 0;
}

bool Player::isAlive() const
{
	return false;
}

void Player::setAsDead()
{
}

bool Player::move(Movement delta)
{
	row += delta.dRow;
	col += delta.dCol;
	return false;
}
