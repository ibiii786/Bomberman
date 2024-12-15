// Added comments for better understanding
#include <iostream>
#include <SFML/Graphics.hpp>

#include "background.hpp"

Background::Background()
	: type(backgroundBlock) {};

void Background::SetUp()
{
	if (!backgroundTexture.loadFromFile("res/img/background.png"))
	{
		std::cout << "Load failed! " << std::endl;
		getchar();
	}

	LoadTexture(backgroundTexture);
}
