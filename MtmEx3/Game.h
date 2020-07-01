#ifndef EX3_HW3_GAME_H
#define EX3_HW3_GAME_H

#include "Character.h"
#include <iostream>
#include "Sniper.h"
#include "Soldier.h"
#include "Medic.h"

/* Game class
*A game between 2 teams CPP, PYTHON  to determine who is the best
* The has 3 Characters @Sniper ,Soldier ,Medic@ everyone with his own functions
* we use a board witch is a matrix that we created in Part B
*/



namespace mtm
{
	class Game
	{
	private:
		mtm::Matrix<std::shared_ptr<mtm::Character>> board;

		friend std::ostream& operator<<(std::ostream& os, const Game& game);

	public:
		// C'tors and D'tor
		Game(int height, int width);
		Game(const Game& other);
		~Game() = default;

		// Operators
		Game& operator=(const Game& other);

		// Methods
		void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);
		static std::shared_ptr<mtm::Character> makeCharacter(mtm::CharacterType type, mtm::Team team, mtm::units_t health,
		mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
		void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
		void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
		void reload(const GridPoint & coordinates);
		bool isOver(Team* winningTeam = NULL) const;

	};

	std::ostream& operator<<(std::ostream& os, const mtm::Game& game);
}

#endif // 
