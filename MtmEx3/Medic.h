#ifndef EX3_MEDIC_HW3
#define EX3_MEDIC_HW3

#include "Auxiliaries.h"
#include "Character.h"

static const mtm::units_t movement_range = 5;
static const mtm::units_t reload_amount = 5;
static const mtm::units_t attack_ammo_cost = 1;

namespace mtm
{
	class Medic : public mtm::Character
	{
	public:
		Medic(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type = mtm::CharacterType::MEDIC);
		~Medic() = default;
		void reload() override;
		char getFirstletter() override;
		std::shared_ptr<mtm::Character> clone() const override;
		void move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
		void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
	};

}

#endif // EX3_MEDIC_H