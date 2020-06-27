#ifndef MEDIC_HW3
#define MEDIC_HW3
#include "Auxiliaries.h"
#include "Character.h"
#define MEDIC_MOVEMENT_RANGE 5
#define MEDIC_AMMO_RELOADED 5
#define MEDIC_AMMO_ATTACK_COST 1

class Medic : public mtm::Character
{
	public:
	Medic(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type =  mtm::CharacterType::MEDIC);
	void reload() override;
	bool enoughAmmoForAnAttack() override;
	bool canMove(const mtm::GridPoint& start, const mtm::GridPoint& finish) override;
	virtual std::shared_ptr<mtm::Character> clone() const;


};
#endif