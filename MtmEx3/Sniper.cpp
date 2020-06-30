#include "Sniper.h"
#include "Auxiliaries.h"
#include "Exceptions.h"

static const mtm::units_t min_range_rate = 2;
static const mtm::units_t power_spike = 2;
static const mtm::units_t power_increase_rate = 3;


mtm::Sniper::Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type)
	: mtm::Character(health, ammo, range, power, team, type)
{
	counter = 0;
}

void mtm::Sniper::reload()
{
	ammo += reload_amount;
}

std::shared_ptr<mtm::Character> mtm::Sniper::clone() const
{
	std::shared_ptr<mtm::Character> ptr(new mtm::Sniper(*this));
	return ptr;
}

char mtm::Sniper::getFirstletter()
{
	if (team == CPP)
	{
		return 'N';
	}
	else
	{
		return 'n';
	}

}

// move sniper between 2 cells . start,finish on this board.
void mtm::Sniper::move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish)
{
	if (!board.isWithinLimits(finish) or !board.isWithinLimits(start))
	{
		throw IllegalCell();
	}
	if (board(start.row, start.col) == nullptr)
	{
		throw CellEmpty();
	}
	if (GridPoint::distance(start, finish) > movement_range)
	{
		throw MoveTooFar();
	}
	if (board(finish.row, finish.col) != nullptr)
	{
		throw CellOccupied();
	}

	std::shared_ptr<mtm::Character> temp = board(start.row, start.col)->clone();
	board(finish.row, finish.col) = temp;
	board(start.row, start.col) = nullptr;
}

//attack function for the sniper.
//@param game board , sniper cell , target cell.
void mtm::Sniper::attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish)
{
	if (!board.isWithinLimits(finish) or !board.isWithinLimits(start))
	{
		throw IllegalCell();
	}
	if (board(start.row, start.col) == nullptr)
	{
		throw CellEmpty();
	}
	if (GridPoint::distance(start, finish) > range or GridPoint::distance(start, finish) < (int)(ceil(range / min_range_rate) + 0.5))
	{
		throw OutOfRange();
	}
	if (ammo <= 0)
	{
		throw OutOfAmmo();
	}
	if (board(finish.row, finish.col) == nullptr or board(finish.row, finish.col)->getTeam() == team)
	{
		throw IllegalTarget();
	}
	
	ammo = ammo - attack_ammo_cost; //reduce ammo

	//if we get here it is a legal attack 
	if (counter == power_spike)   //if counter=3 we do a power spike.
	{
		board(finish.row, finish.col)->updateHealth(-power_increase_rate * power);
		counter = 0;
	}
	else
	{
		board(finish.row, finish.col)->updateHealth(-power);
		counter++;
	}

	if (board(finish.row, finish.col)->getHealth() <= 0)     //check if the enemy died
	{
		board(finish.row, finish.col) = nullptr;
	}


}











