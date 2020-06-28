#include "Soldier.h"
#include "Auxiliaries.h"
#include "Exceptions.h"

static const mtm::units_t power_rate = 3;
static const mtm::units_t damage_radius = 2;

mtm::Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power,Team team, CharacterType type)
		: Character(health, ammo, range, power,team, type)
        {}

void mtm::Soldier::reload()
{
    ammo += reload_amount;
}


//moving the soldier from start cell to finish. (if we can)
 void mtm::Soldier::move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish)
 {
	 if (!board.isWithinLimits(finish) or !board.isWithinLimits(start))
	 {
		 throw IllegalCell();
	 }
	 if (board(start.row,start.col) == nullptr)
	 {
		 throw CellEmpty();
	 }
	 if (GridPoint::distance(start, finish) >= movement_range)
	 {
		 throw MoveTooFar();
	 }
	 if (board(finish.row, finish.col) != nullptr)
	 {
		 throw CellOccupied();
	 }

	 std::shared_ptr<mtm::Character> temp = board(start.row, start.col)->clone();    // u need clone here to make exact copy 
	 board(finish.row, finish.col) = temp;
	 board(start.row, start.col) = nullptr;
 }

 std::shared_ptr<mtm::Character> mtm::Soldier::clone() const
 {
    std::shared_ptr<Character> ptr(new Soldier(*this));
    return ptr;
 }

 void mtm::Soldier::damage(Matrix<std::shared_ptr<mtm::Character>>& board, const GridPoint& start, const GridPoint& finish)
 {
	 if (start.row == finish.row && start.col == finish.col)
	 {
		 board(finish.row, finish.col)->updateHealth(-power);
	 }
	 else
	 {
		 board(finish.row, finish.col)->updateHealth(-(int)ceil(power / power_rate));
	 }

	 // Check if the damaged character has died
	 if (board(finish.row, finish.col)->getHealth() <= 0)
	 {
		 board(finish.row, finish.col) = nullptr;
	 }
 }

// attack function
// soldier attacking the finish cell acoording to the game rules.
 void mtm::Soldier::attack(Matrix<std::shared_ptr<mtm::Character>>& board, const mtm::GridPoint& start, const mtm::GridPoint& finish)
 {
	 if (!board.isWithinLimits(finish) or !board.isWithinLimits(start)) 
	 {
		 throw IllegalCell();
	 }
	 if (ammo <= 0)
	 {
		 throw OutOfAmmo();
	 }
	 if (start.row != finish.row && start.col != finish.col)
	 {
		 throw OutOfRange();
	 }
	 if (GridPoint::distance(start, finish) > range) 
	 {
		 throw OutOfRange();
	 }

	 ammo--;
	 GridPoint origin(0, 0);

	 for (origin.row; origin.row < board.height(); origin.row++)
	 {
		 for (origin.col = 0; origin.col < board.width(); origin.col++)
		 {
			 if (GridPoint::distance(origin, finish) <= (int)(ceil(range / damage_radius)+0.5) &&           //ceil returns double need to cast to make sure .
				 board(origin.row, origin.col)->getTeam() != team &&
				 board(origin.row, origin.col) != nullptr)
			 {
				 damage(board, start, origin);
			 }
		 }
	 }
 }

