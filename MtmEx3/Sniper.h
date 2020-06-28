#ifndef SNIPER_HW3
#define SNIPER_HW3
#include "Auxiliaries.h"
#include "Character.h"
#include "Matrix.h"

static const mtm::units_t sniper_movement_range = 4;
static const mtm::units_t sniper_reload_amount = 2;
static const mtm::units_t sniper_attack_cost = 1;

namespace mtm
{
	class Sniper : public mtm::Character
	{
		private:
		int counter ;
		public:
			Sniper(mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power, mtm::Team team, mtm::CharacterType type =  mtm::CharacterType::SNIPER);
			void reload() override;
			char getFirstletter() override;
			void move(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start, const GridPoint& finish) override;
			void attack(Matrix<std::shared_ptr<Character>>& board, const GridPoint& start,const GridPoint& finish) override;
			virtual std::shared_ptr<mtm::Character> clone() const;


	};

}
#endif