#include "Soldier.h"
#include "Auxiliaries.h"

Soldier::Soldier(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power,mtm::Team team,mtm::CharacterType type = mtm::CharacterType::SOLDIER)
		: mtm::Character(health, ammo, range, power,team, mtm::CharacterType::SOLDIER)
        {}

void Soldier::reload()
{
    ammo += SOLIDER_AMMO_RELOADED; 
}

 bool Soldier::enoughAmmoForAnAttack()
 {
     return ammo >= SOLIDER_AMMO_ATTACK_COST;
 }

 bool Soldier::canMove(const mtm::GridPoint& start, const mtm::GridPoint& finish)
 {
     return mtm::GridPoint::distance(start,finish) <= SOLIDER_MOVEMENT_RANGE ;
 }

 std::shared_ptr<mtm::Character> Soldier::clone() const
 {
    std::shared_ptr<mtm::Character> ptr(new Soldier(*this));
    return ptr;
 }

