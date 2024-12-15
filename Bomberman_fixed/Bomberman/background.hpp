// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "wall.hpp"

class Background : public Wall
{	
	int type;														
	sf::Texture backgroundTexture;									

public:
	Background();

	virtual void SetUp() override;
};