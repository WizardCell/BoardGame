
#include "Character.h"
#include "Exceptions.h"

mtm::Character::Character(units_t health, units_t ammo, units_t range, units_t power, Team team, CharacterType type)
	: health(health), ammo(ammo), range(range), power(power), team(team), type(type)
{
	if (health <= 0 || ammo < 0 || range < 0 || power < 0)
	{
		throw IllegalArgument();
	}
}

mtm::Character::Character(const Character& other)
{
	(*this) = other;
}

mtm::units_t mtm::Character::getHealth() const
{
	return health;
}

void mtm::Character::updateHealth(units_t delta)
{
	health += delta;
}

mtm::CharacterType mtm::Character::getType() const
{
	return type;
}

mtm::Team mtm::Character::getTeam() const
{
	return team;
}

