#ifndef HW3_GAME_H
#define HW3_GAME_H

#include <vector>
#include "Character.h"

namespace mtm
{
	class Game
	{
	private:
		int height, width;

		std::vector<Character> Characters;
	public:
		Game(int height, int width);
		~Game();
		Game(const Game& other);
		Game& operator=(const Game& other);


		


	};

}







#endif
