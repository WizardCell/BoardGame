#include "Soldier.h"
#include "Auxiliaries.h"
#include "Exceptions.h"

static const double power_rate = 2.0;
static const double damage_radius = 3.0;

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
	 if (GridPoint::distance(start, finish) > movement_range)
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

//helper function , that reduces the health of the target and his near teammates according to the attacker power
// @param , game board , the target cell , near cell 
 void mtm::Soldier::damage(Matrix<std::shared_ptr<mtm::Character>>& board, const GridPoint& finish, const GridPoint& near)
 {
	 if (near.row == finish.row && near.col == finish.col)
	 {
		 board(finish.row, finish.col)->updateHealth(-power);
	 }
	 else
	 {
		 board(near.row, near.col)->updateHealth(-(int)ceil(power / power_rate));
	 }

	 // Check if the damaged character has died
	 if (board(near.row, near.col)->getHealth() <= 0)
	 {
		 board(near.row, near.col) = nullptr;
	 }
 }

 //retruns the firsl letter of the character
 //In capital letter if he belongs to CPP  , else small letter
 char mtm::Soldier::getFirstletter()
 {
	 if (team == CPP)
	 {
		 return 'S';
	 }
	 else
	 {
		 return 's';
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
	 if (board(start.row ,start.col) == nullptr)
	 {
		 throw CellEmpty();
	 }
	 if (GridPoint::distance(start, finish) > range) 
	 {
		 throw OutOfRange();
	 }
	 if (ammo <= 0)
	 {
		 throw OutOfAmmo();
	 }
	 if (start.row != finish.row && start.col != finish.col)
	 {
		 throw IllegalTarget();
	 }
	 

	 ammo--;
	 for (int i = 0; i < board.height(); i++)       //now we make the attack 
	 {
		 for (int j = 0; j < board.width(); j++)
		 {
			 GridPoint near(i, j);
			 if (GridPoint::distance(near, finish) <= (int)(ceil(range / damage_radius)+0.5) &&           //ceil returns double need to cast to make sure .
				 board(i,j) != nullptr && 
				 board(i, j)->getTeam() != team )
			 {
				 damage(board, finish, near);    
			 }
		 }
	 }
 }

