// Added comments for better understanding
#include <iostream>
#include <SFML/Graphics.hpp>

#include "breakable_wall.hpp"

BreakableWall::BreakableWall()
	:type(breakableBlock) {};

void BreakableWall::SetUp()
{
	if (!breakable_wall.loadFromFile("res/img/bricks.jpg"))
	{
		std::cout << "Load failed! " << std::endl;
		getchar();
	}

	LoadTexture(breakable_wall);
}
