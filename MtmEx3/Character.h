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
		CharacterType type;

	public:
		Character(units_t health, units_t ammo, units_t range, units_t power, Team team, CharacterType type);
		Character(const Character& other);
		virtual ~Character() = default;
		// @TODO: Board class to be implemented
		//virtual void move(Board<Character>& board, const GridPoint& s_place, const GridPoint& d_place) = 0;
		//virtual void attack(Board<Character>& board, const GridPoint& s_place,const GridPoint& d_place) = 0;

		virtual void updateHealth(units_t delta);
		virtual units_t getHealth() const;
		CharacterType getType() const;
		virtual Team getTeam() const;
		virtual void reload() = 0;
		virtual std::shared_ptr<Character> clone() const = 0;
		
		


	};
}


#endif // EX3_CHARACTER_H

