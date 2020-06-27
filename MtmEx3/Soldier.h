#ifndef EX3_SOLDIER_H
#define EX3_SOLDIER_H
#include "Auxiliaries.h"
#include "Character.h"
#define SOLIDER_MOVEMENT_RANGE 3
#define SOLIDER_AMMO_RELOADED 3
#define SOLIDER_AMMO_ATTACK_COST 1

class Soldier : public mtm::Character
{
	public:
	Soldier(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type =  mtm::CharacterType::SOLDIER);
	void reload() override;
	bool enoughAmmoForAnAttack() override;
	bool canMove(const mtm::GridPoint& start, const mtm::GridPoint& finish) override;
	virtual std::shared_ptr<mtm::Character> clone() const;


};







#endif // EX3_SOLDIER_H
