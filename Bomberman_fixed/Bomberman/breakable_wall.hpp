// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "wall.hpp"
#include "enum.hpp"

class BreakableWall : public Wall
{
	int type;										
	sf::Texture breakable_wall;						
public:
	BreakableWall();

	virtual void SetUp() override;
};