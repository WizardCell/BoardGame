#ifndef SNIPER_HW3
#define SNIPER_HW3
#include "Auxiliaries.h"
#include "Character.h"
#define SNIPER_MOVEMENT_RANGE 5
#define SNIPER_AMMO_RELOADED 5
#define SNIPER_AMMO_ATTACK_COST 1

class Sniper : public mtm::Character
{
	public:
	Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type =  mtm::CharacterType::SNIPER);
	void reload() override;
	bool enoughAmmoForAnAttack() override;
	bool canMove(const mtm::GridPoint& start, const mtm::GridPoint& finish) override;
	virtual std::shared_ptr<mtm::Character> clone() const;


};
#endif