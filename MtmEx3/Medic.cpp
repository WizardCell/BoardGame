
#include "Medic.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
using namespace mtm;

Medic::Medic(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power,mtm::Team team,mtm::CharacterType type)
		: mtm::Character(health, ammo, range, power,team,type)
        {}

//adding ammo with the amunt allowed to this character
void Medic::reload()
{
    ammo += medic_reload_amount; 
}

 std::shared_ptr<mtm::Character>  Medic::clone() const
{
    std::shared_ptr<mtm::Character> ptr(new  Medic(*this));
    return ptr;
}
char Medic::getFirstletter()
{
	if (team == CPP)
	{
		return 'M';
	}
	else
	{
		return 'm';
	}

}

//move Medic from start to finish if possible
/*Exceptions
*IllegalCell - one of the cells out of the board
*CelleEmpty - start cell empty
*MoveToFar - the distance out of Medic movement_range
*CellOcccupied - finish cell is busy
*/
void Medic::move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish)
{
     if (!board.isWithinLimits(finish) or !board.isWithinLimits(start))
	 {
		 throw IllegalCell();
	 }
	 if (board(start.row,start.col) == nullptr)
	 {
		 throw CellEmpty();
	 }
	 if (GridPoint::distance(start, finish) > medic_movement_range)
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

//attack function for Medic 
//@param game board , Medic cell , target cell 
void Medic::attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start,const GridPoint& finish)
{
    if (!board.isWithinLimits(finish) or !board.isWithinLimits(start)) 
	 {
		 throw IllegalCell();
	 }
	 if (board(start.row ,start.col) == nullptr)
	 {
		 throw CellEmpty();
	 }
     if (GridPoint::distance(start, finish) > range )
	 {
		 throw OutOfRange();
	 }
    if (ammo <= 0 and (board(finish.row,finish.col)->getTeam() != team))
    {
        throw OutOfAmmo();
    }
    if( (start.row == finish.row and start.col == finish.col) or board(finish.row,finish.col) == nullptr)  //self attacking && empty cell
    {
        throw IllegalTarget();
    }

    if (board(finish.row,finish.col)->getTeam() != team )
    {
        ammo--;
        board(finish.row,finish.col)->updateHealth(-power);
        if (board(finish.row,finish.col)->getHealth() <= 0)
        {
            board(finish.row,finish.col) = nullptr;
        }
    }
    else  //same teams ,(we heal teammates)
    {
        board(finish.row,finish.col)->updateHealth(power);
    }
    
}







