
#include "Game.h"
#include "Exceptions.h"

mtm::Game::Game(int height, int width) : board((height <= 0 or width <= 0) ?
 throw mtm::IllegalArgument() : mtm::Matrix<std::shared_ptr<mtm::Character>>(Dimensions(height,width),nullptr))
{
	std::vector<Character> characters;
}
mtm::Game::Game(const Game& other) :  board(Dimensions(other.board.height(),other.board.width()),nullptr) 
{
	for (int i = 0; i < board.height(); i++)
	{
		for (int j = 0; j < board.width(); j++)
		{
			board(i,j) = (other.board)(i,j)->clone();
		}
	}
	std::vector<mtm::Character> characters = other.characters ;
	
}	

mtm::Game::Game& mtm::Game::operator=(const Game& other)
{
	for (int i = 0; i < board.height(); i++)
	{
		for (int j = 0; j < board.width(); j++)
		{
			board(i,j) = (other.board)(i,j)->clone();
		}
	}
	std::vector<mtm::Character> characters = other.characters ;

}

void mtm::Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<mtm::Character> character)
{
  	if ( coordinates.row <0 or coordinates.row > board.height() or coordinates.col < 0 or coordinates.col > board.width())
 	 {
	  throw IllegalCell();
  	}
	
	if ( board(coordinates.row,coordinates.col) != nullptr)
	{
		throw CellOcupied();
	}
	board(coordinates.row,coordinates.col) = character ;
}

static std::shared_ptr<mtm::Character> makeCharacter(mtm::CharacterType type, mtm::Team team,mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power)
{
	std::shared_ptr<mtm::Character> ptr(new type(health,ammo,range,power,team));
	return ptr;
}
