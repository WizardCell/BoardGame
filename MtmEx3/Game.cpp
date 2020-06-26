
#include "Game.h"

mtm::Game::Game(int height, int width)
	: height(height), width(width)
{
	if (height <= 0 || width <= 0)
	{
		throw IllegalArgument();
	}
}

mtm::Game::~Game()
{

}

mtm::Game::Game(const Game& other)
{

}

mtm::Game::Game& mtm::Game::operator=(const Game& other)
{

}
