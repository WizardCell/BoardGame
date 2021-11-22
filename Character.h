#ifndef EX3_CHARACTER_H
#define EX3_CHARACTER_H

#include "Auxiliaries.h"
#include "Matrix.h"

#include <memory>
#include <iostream>

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
		virtual void move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) = 0;
		virtual void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start,const GridPoint& finish) = 0;
		virtual char getFirstletter() = 0;
		virtual void updateHealth(units_t delta);
		virtual units_t getHealth() const;
		CharacterType getType() const;
		virtual Team getTeam() const;
		virtual void reload() = 0;
		virtual std::shared_ptr<Character> clone() const = 0;

	};
}


#endif // EX3_CHARACTER_H

