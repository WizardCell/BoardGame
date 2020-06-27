
#include "Medic.h"
#include "Auxiliaries.h"

Medic::Medic(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power,mtm::Team team,mtm::CharacterType type)
		: mtm::Character(health, ammo, range, power,team,type)
        {}

void Medic::reload()
{
    ammo += MEDIC_AMMO_RELOADED; 
}

 bool  Medic::enoughAmmoForAnAttack()
 {
     return ammo >= MEDIC_AMMO_ATTACK_COST;
 }

 bool  Medic::canMove(const mtm::GridPoint& start, const mtm::GridPoint& finish)
 {
     return mtm::GridPoint::distance(start,finish) <= MEDIC_MOVEMENT_RANGE ;
 }

 std::shared_ptr<mtm::Character>  Medic::clone() const
 {
    std::shared_ptr<mtm::Character> ptr(new  Medic(*this));
    return ptr;
 }










