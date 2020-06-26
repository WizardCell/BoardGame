#ifndef EX3_SOLDIER_H
#define EX3_SOLDIER_H

static const units_t movement_range = 3;
static const units_t ammo_reloaded = 3;
static const units_t ammo_attack_cost = 1;

class Soldier : public Character
{
	public Soldier(units_t health, units_t ammo, units_t range, units_t power)
		: Character(health, ammo, range, power)
};







#endif // EX3_SOLDIER_H
