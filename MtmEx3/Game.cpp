
#include "Game.h"
#include "Exceptions.h"


mtm::Game::Game(int height, int width) : board((height <= 0 or width <= 0) ?
	throw mtm::IllegalArgument() : mtm::Matrix<std::shared_ptr<mtm::Character>>(Dimensions(height, width), nullptr))
{}

//copy constructor
mtm::Game::Game(const Game& other) : board(Dimensions(other.board.height(), other.board.width()), nullptr)
{
	for (int i = 0; i < board.height(); i++)
	{
		for (int j = 0; j < board.width(); j++)
		{
			if (other.board(i, j) != nullptr)
			{
				board(i, j) = (other.board)(i, j)->clone();
			}
		}
	}
}

//operator=
//the 2 games not connected we use clone .
mtm::Game& mtm::Game::operator=(const Game& other)
{
	for (int i = 0; i < board.height(); i++)
	{
		for (int j = 0; j < board.width(); j++)
		{
			if (other.board(i, j) != nullptr)
			{
				board(i, j) = (other.board)(i, j)->clone();
			}
			else
			{
				board(i, j) = nullptr;
			}
		}
	}
}

//adding character to the board
//no need to make a copy we use the original.
void mtm::Game::addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<mtm::Character> character)
{
	if (coordinates.row <0 or coordinates.row > board.height() or coordinates.col < 0 or coordinates.col > board.width())
	{
		throw IllegalCell();
	}

	if (board(coordinates.row, coordinates.col) != nullptr)
	{
		throw CellOccupied();
	}
	board(coordinates.row, coordinates.col) = character;
}

//adding new character accodring to the values were given 
//(excptions send from the cons')
std::shared_ptr<mtm::Character> mtm::Game::makeCharacter(mtm::CharacterType type, mtm::Team team, mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power)
{
	if (type == mtm::CharacterType::SOLDIER)
	{
		std::shared_ptr<mtm::Character> ptr(new Soldier(health, ammo, range, power, team));
		return ptr;
	}
	if (type == mtm::CharacterType::SNIPER)
	{
		std::shared_ptr<mtm::Character> ptr(new Sniper(health, ammo, range, power, team));
		return ptr;
	}
	if (type == mtm::CharacterType::MEDIC)
	{
		std::shared_ptr<mtm::Character> ptr(new Medic(health, ammo, range, power, team));
		return ptr;
	}
	return nullptr; // should not get here
}

//calling move function according to the character in the cell (polymorphsim) 
void mtm::Game::move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates)
{
	if (board(src_coordinates.row, src_coordinates.col) == nullptr)
	{
		throw CellEmpty();
	}
	board(src_coordinates.row, src_coordinates.col)->move(board, src_coordinates, dst_coordinates);
}

//calling attack function for the character in the src_coordiantes
void mtm::Game::attack(const GridPoint& src_coordinates, const GridPoint & dst_coordinates)
{
	if (board(src_coordinates.row, src_coordinates.col) == nullptr)
	{
		throw CellEmpty();
	}
	board(src_coordinates.row, src_coordinates.col)->attack(board, src_coordinates, dst_coordinates);
}

void mtm::Game::reload(const mtm::GridPoint& coordinates)
{
	if (!(board.isWithinLimits(coordinates)))
	{
		throw IllegalCell();
	}
	if (board(coordinates.row, coordinates.col) == nullptr)
	{
		throw CellEmpty();
	}
	board(coordinates.row, coordinates.col)->reload();
}

//operator << calling printMatrix
std::ostream& mtm::operator<<(std::ostream& os, const mtm::Game game)
{
	int col = game.board.width();
	char* names = new char[game.board.size()];
	for (int i = 0; i < game.board.height(); i++)
	{
		for (int j = 0; j < game.board.width(); j++)
		{
			if (game.board(i, j) == nullptr)
			{
				names[i*col + j] = ' ';
			}
			else
			{
				names[i*col + j] = game.board(i, j)->getFirstletter();
			}

		}

	}
	std::ostream& s = printGameBoard(os, names, names + game.board.size(), col);
	delete[] names;
	return s;
}

//checking if the game is over or not
// not over - return false
// over - return true , and write the winner to the pointer if he was not given  NULL
// over + pointer NULL - return true
bool mtm::Game::isOver(Team* winningTeam) const
{
	int cpp_counter = 0;
	int python_counter = 0;
	for (int i = 0; i < board.height(); i++)
	{
		for (int j = 0; j < board.width(); j++)
		{
			if (board(i, j) == nullptr)
			{
				continue;
			}
			else
			{
				if (board(i, j)->getTeam() == CPP)
				{
					cpp_counter++;
					continue;
				}
				python_counter++;
			}

		}

	}
	//now we analysis the data
	if ((cpp_counter == 0 and python_counter == 0) or (cpp_counter != 0 and python_counter != 0)) //game not over
	{
		return false;
	}
	if (winningTeam != NULL and winningTeam != nullptr)
	{
		if (cpp_counter != 0 and python_counter == 0)
		{
			*winningTeam = CPP;
			return true;
		}
		if (cpp_counter == 0 and python_counter != 0)
		{
			*winningTeam = PYTHON;
			return true;
		}
	}
	if (winningTeam == nullptr or winningTeam == NULL)
	{
		return true;
	}
	return false; //should not get here

}