
#include "Game.h"
#include "Exceptions.h"

mtm::Game::Game(int height, int width) : board((height <= 0 or width <= 0) ?
 throw mtm::IllegalArgument() : mtm::Matrix<std::shared_ptr<mtm::Character>>(Dimensions(height,width),nullptr))
{
	std::vector<std::shared_ptr<mtm::Character>> characters;
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
	std::vector<std::shared_ptr<mtm::Character>> characters;
	for (size_t i=0 ; i<other.characters.size(); i++)
	{
		characters.push_back(other.characters[i]->clone());
	}
	
}	

mtm::Game& mtm::Game::operator=(const Game& other)
{
	for (int i = 0; i < board.height(); i++)
	{
		for (int j = 0; j < board.width(); j++)
		{
			board(i,j) = (other.board)(i,j)->clone();
		}
	}
	for (size_t i=0 ; i<other.characters.size(); i++)
	{
		characters.push_back(other.characters[i]->clone());
	}
		return *this ; 
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

 std::shared_ptr<mtm::Character> makeCharacter(mtm::CharacterType type, mtm::Team team,mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power)
{
	if (type == mtm::CharacterType::SOLDIER)
	{
		std::shared_ptr<mtm::Character> ptr(new Soldier(health,ammo,range,power,team));
		return ptr;
	}
	if (type == mtm::CharacterType::SNIPER)
	{
		std::shared_ptr<mtm::Character> ptr(new Sniper(health,ammo,range,power,team));
		return ptr;
	}
	if (type == mtm::CharacterType::MEDIC)
	{
		std::shared_ptr<mtm::Character> ptr(new Medic(health,ammo,range,power,team));
		return ptr;
	}
	return nullptr; // should not get here
}

int main()
{
	mtm::Game g1(8,8);
	g1.addCharacter(mtm::GridPoint(1,1), mtm::Game::makeCharacter(mtm::CharacterType::MEDIC, mtm::Team::CPP, 10, 2, 4, 5));
	g1.addCharacter(mtm::GridPoint(1,4), mtm::Game::makeCharacter(mtm::CharacterType::SNIPER, mtm::Team::CPP, 10, 2, 4, 5));
	g1.addCharacter(mtm::GridPoint(6,1), mtm::Game::makeCharacter(mtm::CharacterType::SOLDIER, mtm::Team::PYTHON, 10, 2, 4, 5));
	return 0;
}
