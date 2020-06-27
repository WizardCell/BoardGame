#include "Sniper.h"
#include "Auxiliaries.h"

Sniper::Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power,mtm::Team team,mtm::CharacterType type )
		: mtm::Character(health, ammo, range, power,team, type)
        {}

void Sniper::reload()
{
    ammo += SNIPER_AMMO_RELOADED; 
}

 bool  Sniper::enoughAmmoForAnAttack()
 {
     return ammo >= SNIPER_AMMO_ATTACK_COST;
 }

 bool  Sniper::canMove(const mtm::GridPoint& start, const mtm::GridPoint& finish)
 {
     return mtm::GridPoint::distance(start,finish) <= SNIPER_MOVEMENT_RANGE ;
 }

 std::shared_ptr<mtm::Character>  Sniper::clone() const
 {
    std::shared_ptr<mtm::Character> ptr(new  Sniper(*this));
    return ptr;
 }










