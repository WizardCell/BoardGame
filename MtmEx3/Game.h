#ifndef HW3_GAME_H
#define HW3_GAME_H

#include <vector>
#include "Character.h"
#include <iostream>
#include "Sniper.h"
#include "Soldier.h"
#include "Medic.h"




namespace mtm
{
	class Game
	{
	private:
		mtm::Matrix<std::shared_ptr<mtm::Character>>  board;
		std::vector<std::shared_ptr<mtm::Character>> characters;

	public:
		Game(int height, int width);
		~Game() = default;
		Game(const Game& other);
		Game& operator=(const Game& other);
		void addCharacter(const mtm::GridPoint& coordinates, std::shared_ptr<Character> character);
		static std::shared_ptr<mtm::Character> makeCharacter(mtm::CharacterType type, mtm::Team team,mtm::units_t health, mtm::units_t ammo, mtm::units_t range, mtm::units_t power);
		void move(const GridPoint& src_coordinates, const GridPoint& dst_coordinates);
		void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
		void reload(const GridPoint & coordinates);
		friend std::ostream& operator<<(std::ostream& os, const Game game);
		bool isOver(Team* winningTeam=NULL) const;
		
	};

	std::ostream& operator<<(std::ostream& os, const mtm::Game game);
}







#endif
