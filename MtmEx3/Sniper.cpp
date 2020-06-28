#include "Sniper.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
using namespace mtm;

static const int min_range_rate =2 ;
static const int power_spike = 3 ;



Sniper::Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power,mtm::Team team,mtm::CharacterType type )
		: mtm::Character(health, ammo, range, power,team, type)
        {
            counter = 0 ;
        }

void Sniper::reload()
{
    ammo += sniper_reload_amount; 
}

std::shared_ptr<mtm::Character>  Sniper::clone() const
 {
    std::shared_ptr<mtm::Character> ptr(new  Sniper(*this));
    return ptr;
 }

 char Sniper::getFirstletter()
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
void Sniper::move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish)
 {
     if (!board.isWithinLimits(finish) or !board.isWithinLimits(start))
	 {
		 throw IllegalCell();
	 }
	 if (board(start.row,start.col) == nullptr)
	 {
		 throw CellEmpty();
	 }
	 if (GridPoint::distance(start, finish) > sniper_movement_range)
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

void Sniper::attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start,const GridPoint& finish) 
{
    if (!board.isWithinLimits(finish) or !board.isWithinLimits(start)) 
	 {
		 throw IllegalCell();
	 }
	 if (board(start.row ,start.col) == nullptr)
	 {
		 throw CellEmpty();
	 }
     if (GridPoint::distance(start, finish) > range or GridPoint::distance(start,finish) < (int)(ceil(range/min_range_rate)+0.5))
	 {
		 throw OutOfRange();
	 }
    if (ammo <= 0)
    {
        throw OutOfAmmo();
    }
    if (board(finish.row ,finish.col) == nullptr or board(finish.row ,finish.col)->getTeam() == team )
    {
        throw IllegalTarget();
    }


    //if we get here it is a legal attack 
    ammo--;
    if (counter == power_spike)   //if counter=3 we do a power spike.
    {
        board(finish.row ,finish.col)->updateHealth(-2 * power);
        counter = 0;
    }
    else
    {
        board(finish.row ,finish.col)->updateHealth(-power);
        counter++ ;
    }
    
    if (board(finish.row ,finish.col)->getHealth() <= 0)     //check if the enemy died
    {
        board(finish.row ,finish.col) = nullptr;
    }


}
 










