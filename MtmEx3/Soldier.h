#ifndef EX3_SOLDIER_H
#define EX3_SOLDIER_H

#include "Auxiliaries.h"
#include "Character.h"

static const mtm::units_t movement_range = 3;
static const mtm::units_t reload_amount = 3;
static const mtm::units_t attack_cost = 1;

namespace mtm
{
	class Soldier : public Character
	{
	private:
		// Helper function that deals damage to enemies
		void damage(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish);

	public:
		Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team, CharacterType type = CharacterType::SOLDIER);
		~Soldier() = default;
		void reload() override;
		char getFirstletter();
		void move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
		void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
		std::shared_ptr<Character> clone() const override;
	};
}
#endif // EX3_SOLDIER_H
