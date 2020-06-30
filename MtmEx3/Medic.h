#ifndef MEDIC_HW3
#define MEDIC_HW3
#include "Auxiliaries.h"
#include "Character.h"
static const mtm::units_t medic_movement_range = 5;
static const mtm::units_t medic_reload_amount = 5;


namespace mtm
{
	class Medic : public mtm::Character
	{
		public:
		Medic(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type =  mtm::CharacterType::MEDIC);
		void reload() override;
		char getFirstletter() override;
		virtual std::shared_ptr<mtm::Character> clone() const;
		void move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
		void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start,const GridPoint& finish) override;
	};

}

#endif