// Added comments for better understanding
#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include "wall.hpp"

class SolidWall : public Wall
{
	int type;											
	sf::Texture solid_texture;							
public:
	SolidWall();

	virtual void SetUp() override;
};