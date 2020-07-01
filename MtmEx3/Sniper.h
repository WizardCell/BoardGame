#ifndef EX3_SNIPER_HW3
#define EX3_SNIPER_HW3
#include "Auxiliaries.h"
#include "Character.h"
#include "Matrix.h"

static const mtm::units_t movement_range = 4;
static const mtm::units_t reload_amount = 2;
static const mtm::units_t attack_ammo_cost = 1;

namespace mtm
{
	class Sniper : public mtm::Character
	{
	private:
		int counter;
	public:
		Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type = mtm::CharacterType::SNIPER);
		~Sniper() = default;
		void reload() override;
		char getFirstletter() override;
		void move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
		void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
		virtual std::shared_ptr<mtm::Character> clone() const override;


	};

}
#endif // EX3_Sniper_H