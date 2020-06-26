#ifndef EX3_CHARACTER_H
#define EX3_CHARACTER_H

#include "Auxiliaries.h"

namespace mtm
{
	class Character
	{
	protected:
		units_t health;
		units_t ammo;
		units_t range;
		units_t power;
		Team team;
		CharacterType Type;

	public:
		Character(units_t health, units_t ammo, units_t range, units_t power)
			: health(health), ammo(ammo), range(range), power(power) {}
		
		virtual ~Character() {}






	};
}


#endif // EX3_CHARACTER_H

