// Added comments for better understanding
#include <iostream>
#include <SFML/Graphics.hpp>

#include "block.hpp"

void Block::Update(const sf::Time deltaTime)
{
	sprite.setPosition(position);
}
