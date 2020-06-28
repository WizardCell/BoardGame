#include "Soldier.h"
#include "Auxiliaries.h"

static const mtm::units_t power_rate = 3;
static const mtm::units_t damage_radius = 2;
using mtm::Soldier;

Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power,Team team, CharacterType type)
		: Character(health, ammo, range, power,team, type)
        {}

void Soldier::reload()
{
    ammo += reload_amount;
}

 bool Soldier::enoughAmmoForAnAttack()
 {
     return ammo >= attack_cost;
 }

 void Soldier::move(Matrix<Character>& board, const GridPoint& start, const GridPoint& finish)
 {
	 if (GridPoint::distance(start, finish) >= movement_range)
	 {
		 throw MoveTooFar();
	 }
	 if (!board.isWithinLimits(finish))
	 {
		 throw IllegalCell();
	 }
	 if (board(finish.row, finish.col) != nullptr)
	 {
		 throw CellOccupied();
	 }

	 std::shared_ptr<Character> temp = board(start.row, start.col);
	 board(finish.row, finish.col) = temp;
	 board(start.row, start.col) = nullptr;
 }

 std::shared_ptr<Character> Soldier::clone() const
 {
    std::shared_ptr<Character> ptr(new Soldier(*this));
    return ptr;
 }

 void Soldier::damage(Matrix<Character>& board, const GridPoint& start, const GridPoint& finish)
 {
	 if (start.row == finish.row && start.col == finish.col)
	 {
		 board(finish.row, finish.col)->updateHealth(-power);
	 }
	 else
	 {
		 board(finish.row, finish.col)->updateHealth(-ceil(power / power_rate));
	 }

	 // Check if the damaged character has died
	 if (board(finish.row, finish.col)->getHealth() <= 0)
	 {
		 board(finish.row, finish.col) = nullptr;
	 }
 }

 void Soldier::attack(Matrix<Character>& board, const mtm::GridPoint& start, const mtm::GridPoint& finish)
 {
	 if (!board.isWithinLimits(finish))
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
			 if (GridPoint::distance(origin, finish) <= ceil(range / damage_radius) &&
				 board(origin.row, origin.col)->getTeam() != team &&
				 board(origin.row, origin.col) != nullptr)
			 {
				 damage(board, start, origin);
			 }
		 }
	 }
 }

